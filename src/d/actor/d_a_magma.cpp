//
// Generated by dtk
// Translation Unit: d_a_magma.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/d_magma.h"
#include "dolphin/types.h"


class daMagma_c : public fopAc_ac_c {
public:
    ~daMagma_c() {
        dComIfG_resDelete(&mPhs, "Magma");
    }

    request_of_phase_process_class mPhs;
};

/* 00000078-00000080       .text daMagma_IsDelete__FP9daMagma_c */
BOOL daMagma_IsDelete(daMagma_c* i_this) {
    return TRUE;
}

/* 00000080-000000CC       .text daMagma_Delete__FP9daMagma_c */
BOOL daMagma_Delete(daMagma_c* i_this) {
    i_this->~daMagma_c();
    return TRUE;
}

/* 000000CC-00000178       .text daMagma_Create__FP10fopAc_ac_c */
s32 daMagma_Create(fopAc_ac_c* i_this) {
    daMagma_c* magma = static_cast<daMagma_c*>(i_this);

    fopAcM_SetupActor(magma, daMagma_c);

    int result = dComIfG_resLoad(&magma->mPhs, "Magma");
    if (result != cPhs_COMPLEATE_e) {
        return result;
    }

    if (g_dComIfG_gameInfo.play.createMagma()) {
        g_dComIfG_gameInfo.play.mpMagmaPacket->newFloor(
            magma->current.pos,
            magma->mScale,
            magma->getRoomNo(),
            magma->mBase.mParameters
        );
    }

    return cPhs_ERROR_e;
}

static actor_method_class l_daMagma_Method = {
    (process_method_func)daMagma_Create,
    (process_method_func)daMagma_Delete,
    (process_method_func)0,
    (process_method_func)daMagma_IsDelete,
    (process_method_func)0,
};

extern actor_process_profile_definition g_profile_MAGMA = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_MAGMA,
    &g_fpcLf_Method.mBase,
    sizeof(daMagma_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x01BC,
    &l_daMagma_Method,
    0x00040180,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e
};
