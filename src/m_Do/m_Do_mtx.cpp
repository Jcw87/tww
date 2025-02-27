//
// Generated by dtk
// Translation Unit: m_Do_mtx.cpp
//

#include "m_Do/m_Do_mtx.h"
#include "dolphin/mtx/mtx.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JMath/JMath.h"
#include "SSystem/SComponent/c_math.h"

/* 8000CB48-8000CBEC       .text mDoMtx_XYZrotM__FPA4_fsss */
void mDoMtx_XYZrotM(Mtx mtx, s16 x, s16 y, s16 z) {
    Mtx tmp;
    if (z != 0) {
        mDoMtx_ZrotS(tmp, z);
        PSMTXConcat(mtx, tmp, mtx);
    }

    if (y != 0) {
        mDoMtx_YrotS(tmp, y);
        PSMTXConcat(mtx, tmp, mtx);
    }

    if (x != 0) {
        mDoMtx_XrotS(tmp, x);
        PSMTXConcat(mtx, tmp, mtx);
    }
}

/* 8000CBEC-8000CC84       .text mDoMtx_ZXYrotS__FPA4_fsss */
void mDoMtx_ZXYrotS(Mtx mtx, s16 x, s16 y, s16 z) {
    Mtx tmp;
    if (y != 0) {
        mDoMtx_YrotS(mtx, y);
    } else {
        PSMTXIdentity(mtx);
    }

    if (x != 0) {
        mDoMtx_XrotS(tmp, x);
        PSMTXConcat(mtx, tmp, mtx);
    }

    if (z != 0) {
        mDoMtx_ZrotS(tmp, z);
        PSMTXConcat(mtx, tmp, mtx);
    }
}

/* 8000CC84-8000CD28       .text mDoMtx_ZXYrotM__FPA4_fsss */
void mDoMtx_ZXYrotM(Mtx mtx, s16 x, s16 y, s16 z) {
    Mtx tmp;
    if (y != 0) {
        mDoMtx_YrotS(tmp, y);
        PSMTXConcat(mtx, tmp, mtx);
    }

    if (x != 0) {
        mDoMtx_XrotS(tmp, x);
        PSMTXConcat(mtx, tmp, mtx);
    }

    if (z != 0) {
        mDoMtx_ZrotS(tmp, z);
        PSMTXConcat(mtx, tmp, mtx);
    }
}

/* 8000CD28-8000CD88       .text mDoMtx_XrotS__FPA4_fs */
void mDoMtx_XrotS(Mtx, s16) {
    /* Nonmatching */
}

/* 8000CD88-8000CDC8       .text mDoMtx_XrotM__FPA4_fs */
void mDoMtx_XrotM(Mtx mtx, s16 x) {
    Mtx tmp;
    mDoMtx_XrotS(tmp, x);
    PSMTXConcat(mtx, tmp, mtx);
}

/* 8000CDC8-8000CE28       .text mDoMtx_YrotS__FPA4_fs */
void mDoMtx_YrotS(Mtx, s16) {
    /* Nonmatching */
}

/* 8000CE28-8000CE68       .text mDoMtx_YrotM__FPA4_fs */
void mDoMtx_YrotM(Mtx mtx, s16 y) {
    Mtx tmp;
    mDoMtx_YrotS(tmp, y);
    PSMTXConcat(mtx, tmp, mtx);
}

/* 8000CE68-8000CEC8       .text mDoMtx_ZrotS__FPA4_fs */
void mDoMtx_ZrotS(Mtx, s16) {
    /* Nonmatching */
}

/* 8000CEC8-8000CF08       .text mDoMtx_ZrotM__FPA4_fs */
void mDoMtx_ZrotM(Mtx mtx, s16 z) {
    Mtx tmp;
    mDoMtx_ZrotS(tmp, z);
    PSMTXConcat(mtx, tmp, mtx);
}

/* 8000CF08-8000D10C       .text mDoMtx_lookAt__FPA4_fPC3VecPC3Vecs */
void mDoMtx_lookAt(Mtx, const Vec*, const Vec*, s16) {
    /* Nonmatching */
}

