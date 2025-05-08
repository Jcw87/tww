
#include "global.h"
#include <dolphin/ar/ar.h>
#include <dolphin/os/OS.h>
#include <stdlib.h>

const char* __ARVersion = "<< Dolphin SDK - AR\trelease build: " __DATE__ " " __TIME__ " (0x2301) >>";

static ARCallback __AR_Callback;
static u32 __AR_Size;
static u32 __AR_InternalSize;
static u32 __AR_ExpansionSize;
static u32 __AR_StackPointer;
static u32 __AR_FreeBlocks;
static u32* __AR_BlockLength;
static BOOL __AR_init_flag;

void* __AR_RAM = NULL;

static void __ARChecksize(void);

u32 ARAlloc(u32 length) {
	BOOL old = OSDisableInterrupts();
	u32 tmp = __AR_StackPointer;
	__AR_StackPointer += length;
	*__AR_BlockLength = length;
	__AR_BlockLength++;
	__AR_FreeBlocks--;
	OSRestoreInterrupts(old);
	return tmp;
}

u32 ARInit(u32* stack_index_addr, u32 num_entries) {
	if (__AR_init_flag == 1) {
		return 0x00004000;
	}

	OSRegisterVersion(__ARVersion);

	BOOL old = OSDisableInterrupts();
	__AR_Callback = NULL;
	__AR_StackPointer = 0x00004000;
	__AR_FreeBlocks = num_entries;
	__AR_BlockLength = stack_index_addr;

	__ARChecksize();
	__AR_init_flag = 1;
	OSRestoreInterrupts(old);
	return __AR_StackPointer;
}
u32 ARGetBaseAddress() { return 0x4000; }
u32 ARGetSize() { return __AR_Size; }

void __ARChecksize() {
	if (!__AR_RAM) {
		__AR_Size = 1024 * 1024 * 16;
		__AR_RAM = malloc(__AR_Size);
	}
}
