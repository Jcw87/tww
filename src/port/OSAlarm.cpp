
#include <dolphin/os/OSAlarm.h>

void OSInitAlarm() {}
void OSCreateAlarm(OSAlarm* alarm) {}
void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler) {}
void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler) {}
void OSCancelAlarm(OSAlarm* alarm) {}
