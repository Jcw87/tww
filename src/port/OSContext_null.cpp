
#include "global.h"
#include "dolphin/os/OS.h"
#include <intrin.h>


OSContext* __OSCurrentContext;

void OSSaveFPUContext(OSContext* context) {
	NOT_IMPLEMENTED;
}

void OSSetCurrentContext(OSContext* context) {
	__OSCurrentContext = context;
}

OSContext* OSGetCurrentContext() {
	return __OSCurrentContext;
}

u32 OSSaveContext(OSContext* context) {
	NOT_IMPLEMENTED;
	return 0;
}

void OSLoadContext(OSContext* context) {
	NOT_IMPLEMENTED;
}

u8* OSGetStackPointer() {
	u32* addr = (u32*)_AddressOfReturnAddress();
	addr--;
	return (u8*)addr;
}

void OSClearContext(OSContext* context) {}

void OSInitContext(OSContext* context, u32 param_2, u32 param_3) {
	NOT_IMPLEMENTED;
}

void OSDumpContext(OSContext* context) {
	OSReport("------------------------- Context 0x%08x -------------------------\n", context);
	NOT_IMPLEMENTED;
}

void OSFillFPUContext(OSContext* context) {
	NOT_IMPLEMENTED;
}