/* 8000D148-8000D284       .text mDoMtx_lookAt__FPA4_fPC3VecPC3VecPC3Vecs */
void mDoMtx_lookAt(Mtx, const Vec*, const Vec*, const Vec*, s16) {
    /* Nonmatching */
}

/* 8000D284-8000D388       .text mDoMtx_concatProjView__FPA4_CfPA4_CfPA4_f */
void mDoMtx_concatProjView(const Mtx, const Mtx, Mtx) {
    /* Nonmatching */
}

/* 8000D388-8000D530       .text mDoMtx_inverseTranspose__FPA4_CfPA4_f */
void mDoMtx_inverseTranspose(const Mtx, Mtx) {
    /* Nonmatching */
}

/* 8000D530-8000D634       .text mDoMtx_QuatConcat__FPC10QuaternionPC10QuaternionP10Quaternion */
void mDoMtx_QuatConcat(const Quaternion*, const Quaternion*, Quaternion*) {
    /* Nonmatching */
}

/* 8000D634-8000D74C       .text mDoMtx_MtxToRot__FPA4_CfP5csXyz */
// NONMATCHING - sqrtf issues
void mDoMtx_MtxToRot(const Mtx m, csXyz* o_rot) {
    o_rot->x = cM_atan2s(-m[1][2], sqrtf(m[0][2] * m[0][2] + m[2][2] * m[2][2]));

    if (o_rot->x == 0x4000 || o_rot->x == -0x4000) {
        o_rot->z = 0;
        o_rot->y = cM_atan2s(-m[2][0], m[0][0]);
    } else {
        o_rot->y = cM_atan2s(m[0][2], m[2][2]);
        o_rot->z = cM_atan2s(m[1][0], m[1][1]);
    }
}

Mtx mDoMtx_stack_c::now;
Mtx mDoMtx_stack_c::buffer[16];

Mtx* mDoMtx_stack_c::next = mDoMtx_stack_c::buffer;
Mtx* mDoMtx_stack_c::end = mDoMtx_stack_c::buffer + 16;

/* 8000D74C-8000D7CC       .text push__14mDoMtx_stack_cFv */
bool mDoMtx_stack_c::push() {
    if (next >= end) {
        JUT_ASSERT(723, next < end)
        return false;
    }
    Mtx* old = next++;
    PSMTXCopy(now, *old);
    return true;
}

/* 8000D7CC-8000D850       .text pop__14mDoMtx_stack_cFv */
bool mDoMtx_stack_c::pop() {
    if (next <= buffer) {
        JUT_ASSERT(745, next > buffer)
        return false;
    }
    next--;
    PSMTXCopy(*next, now);
    return true;
}

/* 8000D850-8000D888       .text transM__14mDoMtx_stack_cFfff */
void mDoMtx_stack_c::transM(f32 x, f32 y, f32 z) {
    Mtx tmp;
    PSMTXTrans(tmp, x, y, z);
    PSMTXConcat(now, tmp, now);
}

/* 8000D888-8000D8C0       .text scaleM__14mDoMtx_stack_cFfff */
void mDoMtx_stack_c::scaleM(f32 x, f32 y, f32 z) {
    Mtx tmp;
    PSMTXScale(tmp, x, y, z);
    PSMTXConcat(now, tmp, now);
}

/* 8000D8C0-8000D904       .text lYrotM__14mDoMtx_stack_cFl */
void mDoMtx_stack_c::lYrotM(s32 param_0) {
    Mtx m;
    mDoMtx_YrotS(m, param_0 >> 16);
    MTXConcat(now, m, now);
}

/* 8000D904-8000D940       .text rYrotM__14mDoMtx_stack_cFf */
void mDoMtx_stack_c::rYrotM(f32 i_rad) {
    Mtx m;
    PSMTXRotRad(m, 'Y', i_rad);
    MTXConcat(now, m, now);
}

/* 8000D940-8000D97C       .text quatM__14mDoMtx_stack_cFPC10Quaternion */
void mDoMtx_stack_c::quatM(const Quaternion* param_0) {
    Mtx tmp;
    PSMTXQuat(tmp, param_0);
    PSMTXConcat(now, tmp, now);
}

static mDoMtx_stack_c mDoMtx_stack;

static mDoMtx_quatStack_c mDoMtx_quatStack;

extern Mtx g_mDoMtx_identity = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
};
