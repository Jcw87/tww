
#include "dolphin/os/OSContext.h"

#include "dolphin/os/OSInterrupt.h"

volatile BOOL InterruptEnable;

BOOL OSDisableInterrupts() {
    BOOL prev = InterruptEnable;
	InterruptEnable = false;
	return prev;
}
BOOL OSEnableInterrupts() {
    BOOL prev = InterruptEnable;
	InterruptEnable = true;
	return prev;
}
BOOL OSRestoreInterrupts(BOOL level) {
    BOOL prev = InterruptEnable;
	InterruptEnable = level;
	return prev;
}
