//
// Generated by dtk
// Translation Unit: J3DUMotion.cpp
//

#include "JSystem/J3DU/J3DUMotion.h"
#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "dolphin/types.h"

// this puts the correct functions here when they are weak
// however, the data from J3DMtxCalcBasic::init starts appearing in other TUs
static void dummy(J3DMtxCalcBasic* calc1, J3DMtxCalcSoftimage* calc2) {
    Vec vec;
    Mtx mtx;
    calc1->init(vec, mtx);
    calc2->init(vec, mtx);
    delete calc2;
}

/* 80256DBC-80256E4C       .text __dt__19J3DMtxCalcSoftimageFv */
J3DMtxCalcSoftimage::~J3DMtxCalcSoftimage() {}

/* 80256E4C-80256E94       .text init__19J3DMtxCalcSoftimageFRC3VecRA3_A4_Cf */
void J3DMtxCalcSoftimage::init(const Vec& vec, const Mtx& mtx) {
    J3DSys::mCurrentS = vec;
    MTXCopy(mtx, J3DSys::mCurrentMtx);
}

/* 80256E94-80256F80       .text init__15J3DMtxCalcBasicFRC3VecRA3_A4_Cf */
void J3DMtxCalcBasic::init(const Vec& vec, const Mtx& mtx) {
    J3DSys::mCurrentS = vec;
    J3DSys::mParentS = (Vec){1.0f, 1.0f, 1.0f};
    J3DSys::mCurrentMtx[0][0] = mtx[0][0] * J3DSys::mCurrentS.x;
    J3DSys::mCurrentMtx[0][1] = mtx[0][1] * J3DSys::mCurrentS.y;
    J3DSys::mCurrentMtx[0][2] = mtx[0][2] * J3DSys::mCurrentS.z;
    J3DSys::mCurrentMtx[0][3] = mtx[0][3];
    J3DSys::mCurrentMtx[1][0] = mtx[1][0] * J3DSys::mCurrentS.x;
    J3DSys::mCurrentMtx[1][1] = mtx[1][1] * J3DSys::mCurrentS.y;
    J3DSys::mCurrentMtx[1][2] = mtx[1][2] * J3DSys::mCurrentS.z;
    J3DSys::mCurrentMtx[1][3] = mtx[1][3];
    J3DSys::mCurrentMtx[2][0] = mtx[2][0] * J3DSys::mCurrentS.x;
    J3DSys::mCurrentMtx[2][1] = mtx[2][1] * J3DSys::mCurrentS.y;
    J3DSys::mCurrentMtx[2][2] = mtx[2][2] * J3DSys::mCurrentS.z;
    J3DSys::mCurrentMtx[2][3] = mtx[2][3];
}
