
#include "global.h"
#include <dolphin/os/OSReset.h>

void OSRegisterResetFunction(OSResetFunctionInfo* info) {
    NOT_IMPLEMENTED;
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu) {
    NOT_IMPLEMENTED;
}

u32 OSGetResetCode() {
    NOT_IMPLEMENTED_CONTINUE;
    return 0;
}
