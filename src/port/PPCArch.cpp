
#include "global.h"
#include <dolphin/base/PPCArch.h>
#include "stdlib.h"
#include <bit>

int __cntlzw(uint value) {
    return std::countl_zero(value);
}

void __dcbz(void*, int) {
}

u32 PPCMfmsr() { return 0; }
void PPCMtmsr(u32 newMSR) { }
void PPCSync() { }
void PPCHalt() { abort(); }
u32 PPCMfhid2() { NOT_IMPLEMENTED; return 0; }
