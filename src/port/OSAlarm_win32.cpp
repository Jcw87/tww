
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSInterrupt.h>

#include <mutex>
#include <unordered_map>

#if _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

// ============================================================================
// Side-table: native timer per OSAlarm
// ============================================================================

struct PCAlarmData {
    HANDLE timer;
};

static std::mutex& GetAlarmMapMutex() {
    static std::mutex mtx;
    return mtx;
}

static std::unordered_map<OSAlarm*, std::unique_ptr<PCAlarmData>>& GetAlarmMap() {
    static std::unordered_map<OSAlarm*, std::unique_ptr<PCAlarmData>> map;
    return map;
}

static PCAlarmData& GetAlarmData(OSAlarm* alarm) {
    std::lock_guard<std::mutex> lock(GetAlarmMapMutex());
    auto& map = GetAlarmMap();
    auto it = map.find(alarm);
    if (it == map.end()) {
        auto result = map.emplace(alarm, std::make_unique<PCAlarmData>());
        return *result.first->second;
    }
    return *it->second;
}

static size_t RemoveAlarmData(OSAlarm* alarm) {
    std::lock_guard<std::mutex> lock(GetAlarmMapMutex());
    auto& map = GetAlarmMap();
    return map.erase(alarm);
}

HANDLE TimerQueue;
HANDLE KernelThread;

extern volatile bool InterruptEnable;

void __stdcall DecrementerExceptionHandler(PVOID ptr, BOOLEAN waited) {
	OSAlarm* alarm = (OSAlarm*)ptr;
	alarm->handler(alarm, NULL);
}

void OSInitAlarm() {
	TimerQueue = CreateTimerQueue();
	HANDLE process = GetCurrentProcess();
	DuplicateHandle(process, GetCurrentThread(), process, &KernelThread, 0, false, DUPLICATE_SAME_ACCESS);
}

void OSCreateAlarm(OSAlarm* alarm) {
	alarm->handler = NULL;
    alarm->tag = 0;

	// Create/reset side-table entry
    GetAlarmData(alarm);
}

void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler) {
    alarm->period_time = 0;
	alarm->handler = handler;
    PCAlarmData& data = GetAlarmData(alarm);
	if (data.timer) {
        DeleteTimerQueueTimer(TimerQueue, data.timer, INVALID_HANDLE_VALUE);
	}
	CreateTimerQueueTimer(&data.timer, TimerQueue, &DecrementerExceptionHandler, alarm, OSTicksToMilliseconds(tick), 0, WT_EXECUTEINTIMERTHREAD);
}

void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler) {
    OSTime time = start - OSGetTime() + period;
    if (time < 0) {
        time = 0;
    }
    alarm->period_time = period;
	alarm->handler = handler;
    PCAlarmData& data = GetAlarmData(alarm);
	if (data.timer) {
        DeleteTimerQueueTimer(TimerQueue, data.timer, INVALID_HANDLE_VALUE);
	}
	CreateTimerQueueTimer(&data.timer, TimerQueue, &DecrementerExceptionHandler, alarm, OSTicksToMilliseconds(time), OSTicksToMilliseconds(period), WT_EXECUTEINTIMERTHREAD);
}

void OSCancelAlarm(OSAlarm* alarm) {
    PCAlarmData& data = GetAlarmData(alarm);
    if (data.timer) {
        DeleteTimerQueueTimer(TimerQueue, data.timer, INVALID_HANDLE_VALUE);
    }
    RemoveAlarmData(alarm);
	alarm->handler = NULL;
}