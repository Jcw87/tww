

#include "dolphin/os/OSInterrupt.h"

#include "dolphin/os/OSTime.h"
#include <chrono>

struct gc_clock
{
    using duration = std::chrono::microseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<gc_clock>;
    static const bool is_steady = false;

    static time_point now() noexcept {
        using namespace std::chrono;
        return time_point { duration_cast<duration>(system_clock::now() - sys_days{January / 1 / 2000}) };
    }
};

// End of each month in standard year
static int YearDays[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
// End of each month in leap year
static int LeapYearDays[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

OSTick OSGetTick() {
    return (OSTick)OSGetTime();
}

OSTime OSGetTime() {
    BOOL level = OSDisableInterrupts();
    const auto now = gc_clock::now();
    // 162 comes from 1/3 the Gamecube clockspeed (486 MHz)
    return (now.time_since_epoch().count() * 162ull) / 4ull;
}

static int IsLeapYear(int year) { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }

static int GetYearDays(int year, int mon) {
  int* md = (IsLeapYear(year)) ? LeapYearDays : YearDays;

  return md[mon];
}

static int GetLeapDays(int year) {
  if (year < 1) {
    return 0;
  }
  return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

static void GetDates(int days, OSCalendarTime* td) {
  int year;
  int n;
  int month;
  int* md;

  td->week_day = (days + 6) % 7;

  for (year = days / 365; days < (n = year * 365 + GetLeapDays(year)); year--) {}

  days -= n;
  td->year = year;
  td->year_day = days;

  md = IsLeapYear(year) ? LeapYearDays : YearDays;
  for (month = 12; days < md[--month];) {
    ;
  }
  td->month = month;
  td->day_of_month = days - md[month] + 1;
}

void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td) {
    int days;
    int secs;
    OSTime d;

    d = ticks % OSSecondsToTicks(1);
    if (d < 0) {
        d += OSSecondsToTicks(1);
    }

    td->microseconds = OSTicksToMicroseconds(d) % 1000;
    td->milliseconds = OSTicksToMilliseconds(d) % 1000;

    ticks -= d;

    days = (OSTicksToSeconds(ticks) / (60 * 60 * 24)) + 0xB2575;
    secs = OSTicksToSeconds(ticks) % (60 * 60 * 24);
    if (secs < 0) {
        days -= 1;
        secs += (60 * 60 * 24);
    }

    GetDates(days, td);
    td->hours = secs / 60 / 60;
    td->minutes = secs / 60 % 60;
    td->seconds = secs % 60;
}

OSTime OSCalendarTimeToTicks(OSCalendarTime* td) {
    OSTime secs;
    int ov_mon;
    int mon;
    int year;

    ov_mon = td->month / 12;
    mon = td->month - (ov_mon * 12);

    if (mon < 0) {
        mon += 12;
        ov_mon--;
    }

    year = td->year + ov_mon;

    secs = OSTime(60 * 60 * 24 * 365) * td->year + 
        OSTime(60 * 60 * 24) * (GetLeapDays(year) + GetYearDays(year, mon) + td->day_of_month - 1) +
        OSTime(60 * 60) * td->hours + 
        OSTime(60) * td->minutes + 
        td->seconds -
        OSTime(0xEB1E1BF80ULL);

    return OSSecondsToTicks(secs) + OSMillisecondsToTicks((s64)td->milliseconds) + OSMicrosecondsToTicks((s64)td->microseconds);
}