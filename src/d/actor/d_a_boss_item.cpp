//
// Generated by dtk
// Translation Unit: d_a_boss_item.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

extern BOOL dComIfGs_isStageBossEnemy(int i_stageNo);
extern BOOL dComIfGs_isStageLife(int i_stageNo);

class bossitem_class : public fopAc_ac_c {
    s32 m0000;
    s32 m0004;
};

/* 00000078-00000080       .text daBossItem_IsDelete__FP14bossitem_class */
BOOL daBossItem_IsDelete(bossitem_class* i_this) {
    return TRUE;
}

/* 00000080-00000088       .text daBossItem_Delete__FP14bossitem_class */
BOOL daBossItem_Delete(bossitem_class* i_this) {
    return TRUE;
}

/* 00000088-00000128       .text daBossItem_Create__FP10fopAc_ac_c */
s32 daBossItem_Create(fopAc_ac_c* i_this) {
    bossitem_class* bItem = static_cast<bossitem_class*>(i_this);

    fopAcM_SetupActor(bItem, bossitem_class);

    int stageNo = bItem->mBase.mParameters & 0xFF;
    BOOL isStageBossDead = dComIfGs_isStageBossEnemy(stageNo);

    if (isStageBossDead && !dComIfGs_isStageLife(stageNo)) {
        fopAcM_createItemForBoss(
            &bItem->current.pos,
            1,
            bItem->current.roomNo,
            &bItem->current.angle,
            0,
            1
        );
    }

    return cPhs_ERROR_e;
}

static actor_method_class daBossItem_METHODS = {
    (process_method_func)daBossItem_Create,
    (process_method_func)daBossItem_Delete,
    (process_method_func)0,
    (process_method_func)daBossItem_IsDelete,
    (process_method_func)0,
};

extern actor_process_profile_definition g_profile_BOSSITEM = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_BOSSITEM,
    &g_fpcLf_Method.mBase,
    sizeof(bossitem_class),
    0,
    0,
    &g_fopAc_Method.base,
    0x00FB,
    &daBossItem_METHODS,
    0x00040000,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
