
#include "global.h"
#include <dolphin/os/OSThread.h>

#include <condition_variable>
#include <mutex>
#include <thread>
#include <unordered_map>

#if _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#elif __APPLE__
#include <pthread.h>
#endif

// ============================================================================
// Side-table: native thread data per OSThread
// ============================================================================

struct PCThreadData {
    std::thread nativeThread;
    std::mutex mtx;
    std::condition_variable cv;
    void* (*func)(void*);
    void* param;
    bool started = false;
    bool suspended = false;
};

// Lazy-initialized to avoid DLL static init crashes (used before DllMain completes)
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

static OSThread DefaultThread;
static u8 sDefaultStack[64 * 1024];
static u8 sDefaultStackEnd = OS_THREAD_STACK_MAGIC;

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

OSSwitchThreadCallback OSSetSwitchThreadCallback(OSSwitchThreadCallback callback) {
    OSSwitchThreadCallback prev = sSwitchThreadCallback;
    sSwitchThreadCallback = callback;
    return prev;
}

static inline void OSSetCurrentThread(OSThread* thread) {
    __OSCurrentThread = thread;
}

void __OSThreadInit(void) {
    memset(&DefaultThread, 0, sizeof(OSThread));

    DefaultThread.state = OS_THREAD_STATE_RUNNING;
    DefaultThread.attributes = OS_THREAD_ATTR_DETACH;
    DefaultThread.effective_priority = 16;
    DefaultThread.base_priority = 16;
    DefaultThread.suspend_count = 0;
    DefaultThread.exit_value = (void*)(intptr_t)-1;
    DefaultThread.mutex = nullptr;
    DefaultThread.queue = nullptr;

    OSInitThreadQueue(&DefaultThread.join_queue);
    DefaultThread.owned_mutexes.head = DefaultThread.owned_mutexes.tail = nullptr;
    DefaultThread.link.next = DefaultThread.link.prev = nullptr;
    DefaultThread.active_threads_link.next = DefaultThread.active_threads_link.prev = nullptr;

    // Stack pointers (JKRThread reads these)
    DefaultThread.stack_base = sDefaultStack + sizeof(sDefaultStack);
    DefaultThread.stack_end = (u32*)&sDefaultStackEnd;
    sDefaultStackEnd = OS_THREAD_STACK_MAGIC;

    OSClearContext(&DefaultThread.context);

    DefaultThread.error_code = 0;
    DefaultThread.data[0] = nullptr;
    DefaultThread.data[1] = nullptr;

    // Set as current thread for main thread
    __OSCurrentThread = &DefaultThread;

    // Active queue
    sActiveThreadCount = 1;

    OSReport("[PC-OSThread] Thread system initialized (multi-threaded mode)\n");
}

void OSInitMutexQueue(OSMutexQueue* queue) {
    if (queue) {
        queue->head = queue->tail = NULL;
    }
}

