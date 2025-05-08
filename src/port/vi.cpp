
#include "global.h"
#include <dolphin/vi/vi.h>
#include <dolphin/os/OS.h>

const char* __VIVersion = "<< Dolphin SDK - VI\trelease build: " __DATE__ " " __TIME__ " (0x2301) >>";

static BOOL IsInitialized;
static volatile u32 retraceCount;
static OSThreadQueue retraceQueue;
static VIRetraceCallback PreCB;
static VIRetraceCallback PostCB;

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
}

void VIWaitForRetrace() {
    retraceCount++;
    if (PreCB) {
        PreCB(retraceCount);
    }
    if (PostCB) {
        PostCB(retraceCount);
    }
}

void VIConfigure(GXRenderModeObj*) { NOT_IMPLEMENTED_CONTINUE; }
void VIFlush() { NOT_IMPLEMENTED_CONTINUE; }
void VISetNextFrameBuffer(void*) { NOT_IMPLEMENTED_CONTINUE; }
void VISetBlack(BOOL) { NOT_IMPLEMENTED_CONTINUE; }
u32 VIGetRetraceCount() { return retraceCount; }
u32 VIGetNextField() { NOT_IMPLEMENTED; return 0; }
u32 VIGetTvFormat() { NOT_IMPLEMENTED; return 0; }
u32 VIGetDTVStatus() { NOT_IMPLEMENTED_CONTINUE; return 0; }
