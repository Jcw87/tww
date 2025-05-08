
#include "global.h"
#include "dolphin/gba/GBA.h"

void GBAInit(void) { NOT_IMPLEMENTED_CONTINUE; }
s32 GBAGetStatusAsync(s32 chan, u8* status, GBACallback callback) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAGetStatus(s32 chan, u8* status) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAResetAsync(s32 chan, u8* status, GBACallback callback) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAReset(s32 chan, u8* status) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAGetProcessStatus(s32 chan, u8* percentp) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAJoyBootAsync(s32 chan, s32 palette_color, s32 palette_speed, u8* programp, s32 length, u8* status, GBACallback callback) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAJoyBoot(s32 chan, s32 palette_color, s32 palette_speed, u8* programp, s32 length, u8* status) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAReadAsync(s32 chan, u8* dst, u8* status, GBACallback callback) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBARead(s32 chan, u8* dst, u8* status) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAWriteAsync(s32 chan, u8* src, u8* status, GBACallback callback) { NOT_IMPLEMENTED_CONTINUE; return 0; }
s32 GBAWrite(s32 chan, u8* src, u8* status) { NOT_IMPLEMENTED_CONTINUE; return 0; }
