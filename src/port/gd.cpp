
#include "global.h"
#include "dolphin/gd/GDBase.h"
#include "dolphin/gd/GDGeometry.h"
#include "dolphin/os/OSCache.h"

GDLObj* __GDCurrentDL = NULL;
static GDOverflowCallback overflowcb = NULL;

// GDBase
void GDInitGDLObj(GDLObj* dl, void* start, u32 length) {
    dl->start = (u8*)start;
    dl->ptr = (u8*)start;
    dl->top = (u8*)start + length;
    dl->length = length;
}

void GDFlushCurrToMem() {
    DCFlushRange(__GDCurrentDL->start, __GDCurrentDL->length);
}

void GDPadCurr32() {
    u32 n;

    n = (u32)__GDCurrentDL->ptr & 0x1F;
    if (n != 0) {
        for (; n < 32; n = n + 1) {
            __GDWrite(0);
        }
    }
}

void GDOverflowed() {
    if (overflowcb) {
        overflowcb();
    }
}

// GDGeometry
void GDSetVtxDescv(GXVtxDescList*) { NOT_IMPLEMENTED_CONTINUE; }
void GDSetArray(GXAttr attr, void* data, u8 stride) { NOT_IMPLEMENTED_CONTINUE; }
void GDSetArrayRaw(GXAttr attr, u32 data, u8 stride) { NOT_IMPLEMENTED_CONTINUE; }

// inlines
void __GDWrite(u8 data) {
    *__GDCurrentDL->ptr++ = data;
}

void GDWrite_u8(u8 v) {
    GDOverflowCheck(1);
    __GDWrite(v);
}

inline void GDWrite_u16(u16 v) {
    GDOverflowCheck(2);
    __GDWrite(v >> 8);
    __GDWrite(v & 0xff);
}

inline void GDWrite_u32(u32 v) {
    GDOverflowCheck(4);
    __GDWrite((v >> 24) & 0xff);
    __GDWrite((v >> 16) & 0xff);
    __GDWrite((v >> 8) & 0xff);
    __GDWrite((v >> 0) & 0xff);
}

void GDSetCurrent(GDLObj* obj) { 
    __GDCurrentDL = obj;
}

u32 GDGetGDLObjOffset(GDLObj* obj) {
    return (u32)(obj->ptr - obj->start);
}

u8* GDGetCurrPointer() {
    return __GDCurrentDL->ptr;
}

s32 GDGetCurrOffset() {
    return __GDCurrentDL->ptr - __GDCurrentDL->start;
}

void GDSetCurrOffset(s32 offs) {
    __GDCurrentDL->ptr = __GDCurrentDL->start + offs;
}

void GDOverflowCheck(u32 len) {
    if (__GDCurrentDL->ptr + len > __GDCurrentDL->top) {
        GDOverflowed();
    }
}
