//
// Generated by dtk
// Translation Unit: d_a_scene_change.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

class daSceneChgHIO_c {
public:
    daSceneChgHIO_c();
    virtual ~daSceneChgHIO_c();

    s8 m0004;
    s8 m0005;
    f32 m0008;
};

static daSceneChgHIO_c l_HIO;

class d_a_scene_change_c : public fopAc_ac_c {
public:
    Mtx mTransformMtx;
};

/* 000000EC-00000118       .text __ct__15daSceneChgHIO_cFv */
daSceneChgHIO_c::daSceneChgHIO_c() {
    m0004 = 0xFF;
    m0005 = 0;
    m0008 = 100.0f;
}

/* 00000118-000001A8       .text daSceneChgCreate__FPv */
s32 daSceneChgCreate(void* i_this) {
    d_a_scene_change_c* scnChg = static_cast<d_a_scene_change_c*>(i_this);
    
    fopAcM_SetupActor(scnChg, d_a_scene_change_c);
    
    MTXTrans(mDoMtx_stack_c::now, scnChg->current.pos.x, scnChg->current.pos.y, scnChg->current.pos.z);
    mDoMtx_ZXYrotM(mDoMtx_stack_c::now, scnChg->shape_angle.x, scnChg->shape_angle.y, scnChg->shape_angle.z);
    
    MTXCopy(mDoMtx_stack_c::now, scnChg->mTransformMtx);
    return cPhs_COMPLEATE_e;
}

/* 000001A8-000001B0       .text daSceneChgDelete__FPv */
BOOL daSceneChgDelete(void* i_this) {
    return TRUE;
}

/* 000001B0-000001B8       .text daSceneChgExecute__FPv */
BOOL daSceneChgExecute(void* i_this) {
    return TRUE;
}

/* 000001B8-000001C0       .text daSceneChgDraw__FPv */
BOOL daSceneChgDraw(void* i_this) {
    return TRUE;
}

/* 000001C0-000001C8       .text daSceneChgIsDelete__FPv */
BOOL daSceneChgIsDelete(void* i_this) {
    return TRUE;
}

/* 000001C8-00000218       .text __dt__15daSceneChgHIO_cFv */
daSceneChgHIO_c::~daSceneChgHIO_c() {
    m0004 = 0xFF;
}

static actor_method_class daSceneChgMethodTable = {
    (process_method_func)daSceneChgCreate,
    (process_method_func)daSceneChgDelete,
    (process_method_func)daSceneChgExecute,
    (process_method_func)daSceneChgIsDelete,
    (process_method_func)daSceneChgDraw,
};

extern actor_process_profile_definition g_profile_SCENECHG = {
    fpcLy_CURRENT_e,
    3,
    fpcLy_CURRENT_e,
    PROC_SCENECHG,
    &g_fpcLf_Method.mBase,
    sizeof(d_a_scene_change_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x01A1,
    &daSceneChgMethodTable,
    0x00040000,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_4_e,
};
