
#include <dolphin/os/OS.h>

u32 OSGetConsoleSimulatedMemSize() {
    OSBootInfo* info = (OSBootInfo*)OSPhysicalToCached(0);
    return info->memory_size;
}

void OSProtectRange(u32 channel, void* address, u32 nBytes, u32 control) {
    NOT_IMPLEMENTED;
}
