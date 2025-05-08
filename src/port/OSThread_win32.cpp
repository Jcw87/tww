
#include "global.h"
#include <dolphin/os/OSThread.h>

#include <condition_variable>
#include <mutex>
#include <thread>
#include <unordered_map>

#if _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#define OSHalt(msg) OSPanic(__FILE__, __LINE__, msg)

char* GetLastErrorStr() {
    DWORD code = GetLastError();
    LPSTR messageBuffer = NULL;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    return messageBuffer;
}

// ============================================================================
// Side-table: native thread data per OSThread
// ============================================================================

struct PCThreadData {
    HANDLE native;
    DWORD id;
    std::mutex mtx;
    std::condition_variable cv;
    void* (*func)(void*);
    void* param;
    bool started = false;
    bool suspended = false;
};

static std::mutex& GetThreadDataMutex() {
    static std::mutex mtx;
    return mtx;
}

static std::unordered_map<OSThread*, std::unique_ptr<PCThreadData>>& GetThreadDataMap() {
    static std::unordered_map<OSThread*, std::unique_ptr<PCThreadData>> map;
    return map;
}

static PCThreadData* GetThreadData(OSThread* thread) {
    std::lock_guard mapLock(GetThreadDataMutex());
    auto it = GetThreadDataMap().find(thread);
    if (it != GetThreadDataMap().end()) {
        return it->second.get();
    }

    return nullptr;
}

// Side-table for OSThreadQueue -> condition_variable (for OSSleepThread/OSWakeupThread)
static std::mutex& GetQueueCvMutex() {
    static std::mutex mtx;
    return mtx;
}
static std::unordered_map<OSThreadQueue*, std::unique_ptr<std::condition_variable>>& GetQueueCvMap() {
    static std::unordered_map<OSThreadQueue*, std::unique_ptr<std::condition_variable>> map;
    return map;
}

static std::condition_variable& GetQueueCV(OSThreadQueue* queue) {
    std::lock_guard<std::mutex> lock(GetQueueCvMutex());
    auto& map = GetQueueCvMap();
    auto it = map.find(queue);
    if (it == map.end()) {
        auto result = map.emplace(queue, std::make_unique<std::condition_variable>());
        return *result.first->second;
    }
    return *it->second;
}

// ============================================================================
// Thread-local current thread pointer
// ============================================================================

static thread_local OSThread* __OSCurrentThread = nullptr;

// ============================================================================
// Global state
// ============================================================================

OSThread DefaultThread;

// Global interrupt mutex (coarse-grained lock replacing interrupt disable)
// Lazy-initialized to avoid DLL static init crashes
static std::recursive_mutex& GetInterruptMutex() {
    static std::recursive_mutex mtx;
    return mtx;
}

static thread_local int sInterruptLockCount = 0;

// Scheduler suspend count
static std::atomic<s32> sSchedulerSuspendCount{0};

// Active thread count
static std::atomic<s32> sActiveThreadCount{0};

// Switch thread callback
static OSSwitchThreadCallback sSwitchThreadCallback = nullptr;

// ============================================================================
// Internal helpers
// ============================================================================

// Thread entry wrapper - runs on the new std::thread
static void ThreadEntryWrapper(OSThread* thread, PCThreadData* data) {
    // Set thread-local pointer
    __OSCurrentThread = thread;

    // Set context pointers for this thread
    OSClearContext(&thread->context);
    OSSetCurrentContext(&thread->context);

    thread->state = OS_THREAD_STATE_RUNNING;

    // Call the actual thread function
    void* result = data->func(data->param);

    // Thread returned - equivalent to OSExitThread
    thread->exit_value = result;
    thread->state = OS_THREAD_STATE_DEAD;
}

// ============================================================================
// C API functions
// ============================================================================

OSSwitchThreadCallback OSSetSwitchThreadCallback(OSSwitchThreadCallback func) { return NULL; }

static inline void OSSetCurrentThread(OSThread* thread) {
    __OSCurrentThread = thread;
}

