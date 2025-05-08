
#include "global.h"
#include <dolphin/ar/arq.h>
#include <dolphin/os/OS.h>

#include "string.h"

extern void* __AR_RAM;

const char* __ARQVersion = "<< Dolphin SDK - ARQ\trelease build: " __DATE__ " " __TIME__ " (0x2301) >>";

static BOOL __ARQ_init_flag;

void ARQInit() {
	if (__ARQ_init_flag != 1) {
		OSRegisterVersion(__ARQVersion);
		__ARQ_init_flag = 1;
	}
}
void ARQPostRequest(ARQRequest* task, u32 owner, u32 type, u32 priority, u32 source, u32 destination, u32 length, ARQCallback callback) {
    if (type == ARAM_DIR_MRAM_TO_ARAM) {
        void* ram = (void*)source;
        void* aram = (u8*)__AR_RAM + destination;
        memcpy(aram, ram, length);
    } else if (type == ARAM_DIR_ARAM_TO_MRAM) {
        void* ram = (void*)destination;
        void* aram = (u8*)__AR_RAM + source;
        memcpy(ram, aram, length);
    } else {
        OSPanic(__FILE__, __LINE__, "ARQPostRequest: invalid type");
    }

    callback((u32)task);
}
