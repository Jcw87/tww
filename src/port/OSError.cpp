
#include <dolphin/os/OS.h>
#include "stdarg.h"
#include "stdio.h"

u32 __OSFpscrEnableBits;

#if 0
void OSReport(const char* msg, ...) {
    va_list marker;
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
}

void OSPanic(const char* file, s32 line, const char* msg, ...) {
    va_list marker;
    u32 i;
    uintptr_t* p;

    OSDisableInterrupts();
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (uintptr_t*)OSGetStackPointer(); p && (uintptr_t)p != 0xffffffff && i++ < 16; p = (uintptr_t*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }

    PPCHalt();
}
#endif

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler) { return NULL; }
