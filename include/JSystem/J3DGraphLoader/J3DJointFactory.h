#ifndef J3DJOINTFACTORY_H
#define J3DJOINTFACTORY_H

#include "JSystem/J3DGraphBase/J3DTransform.h"
#include "dolphin/types.h"
#include "port/byteswap.h"

#if TARGET_PC
#define OFFSET_PTR_V0 BE(u32)
#else
#define OFFSET_PTR_V0 void*
#endif

class J3DJoint;
struct ResNTAB;

struct J3DJointInitData {
    /* 0x00 */ u16 mKind;
    /* 0x02 */ bool mScaleCompensate;
    /* 0x04 */ J3DTransformInfo mTransformInfo;
    /* 0x24 */ f32 mRadius;
    /* 0x28 */ Vec mMin;
    /* 0x2C */ Vec mMax;
};  // Size: 0x30

struct J3DJointBlock {
    /* 0x00 */ BE(u32) mMagic;
    /* 0x04 */ BE(u32) mSize;

    /* 0x08 */ BE(u16) mJointNum;
    /* 0x0A */ u16 _pad;

    /* 0x0C */ OFFSET_PTR_V0 mpJointInitData;
    /* 0x10 */ OFFSET_PTR_V0 mpIndexTable;
    /* 0x14 */ OFFSET_PTR_V0 mpNameTable;
};  // Size: 0x18

struct J3DJointFactory {
    J3DJointFactory(J3DJointBlock const&);
    J3DJoint* create(int);

    /* 0x0 */ J3DJointInitData* mJointInitData;
    /* 0x4 */ u16* mIndexTable;

    u16 getKind(int no) const { return mJointInitData[mIndexTable[no]].mKind; }
    u8 getScaleCompensate(int no) const { return mJointInitData[mIndexTable[no]].mScaleCompensate; }
    const J3DTransformInfo& getTransformInfo(int no) const {
        return mJointInitData[mIndexTable[no]].mTransformInfo;
    }
    f32 getRadius(int no) const { return mJointInitData[mIndexTable[no]].mRadius; }
    Vec& getMin(int no) const { return mJointInitData[mIndexTable[no]].mMin; }
    Vec& getMax(int no) const { return mJointInitData[mIndexTable[no]].mMax; }
};

#endif /* J3DJOINTFACTORY_H */