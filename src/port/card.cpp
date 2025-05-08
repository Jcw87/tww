
#include "global.h"
#include "dolphin/card.h"

void CARDInit() { NOT_IMPLEMENTED_CONTINUE; }
s32 CARDFreeBlocks(s32, s32*, s32*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDCheck(s32) { NOT_IMPLEMENTED_CONTINUE; return 0; }
BOOL CARDProbe(s32) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDProbeEx(s32, s32*, s32*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDMount(s32, void*, CARDCallback) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDUnmount(s32) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDFormat(s32) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDOpen(s32, const char*, CARDFileInfo*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDClose(CARDFileInfo*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDCreate(s32, const char*, u32, CARDFileInfo*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDRead(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDWrite(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDGetStatus(s32, s32, CARDStat*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDSetStatus(s32, s32, CARDStat*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 CARDGetSerialNo(s32, u64*) { NOT_IMPLEMENTED_CONTINUE; return 0; }
