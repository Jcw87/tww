#ifndef GXGEOMETRY_H
#define GXGEOMETRY_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/os/OSError.h"

#ifdef __cplusplus
extern "C" {
#endif

void __GXSetDirtyState(void);
void GXBegin(GXPrimitive type, GXVtxFmt fmt, u16 vert_num);
void __GXSendFlushPrim(void);
void GXSetLineWidth(u8 width, GXTexOffset offsets);
void GXSetPointSize(u8 size, GXTexOffset offsets);
void GXEnableTexOffsets(GXTexCoordID coord, GXBool line, GXBool point);
void GXSetCullMode(GXCullMode mode);
void GXSetCoPlanar(GXBool enable);
void __GXSetGenMode(void);

#ifdef TARGET_PC
void GXBeginDebug(GXPrimitive type, GXVtxFmt fmt, u16 vert_num, const char* file, int line);
void GXEndDebug();
void GXEnd(void);
#define GXBegin(type, fmt, vert_num) GXBeginDebug(type, fmt, vert_num, __FILE__, __LINE__)
#define GXEnd() GXEndDebug()
#else
inline void GXEnd(void) {}
#endif

#ifdef __cplusplus
};
#endif

#endif /* GXGEOMETRY_H */
