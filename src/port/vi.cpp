
#include "global.h"
#include <dolphin/vi/vi.h>
#include <dolphin/os/OS.h>

const char* __VIVersion = "<< Dolphin SDK - VI\trelease build: " __DATE__ " " __TIME__ " (0x2301) >>";

static BOOL IsInitialized;
static volatile u32 retraceCount;
static OSThreadQueue retraceQueue;
static VIRetraceCallback PreCB;
static VIRetraceCallback PostCB;

OSAlarm RetraceAlarm;

void __VIRetraceHandler(OSAlarm* alarm, OSContext* context) {
	retraceCount++;
	if (PreCB) {
		//PreCB(retraceCount);
	}
	if (PostCB) {
		PostCB(retraceCount);
	}
	OSWakeupThread(&retraceQueue);
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb) {
	VIRetraceCallback oldcb = PreCB;
	BOOL enabled = OSDisableInterrupts();
	PreCB = cb;
	OSRestoreInterrupts(enabled);
	return oldcb;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb) {
	VIRetraceCallback oldcb = PostCB;
	BOOL enabled = OSDisableInterrupts();
	PostCB = cb;
	OSRestoreInterrupts(enabled);
	return oldcb;
}

void VIInit() {
	if (IsInitialized != 0) {
		return;
	}
	OSRegisterVersion(__VIVersion);
	IsInitialized = 1;

	retraceCount = 0;
	OSInitThreadQueue(&retraceQueue);
	OSTime period = OSMicrosecondsToTicks(1000 * 1000 / 60);
	OSCreateAlarm(&RetraceAlarm);
	OSSetPeriodicAlarm(&RetraceAlarm, OSGetTime() + period, period, &__VIRetraceHandler);
}

void VIWaitForRetrace(void) {
	bool level = OSDisableInterrupts();
	u32 oldCount = retraceCount;
	while (oldCount == retraceCount) {
		OSSleepThread(&retraceQueue);
	}
	OSRestoreInterrupts(level);
}

void VIConfigure(GXRenderModeObj*) { NOT_IMPLEMENTED_CONTINUE; }
void VIFlush() { NOT_IMPLEMENTED_CONTINUE; }
void VISetNextFrameBuffer(void*) { NOT_IMPLEMENTED_CONTINUE; }
void VISetBlack(BOOL) { NOT_IMPLEMENTED_CONTINUE; }
u32 VIGetRetraceCount() { return retraceCount; }
u32 VIGetNextField() { NOT_IMPLEMENTED; return 0; }
u32 VIGetTvFormat() { NOT_IMPLEMENTED; return 0; }
u32 VIGetDTVStatus() { NOT_IMPLEMENTED_CONTINUE; return 0; }
