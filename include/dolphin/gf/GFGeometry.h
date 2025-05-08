#ifndef GFGEOMETRY_H
#define GFGEOMETRY_H

#include "dolphin/gx/GX.h"

#ifdef __cplusplus
extern "C" {
#endif

void GFSetVtxDescv(GXVtxDescList*);
void GFSetVtxAttrFmtv(GXVtxFmt, GXVtxAttrFmtList*);
void GFSetArray(GXAttr, void*, u8);
void GFSetCullMode(GXCullMode);

inline void GFBegin(GXPrimitive type, GXVtxFmt fmt, u16 vert_num) {
    GXCmd1u8(fmt | type);
    GXCmd1u16(vert_num);
}

inline void GFEnd() {}

inline void GFWrite_f32(f32 f) {
    GXCmd1u32(*reinterpret_cast<u32*>(&f));

}

inline void GFWrite_s16(s16 s) {
#ifdef __MWERKS__
    GXFIFO.s16 = s;
#else
    GXCmd1u16(*reinterpret_cast<u16*>(&s));
#endif
}

inline void GFPosition3f32(f32 x, f32 y, f32 z) {
    GFWrite_f32(x);
    GFWrite_f32(y);
    GFWrite_f32(z);
}

inline void GFTexCoord2s16(s16 u, s16 v) {
    GFWrite_s16(u);
    GFWrite_s16(v);
}

#ifdef __cplusplus
}
#endif

#endif /* GFGEOMETRY_H */
