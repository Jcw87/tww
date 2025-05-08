
#include <string.h>

#include <dolphin/os/OSCache.h>

void DCInvalidateRange(void* param_1, u32 param_2) { }
void DCFlushRange(void* param_1, u32 param_2) { }
void DCStoreRange(void* param_1, u32 param_2) { }
void DCFlushRangeNoSync(void* param_1, u32 param_2) { }
void DCStoreRangeNoSync(void* param_1, u32 param_2) { }
void DCZeroRange(void* param_1, u32 param_2) { memset(param_1, 0, param_2); }
void ICInvalidateRange(void* param_1, u32 param_2) { }
void LCEnable() { }
void LCDisable() { }
void LCStoreBlocks(void* destAddr, void* srcAddr, u32 blockNum) { }
u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes) { return 0; }
void LCQueueWait(u32 len) { }