void __OSThreadInit() {
    memset(&DefaultThread, 0, sizeof(OSThread));

    OSThread* thread = &DefaultThread;
    thread->state = OS_THREAD_STATE_RUNNING;
    thread->attributes = OS_THREAD_ATTR_DETACH;
    thread->effective_priority = thread->base_priority = 16;
    thread->suspend_count = 0;
    thread->exit_value = (void*)-1;
    thread->mutex = NULL;
    OSInitThreadQueue(&thread->join_queue);
    OSInitMutexQueue(&thread->owned_mutexes);

    OSSetCurrentContext(&thread->context);
    // Create side-table entry
    {
        auto data = std::make_unique<PCThreadData>();
        HANDLE process = GetCurrentProcess();
        HANDLE pseudo = GetCurrentThread();
        if (!DuplicateHandle(process, pseudo, process, &data->native, 0, false, DUPLICATE_SAME_ACCESS)) {
            OSHalt(GetLastErrorStr());
        }
        CloseHandle(process);
        data->id = GetCurrentThreadId();
        GetCurrentThreadStackLimits((PULONG_PTR)&thread->stack_base, (PULONG_PTR)&thread->stack_end);

        std::lock_guard<std::mutex> lock(GetThreadDataMutex());
        GetThreadDataMap()[thread] = std::move(data);
    }
    OSSetCurrentThread(thread);
    OSSetCurrentThreadName("DefaultThread");
    sActiveThreadCount = 1;
}

void OSInitMutexQueue(OSMutexQueue* queue) {
    queue->head = queue->tail = NULL;
}

void OSInitThreadQueue(OSThreadQueue* queue) {
    queue->head = queue->tail = NULL;
}

OSThread* OSGetCurrentThread() {
    if (__OSCurrentThread == NULL) {
        __OSThreadInit();
    }
    return __OSCurrentThread;
}

BOOL OSIsThreadTerminated(OSThread* thread) {
    if (!thread) {
        return true;
    }
    PCThreadData* data = GetThreadData(thread);
    if (!data || !data->native) {
        return true;
    }

    return WaitForSingleObject(data->native, 0) == WAIT_OBJECT_0;
}

s32 OSDisableScheduler() {
    return sSchedulerSuspendCount.fetch_add(1);
}

s32 OSEnableScheduler() {
    return sSchedulerSuspendCount.fetch_sub(1);
}

void OSYieldThread() {
    std::this_thread::yield();
}

DWORD WINAPI ThreadStart(LPVOID param) {
    OSThread* thread = (OSThread*)param;
    __OSCurrentThread = thread;

    thread->state = OS_THREAD_STATE_RUNNING;
    GetCurrentThreadStackLimits((PULONG_PTR)&thread->stack_base, (PULONG_PTR)&thread->stack_end);

    PCThreadData* data = GetThreadData(thread);
    void* result = data->func(data->param);

    thread->exit_value = result;
    thread->state = OS_THREAD_STATE_DEAD;
    return (DWORD)result;
}

BOOL OSCreateThread(OSThread* thread, void* (*func)(void*), void* param, void* stack, u32 stackSize, s32 priority, u16 attr) {
    if (!thread) {
        return false;
    }
    if (priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
        return false;
    }

    // Ensure thread system is initialized
    OSGetCurrentThread();

    memset(thread, 0, sizeof(OSThread));

    thread->state = OS_THREAD_STATE_READY;
    thread->attributes = attr & 1u;
    thread->base_priority = priority;
    thread->effective_priority = priority;
    thread->suspend_count = 1; // Created suspended (GC behavior)
    thread->exit_value = (void*)(intptr_t)-1;
    thread->mutex = nullptr;
    OSInitThreadQueue(&thread->join_queue);
    OSInitMutexQueue(&thread->owned_mutexes);

    thread->stack_base = (u8*)stack;
    thread->stack_end = (u32*)((uintptr_t)stack - stackSize);
    *thread->stack_end = OS_THREAD_STACK_MAGIC;

    // Create side-table entry (but don't start the thread yet)
    {
        auto data = std::make_unique<PCThreadData>();
        data->native = CreateThread(NULL, stackSize, &ThreadStart, thread, CREATE_SUSPENDED, &data->id);
        data->func = func;
        data->param = param;

        std::lock_guard<std::mutex> lock(GetThreadDataMutex());
        GetThreadDataMap()[thread] = std::move(data);
    }

    // Add to active queue
    sActiveThreadCount++;

    return true;
}

void OSExitThread(void* val) {
    OSThread* currentThread = OSGetCurrentThread();
    if (!currentThread) {
        return;
    }

    currentThread->exit_value = val;
    if (currentThread->attributes & OS_THREAD_ATTR_DETACH) {
        currentThread->state = OS_THREAD_STATE_UNINITIALIZED;
    } else {
        currentThread->state = OS_THREAD_STATE_DEAD;
    }
    OSWakeupThread(&currentThread->join_queue);
    sActiveThreadCount--;
    ExitThread(DWORD(val));
}

