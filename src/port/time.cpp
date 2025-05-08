#include "port/time.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <shellapi.h>
#include <intrin.h>
#endif
#ifdef __APPLE__
#include <mach/mach_time.h>
#if defined(__x86_64__) || defined(__i386__)
#include <immintrin.h>
#endif
#endif

#if _WIN32
void Limiter::NanoSleep(const duration_t duration) {
    static bool initialized = false;
    static double countPerNs;
    static size_t numSleeps = 0;

    // QueryPerformanceFrequency's result is constant, but calling it occasionally
    // appears to stabilize QueryPerformanceCounter. Without it, the game drifts
    // from 60hz to 144hz. (Cursed, but I suspect it's NVIDIA/G-SYNC related)
    if (!initialized || numSleeps++ % 1000 == 0) {
        LARGE_INTEGER freq;
        if (QueryPerformanceFrequency(&freq) == 0) {
            return;
        }
        countPerNs = static_cast<double>(freq.QuadPart) / 1e9;
        initialized = true;
        numSleeps = 0;
    }

    LARGE_INTEGER start, current;
    QueryPerformanceCounter(&start);
    const LONGLONG ticksToWait = static_cast<LONGLONG>(duration * countPerNs);
    const Uint64 ms = duration / 1'000'000ULL;
    if (ms > 1) {
        ::Sleep(static_cast<DWORD>(ms - 1));
    }
    do {
        QueryPerformanceCounter(&current);
#if defined(_M_ARM64) || defined(_M_ARM)
        __yield();
#else
        _mm_pause();
#endif
    } while (current.QuadPart - start.QuadPart < ticksToWait);
}
#elif defined (__APPLE__)
void Limiter::NanoSleep(const duration_t duration) {
    // Hybrid approach using Apple Mach
    uint64_t start_mach = mach_absolute_time();

    mach_timebase_info_data_t timebase_info;
    mach_timebase_info(&timebase_info);

    uint64_t total_mach_ticks = (duration * timebase_info.denom) / timebase_info.numer;
    uint64_t target_mach = start_mach + total_mach_ticks;

    uint64_t buffer_ns = 2'000'000ULL;
    uint64_t buffer_mach_ticks = (buffer_ns * timebase_info.denom) / timebase_info.numer;

    if (total_mach_ticks > buffer_mach_ticks) {
        uint64_t sleep_until_mach = target_mach - buffer_mach_ticks;
        mach_wait_until(sleep_until_mach);
    }

    while (mach_absolute_time() < target_mach) {
#if defined(__aarch64__) || defined(__arm__)
        asm volatile("yield" ::: "memory");  // Hardware hint, not a scheduler hint.
#else
        _mm_pause();
#endif
    }
}
#else
void Limiter::NanoSleep(const duration_t duration) { SDL_DelayPrecise(duration); }
#endif
