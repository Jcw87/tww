
#include <dolphin/os/OSMutex.h>

#include <condition_variable>
#include <mutex>
#include <unordered_map>

// ============================================================================
// Side-table: native mutex per OSMutex
// ============================================================================

struct PCMutexData {
    std::recursive_mutex nativeMutex;
};

static std::mutex& GetMutexMapMutex() {
    static std::mutex mtx;
    return mtx;
}

static std::unordered_map<OSMutex*, std::unique_ptr<PCMutexData>>& GetMutexMap() {
    static std::unordered_map<OSMutex*, std::unique_ptr<PCMutexData>> map;
    return map;
}

static PCMutexData& GetMutexData(OSMutex* mutex) {
    std::lock_guard<std::mutex> lock(GetMutexMapMutex());
    auto& map = GetMutexMap();
    auto it = map.find(mutex);
    if (it == map.end()) {
        auto result = map.emplace(mutex, std::make_unique<PCMutexData>());
        return *result.first->second;
    }
    return *it->second;
}

// ============================================================================
// Side-table: native condition variable per OSCond
// ============================================================================

struct PCCondData {
    std::condition_variable_any cv;
};

static std::mutex& GetCondMapMutex() {
    static std::mutex mtx;
    return mtx;
}

static std::unordered_map<OSCond*, std::unique_ptr<PCCondData>>& GetCondMap() {
    static std::unordered_map<OSCond*, std::unique_ptr<PCCondData>> map;
    return map;
}

static PCCondData& GetCondData(OSCond* cond) {
    std::lock_guard<std::mutex> lock(GetCondMapMutex());
    auto& map = GetCondMap();
    auto it = map.find(cond);
    if (it == map.end()) {
        auto result = map.emplace(cond, std::make_unique<PCCondData>());
        return *result.first->second;
    }
    return *it->second;
}

void ClearCondMap() {
    std::lock_guard<std::mutex> lock(GetCondMapMutex());
    auto& map = GetCondMap();
    for (auto& pair : map) {
        pair.second->cv.notify_all();
    }
    map.clear();
}

// ============================================================================
// C API functions
// ============================================================================

void OSInitMutex(OSMutex* mutex) {
    if (!mutex) {
        return;
    }

    OSInitThreadQueue(&mutex->queue);
    mutex->thread = nullptr;
    mutex->count = 0;

    // Create/reset side-table entry
    GetMutexData(mutex);
}
void OSLockMutex(OSMutex* mutex) {
    if (!mutex) {
        return;
    }

    PCMutexData& data = GetMutexData(mutex);
    data.nativeMutex.lock();

    // Update GC-visible fields
    OSThread* currentThread = OSGetCurrentThread();
    mutex->thread = currentThread;
    mutex->count++;
}

void OSUnlockMutex(OSMutex* mutex) {
    if (!mutex) {
        return;
    }

    OSThread* currentThread = OSGetCurrentThread();
    if (mutex->thread != currentThread)
        return;

    mutex->count--;
    if (mutex->count == 0) {
        mutex->thread = nullptr;
    }

    PCMutexData& data = GetMutexData(mutex);
    data.nativeMutex.unlock();
}

BOOL OSTryLockMutex(OSMutex* mutex) {
    if (!mutex) {
        return false;
    }

    PCMutexData& data = GetMutexData(mutex);
    if (data.nativeMutex.try_lock()) {
        OSThread* currentThread = OSGetCurrentThread();
        mutex->thread = currentThread;
        mutex->count++;
        return true;
    }
    return false;
}

// ============================================================================
// Condition Variable API
// ============================================================================

void OSInitCond(OSCond* cond) {
    if (!cond) {
        return;
    }

    OSInitThreadQueue(&cond->queue);
    GetCondData(cond);
}

void OSWaitCond(OSCond* cond, OSMutex* mutex) {
    if (!cond || !mutex) {
        return;
    }

    PCCondData& condData = GetCondData(cond);
    PCMutexData& mutexData = GetMutexData(mutex);

    // Save and clear the GC mutex state
    OSThread* currentThread = OSGetCurrentThread();
    s32 savedCount = mutex->count;
    mutex->count = 0;
    mutex->thread = nullptr;

    // Keep one recursion level held so cv.wait() is what releases the mutex;
    // fully unlocking before the wait opens a window where a signal is lost.
    if (savedCount >= 1) {
        for (s32 i = 1; i < savedCount; i++) {
            mutexData.nativeMutex.unlock();
        }
        std::unique_lock lock(mutexData.nativeMutex, std::adopt_lock);
        condData.cv.wait(lock);
        lock.release();
        for (s32 i = 1; i < savedCount; i++) {
            mutexData.nativeMutex.lock();
        }
    } else {
        // Mutex wasn't held on entry (contract violation); wait anyway.
        std::unique_lock lock(mutexData.nativeMutex);
        condData.cv.wait(lock);
    }

    // Restore GC mutex state
    mutex->thread = currentThread;
    mutex->count = savedCount;
}

void OSSignalCond(OSCond* cond) {
    if (!cond) {
        return;
    }

    PCCondData& condData = GetCondData(cond);
    condData.cv.notify_all();
}