void OSCancelThread(OSThread* thread) {
    PCThreadData* data = GetThreadData(thread);
    if (!data->native) {
        OSHalt("Thread is not valid\n");
    }
    TerminateThread(data->native, -1);
    CloseHandle(data->native);
    data->native = NULL;
    data->id = 0;
    if (thread->attributes & OS_THREAD_ATTR_DETACH) {
        thread->state = OS_THREAD_STATE_UNINITIALIZED;
    } else {
        thread->state = OS_THREAD_STATE_DEAD;
    }
    sActiveThreadCount--;
}

BOOL OSJoinThread(OSThread* thread, void* val) {
    if (!thread) {
        return false;
    }

    PCThreadData* data = GetThreadData(thread);
    if (!data->native) {
        return false;
    }
    WaitForSingleObject(data->native, INFINITE);
    if (val) {
        if (!GetExitCodeThread(data->native, (LPDWORD)val)) {
            OSHalt(GetLastErrorStr());
        }
    }
    CloseHandle(data->native);
    data->native = NULL;
    data->id = 0;
    return true;
}

void OSDetachThread(OSThread* thread) {
    if (!thread) {
        return;
    }
    thread->attributes |= OS_THREAD_ATTR_DETACH;
    if (thread->state == OS_THREAD_STATE_DEAD) {
        thread->state = OS_THREAD_STATE_UNINITIALIZED;
    }
    NOT_IMPLEMENTED;
}

s32 OSResumeThread(OSThread* thread) {
    PCThreadData* data = GetThreadData(thread);
    if (!data->native) {
        OSHalt("Thread is not valid\n");
    }
    u32 old = thread->suspend_count;
    if (old == 0) {
        OSHalt("Tried to resume a running thread\n");
    }
    thread->suspend_count--;
    if (thread->suspend_count == 0) {
        ResumeThread(data->native);
    }
    return old;
}
s32 OSSuspendThread(OSThread* thread) {
    PCThreadData* data = GetThreadData(thread);
    if (!data->native) {
        OSHalt("Thread is not valid\n");
    }
    u32 old = thread->suspend_count;
    thread->suspend_count++;
    if (old == 0) {
        SuspendThread(data->native);
    }
    return old;
}

void OSSleepThread(OSThreadQueue* queue) {
    if (!queue) {
        return;
    }
    OSThread* currentThread = OSGetCurrentThread();
    if (!currentThread) {
        return;
    }

    currentThread->state = OS_THREAD_STATE_WAITING;
    currentThread->queue = queue;

    // Enqueue into the thread queue
    OSThread* prev = queue->tail;
    if (prev == nullptr) {
        queue->head = currentThread;
    } else {
        prev->link.next = currentThread;
    }
    currentThread->link.prev = prev;
    currentThread->link.next = nullptr;
    queue->tail = currentThread;

    // Wait on the condition variable for this queue
    std::condition_variable& cv = GetQueueCV(queue);
    std::unique_lock<std::mutex> lock(GetQueueCvMutex());
    cv.wait(lock, [currentThread]() {
        return currentThread->state != OS_THREAD_STATE_WAITING;
    });
}

void OSWakeupThread(OSThreadQueue* queue) {
    if (!queue) {
        return;
    }

    // Wake all threads in the queue
    OSThread* thread = queue->head;
    while (thread) {
        OSThread* next = thread->link.next;
        thread->state = OS_THREAD_STATE_READY;
        thread->link.next = nullptr;
        thread->link.prev = nullptr;
        thread->queue = nullptr;
        thread = next;
    }
    queue->head = queue->tail = nullptr;

    // Notify all waiters
    std::condition_variable& cv = GetQueueCV(queue);
    cv.notify_all();
}

s32 OSSetThreadPriority(OSThread* thread, s32 priority) {
    if (!thread) {
        return false;
    }
    if (priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
        return false;
    }
    thread->base_priority = priority;
    thread->effective_priority = priority;
    return true;
}
s32 OSGetThreadPriority(OSThread* thread) {
    if (!thread) {
        return 16;
    }
    return thread->base_priority;
}

s32 OSCheckActiveThreads() {
    return sActiveThreadCount.load();
}

void OSSetCurrentThreadName(const char* name) {
    wchar_t buffer[256];
    mbstowcs_s(NULL, buffer, name, sizeof(buffer));
    SetThreadDescription(GetCurrentThread(), buffer);
}
