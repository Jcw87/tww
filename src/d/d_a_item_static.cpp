//
// Generated by dtk
// Translation Unit: d_a_item_static.cpp
//

#include "d/actor/d_a_item.h"
#include "dolphin/types.h"

/* 80068820-800688A0       .text checkControl__8daItem_cFv */
BOOL daItem_c::checkControl() {
    if (mCurState == STATE_BRING_NEZUMI) {
        return FALSE;
    }
    if (checkActionNow()) {
        return FALSE;
    }
    if (mCurState == 4) {
        return FALSE;
    }
    if (mCurState == STATE_INIT_NORMAL || mCurState == STATE_MAIN_NORMAL) {
        return FALSE;
    }
    return TRUE;
}

/* 800688A0-800688E8       .text startControl__8daItem_cFv */
BOOL daItem_c::startControl() {
    if (!checkControl()) {
        return FALSE;
    }
    mCurState = STATE_BRING_NEZUMI;
    return TRUE;
}

/* 800688E8-800688F8       .text endControl__8daItem_cFv */
BOOL daItem_c::endControl() {
    mCurState = 0;
    return TRUE;
}

/* 800688F8-80068950       .text checkLock__8daItem_cFv */
BOOL daItem_c::checkLock() {
    if (checkActionNow()) {
        return FALSE;
    }
    if (mCurState == 4) {
        return FALSE;
    }
    return mCurState == 0 ? TRUE : FALSE;
}

/* 80068950-80068998       .text setLock__8daItem_cFv */
BOOL daItem_c::setLock() {
    if (!checkLock()) {
        return FALSE;
    }
    mCurState = STATE_WAIT_MAIN;
    return TRUE;
}

/* 80068998-800689A8       .text releaseLock__8daItem_cFv */
BOOL daItem_c::releaseLock() {
    mCurState = 0;
    return TRUE;
}

/* 800689A8-800689F0       .text checkActionNow__8daItem_cFv */
BOOL daItem_c::checkActionNow() {
    if (fabsf(speedF) < 0.1f && fabsf(next.pos.y - current.pos.y) < 1.0f) {
        return FALSE;
    }
    return TRUE;
}

