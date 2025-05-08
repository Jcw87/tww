#ifndef J3DSHAPEFACTORY_H
#define J3DSHAPEFACTORY_H

#include "dolphin/gx/GXAttr.h"
#include "dolphin/mtx/vec.h"
#include "port/byteswap.h"

#if TARGET_PC
#define OFFSET_PTR_V0 BE(u32)
#else
#define OFFSET_PTR_V0 void*
#endif

class J3DShape;
class J3DShapeMtx;
class J3DShapeDraw;
struct ResNTAB;

struct J3DShapeInitData {
    /* 0x00 */ u8 mShapeMtxType;
    /* 0x02 */ BE(u16) mMtxGroupNum;
    /* 0x04 */ BE(u16) mVtxDescListIndex;
    /* 0x06 */ BE(u16) mMtxInitDataIndex;
    /* 0x08 */ BE(u16) mDrawInitDataIndex;
    /* 0x0C */ BE(f32) mRadius;
    /* 0x10 */ BE(Vec) mMin;
    /* 0x1C */ BE(Vec) mMax;
};

struct J3DShapeMtxInitData {
    /* 0x00 */ BE(u16) mUseMtxIndex;
    /* 0x02 */ BE(u16) mUseMtxCount;
    /* 0x04 */ BE(u32) mFirstUseMtxIndex;
};

struct J3DShapeDrawInitData {
    /* 0x00 */ BE(u32) mDisplayListSize;
    /* 0x04 */ BE(u32) mDisplayListIndex;
};

struct J3DShapeBlock {
    /* 0x00 */ BE(u32) mMagic;
    /* 0x04 */ BE(u32) mSize;

    /* 0x08 */ BE(u16) mShapeNum;
    /* 0x0A */ u16 _pad;

    /* 0x0C */ OFFSET_PTR_V0 mpShapeInitData;
    /* 0x10 */ OFFSET_PTR_V0 mpIndexTable;
    /* 0x14 */ OFFSET_PTR_V0 mpNameTable;
    /* 0x18 */ OFFSET_PTR_V0 mpVtxDescList;
    /* 0x1C */ OFFSET_PTR_V0 mpMtxTable;
    /* 0x20 */ OFFSET_PTR_V0 mpDisplayListData;
    /* 0x24 */ OFFSET_PTR_V0 mpMtxInitData;
    /* 0x28 */ OFFSET_PTR_V0 mpDrawInitData;
};  // Size: 0x2C

struct J3DShapeFactory {
    J3DShapeFactory(const J3DShapeBlock&);
    J3DShape* create(int, u32, GXVtxDescList*);
    J3DShapeMtx* newShapeMtx(u32, int, int) const;
    J3DShapeDraw* newShapeDraw(int, int) const;
    void allocVcdVatCmdBuffer(u32);
    s32 calcSize(int, u32);
    s32 calcSizeVcdVatCmdBuffer(u32);
    s32 calcSizeShapeMtx(u32, int, int) const;

    /* 0x00 */ J3DShapeInitData* mpShapeInitData;
    /* 0x04 */ BE(u16)* mpIndexTable;
    /* 0x08 */ GXVtxDescList* mpVtxDescList;
    /* 0x0C */ BE(u16)* mpMtxTable;
    /* 0x10 */ u8* mpDisplayListData;
    /* 0x14 */ J3DShapeMtxInitData* mpMtxInitData;
    /* 0x18 */ J3DShapeDrawInitData* mpDrawInitData;
    /* 0x1C */ u8* mpVcdVatCmdBuffer;

    u32 getMtxGroupNum(int no) const { return mpShapeInitData[mpIndexTable[no]].mMtxGroupNum; }
    GXVtxDescList* getVtxDescList(int no) const { return (GXVtxDescList*)((u8*)mpVtxDescList + mpShapeInitData[mpIndexTable[no]].mVtxDescListIndex); }
    f32 getRadius(int no) const { return mpShapeInitData[mpIndexTable[no]].mRadius; }
    const Vec& getMin(int no) const { return mpShapeInitData[mpIndexTable[no]].mMin; }
    const Vec& getMax(int no) const { return mpShapeInitData[mpIndexTable[no]].mMax; }
};

#endif /* J3DSHAPEFACTORY_H */
