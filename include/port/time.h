#pragma once

#include <SDL3/SDL_timer.h>

#include <array>
#include <numeric>

class Limiter {
public:
    using duration_t = Uint64;

    void Reset() { 
        m_oldTime = SDL_GetTicksNS(); 
    }

    duration_t Sleep(duration_t targetFrameTime) {
        if (targetFrameTime == 0) {
            return 0;
        }

        const Uint64 start = SDL_GetTicksNS();
        duration_t adjustedSleepTime = SleepTime(targetFrameTime);
        if (adjustedSleepTime > 0) {
            NanoSleep(adjustedSleepTime);
            const duration_t elapsed = TimeSince(start);
            const duration_t overslept = elapsed > adjustedSleepTime ? elapsed - adjustedSleepTime : 0;
            if (overslept < targetFrameTime) {
                m_overheadTimes[m_overheadTimeIdx] = overslept;
                m_overheadTimeIdx = (m_overheadTimeIdx + 1) % m_overheadTimes.size();
            }
        }
        Reset();

        return adjustedSleepTime;
    }

    duration_t SleepTime(duration_t targetFrameTime) {
        const duration_t elapsed = TimeSince(m_oldTime);
        const duration_t sleepTime = elapsed < targetFrameTime ? targetFrameTime - elapsed : 0;
        m_overhead = std::accumulate(m_overheadTimes.begin(), m_overheadTimes.end(), duration_t{0}) / m_overheadTimes.size();
        if (sleepTime > m_overhead) {
            return sleepTime - m_overhead;
        }
        return 0;
    }
    
private:
    Uint64 m_oldTime = 0;
    std::array<duration_t, 4> m_overheadTimes{};
    size_t m_overheadTimeIdx = 0;
    duration_t m_overhead = 0;

    duration_t TimeSince(Uint64 start) const { return SDL_GetTicksNS() - start; }

    void NanoSleep(const duration_t duration);
};