void OSInitThreadQueue(OSThreadQueue* queue) {
    if (queue) {
        queue->head = queue->tail = NULL;
    }
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
    return (thread->state == OS_THREAD_STATE_DEAD || thread->state == OS_THREAD_STATE_UNINITIALIZED) ? TRUE : FALSE;
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

int OSCreateThread(OSThread* thread, void* (*func)(void*), void* param,
                   void* stack, u32 stackSize, OSPriority priority, u16 attr) {
    if (!thread) {
        return 0;
    }
    if (priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
        return 0;
    }

    // Ensure thread system is initialized
    OSGetCurrentThread();

    memset(thread, 0, sizeof(OSThread));

    thread->state = OS_THREAD_STATE_READY;
    thread->attributes = attr & 1u;
    thread->base_priority = priority;
    thread->effective_priority = priority;
    thread->suspend_count  = 1;  // Created suspended (GC behavior)
    thread->exit_value = (void*)(intptr_t)-1;
    thread->mutex = nullptr;

    OSInitThreadQueue(&thread->join_queue);
    thread->owned_mutexes.head = thread->owned_mutexes.tail = nullptr;
    thread->link.next = thread->link.prev = nullptr;
    thread->active_threads_link.next = thread->active_threads_link.prev = nullptr;

    // Stack (stack points to TOP on GameCube)
    thread->stack_base = (u8*)stack;
    thread->stack_end = (u32*)((uintptr_t)stack - stackSize);
    *thread->stack_end = OS_THREAD_STACK_MAGIC;

    OSClearContext(&thread->context);

    thread->error_code = 0;
    thread->data[0] = nullptr;
    thread->data[1] = nullptr;

    // Create side-table entry (but don't start the thread yet)
    {
        auto data = std::make_unique<PCThreadData>();
        data->func  = func;
        data->param = param;

        std::lock_guard<std::mutex> lock(GetThreadDataMutex());
        GetThreadDataMap()[thread] = std::move(data);
    }

    // Add to active queue
    sActiveThreadCount++;

    OSReport("[PC-OSThread] Created thread %p (priority=%d, stackSize=%u)\n", thread, priority, stackSize);
    return 1;
}

void OSExitThread(void* val) {
    OSThread* currentThread = OSGetCurrentThread();
    if (!currentThread) return;

    currentThread->exit_value = val;

    if (currentThread->attributes & OS_THREAD_ATTR_DETACH) {
        currentThread->state = 0;
    } else {
        currentThread->state = OS_THREAD_STATE_DEAD;
    }

    // Wake anyone waiting to join
    OSWakeupThread(&currentThread->join_queue);
    sActiveThreadCount--;
}

void OSCancelThread(OSThread* thread) {
    NOT_IMPLEMENTED;
}

BOOL OSJoinThread(OSThread* thread, void* val) {
    if (!thread) {
        return 0;
    }

    if (!(thread->attributes & OS_THREAD_ATTR_DETACH)) {
        GetThreadData(thread)->nativeThread.join();
    }

    if (thread->state == OS_THREAD_STATE_DEAD) {
        if (val) {
            *(s32*)val = (s32)(intptr_t)thread->exit_value;
        }
        thread->state = 0;
        return 1;
    }
    return 0;
}

void OSDetachThread(OSThread* thread) {
    NOT_IMPLEMENTED;
}

s32 OSResumeThread(OSThread* thread) {
    if (!thread)
        return 0;

    s32 prevSuspend = thread->suspend_count;
    if (thread->suspend_count > 0) {
        thread->suspend_count--;
    }

    // Only wake up if suspend count drops to 0
    if (thread->suspend_count == 0) {
        PCThreadData* data = GetThreadData(thread);

        if (data) {
            // Lock the specific thread mutex to safely modify state and notify
            std::unique_lock<std::mutex> threadLock(data->mtx);

            if (!data->started) {
                // First resume: launch the native thread
                data->started = true;
                data->suspended = false;

                // Unlock before launching to avoid potential deadlocks in thread initialization
                threadLock.unlock();

                data->nativeThread = std::thread(ThreadEntryWrapper, thread, data);
                OSReport("[PC-OSThread] Started thread %p\n", thread);
            } else {
                // Resume from suspension: signal the condition variable
                // IMPORTANT: Set suspended to false BEFORE notifying to pass the wait predicate
                data->suspended = false;
                data->cv.notify_all();
            }
        }
    }

    return prevSuspend;
}

s32 OSSuspendThread(OSThread* thread) {
    if (!thread)
        return 0;

    s32 prevSuspend = thread->suspend_count;
    thread->suspend_count++;

    // If transitioning from running (0) to suspended (1)
    if (prevSuspend == 0) {
        PCThreadData* data = GetThreadData(thread);

        if (data && data->started) {
            std::unique_lock<std::mutex> threadLock(data->mtx);
            data->suspended = true;

            // FIX: If the thread is suspending ITSELF, we must block execution here.
            // This replicates the GameCube behavior where OSSuspendThread yields the CPU
            // immediately.
            if (thread == OSGetCurrentThread()) {
                // Block until 'suspended' becomes false (set by OSResumeThread)
                // The predicate protects against spurious wakeups.
                data->cv.wait(threadLock, [data] { return !data->suspended; });
            } else {
                // NOTE: Suspending *other* threads is difficult in C++ std::thread
                // without cooperative checkpoints or platform-specific hacks.
                // For now, we only set the flag. The target thread would need to check 'suspended'
                // periodically.
            }
        }
    }

    return prevSuspend;
}

void OSSleepThread(OSThreadQueue* queue) {
    if (!queue) return;

    OSThread* currentThread = OSGetCurrentThread();
    if (!currentThread) return;

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
#if _WIN32
    wchar_t buffer[256];
    mbstowcs_s(NULL, buffer, name, sizeof(buffer));
    SetThreadDescription(GetCurrentThread(), buffer);
#elif __APPLE__
    pthread_setname_np(name);
#endif
}