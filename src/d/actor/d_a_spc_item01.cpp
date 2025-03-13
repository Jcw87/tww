//
// Generated by dtk
// Translation Unit: d_a_spc_item01.cpp
//

#include "d/actor/d_a_spc_item01.h"
#include "d/d_procname.h"

#include "d/d_bg_s_acch.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_item.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"

namespace daSpcItem01_prm {
    inline u8 getItemNo(daSpcItem01_c* i_this) { return fopAcM_GetParam(i_this) >> 0 & 0xFF; }
    inline u16 getFlag(daSpcItem01_c* i_this) { return fopAcM_GetParam(i_this) >> 8 & 0xFFFF; }
};

const float magic_double = -24.0f;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 4,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    },
};

/* 8015DAF4-8015DBC0       .text set_mtx__13daSpcItem01_cFv */
void daSpcItem01_c::set_mtx() {
    csXyz angle = current.angle;
    cXyz scaleVec = scale;
    f32 offsetY = 0.0f;
    switch (m_itemNo) {
    case BOKO_BELT:
        offsetY = -24.0f;
        break;
    }
    mpModel->setBaseScale(scaleVec);

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + offsetY, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(angle);

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 8015DBC0-8015DBF4       .text _delete__13daSpcItem01_cFv */
BOOL daSpcItem01_c::_delete() {
    return DeleteBase(dItem_data::getFieldArc(m_itemNo));
}

/* 8015DBF4-8015DDD0       .text _create__13daSpcItem01_cFv */
s32 daSpcItem01_c::_create() {
    fopAcM_SetupActor(this, daSpcItem01_c);
    m_itemNo = daSpcItem01_prm::getItemNo(this);
    if (m_itemNo == dItem_SHIELD_e && dComIfGs_isEventBit(0xE20)) {
        setLoadError();
        return cPhs_ERROR_e;
    }
    int phase_state = dComIfG_resLoad(&mPhs, dItem_data::getFieldArc(m_itemNo));
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, &CheckFieldItemCreateHeap,
                                   dItem_data::getHeapSize(m_itemNo)))
        {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }
    return phase_state;
}

/* 8015DDD0-8015DF4C       .text CreateInit__13daSpcItem01_cFv */
BOOL daSpcItem01_c::CreateInit() {
    set_mtx();
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    mStts.Init(0, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    f32 tempVar1 = (f32)getHeight();
    f32 tempVar2 = (f32)getR();
    if (scale.x > 1.0f) {
        tempVar1 *= scale.x;
        tempVar2 *= scale.x;
    }
    mCyl.SetR(tempVar2);
    mCyl.SetH(tempVar1);
    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);

    field_0x644 = daSpcItem01_prm::getFlag(this);
    fopAcM_SetGravity(this, -4.0f);
    switch ((s8)m_itemNo) {
    case dItem_SHIELD_e:
        scale.x = 1.5f;
        scale.y = 1.5f;
        scale.z = 1.5f;
        current.angle.x = 4000;
        current.angle.y = 4200;
        current.angle.z = 5200;
        fopAcM_SetGravity(this, 0.0f);
        break;
    }

    return TRUE;
}

/* 8015DF4C-8015DFE8       .text _execute__13daSpcItem01_cFv */
BOOL daSpcItem01_c::_execute() {
    eyePos = current.pos;
    attention_info.position = current.pos;
    m_timer++;
    set_effect();
    scale_anim();
    anim_play();
    move();
    rotate_item();
    setCol();
    set_mtx();
    return TRUE;
}

/* 8015DFE8-8015E070       .text set_effect__13daSpcItem01_cFv */
void daSpcItem01_c::set_effect() {
    if (cLib_checkBit(field_0x644, (u16)0x01) && dItem_data::checkAppearEffect(m_itemNo) && !field_0x642 && m_itemNo != BOKO_BELT) {
        dComIfGp_particle_setSimple(dItem_data::getAppearEffect(m_itemNo), &current.pos);
    }
}

/* 8015E070-8015E0D8       .text scale_anim__13daSpcItem01_cFv */
void daSpcItem01_c::scale_anim() {
    if (isRupee(m_itemNo)) {
        cLib_chaseF(&scale.x, 1.0f, 0.05f);
        cLib_chaseF(&scale.y, 1.0f, 0.05f);
        cLib_chaseF(&scale.z, 1.0f, 0.05f);
    }
}

/* 8015E0D8-8015E11C       .text anim_play__13daSpcItem01_cFv */
void daSpcItem01_c::anim_play() {
    f32 animPlayParam = 1.0f;
    if (m_itemNo == BOKO_BELT) {
        animPlayParam = 0.0f;
    }
    animPlay(1.0f, 1.0f, 1.0f, 1.0f, animPlayParam);
}

/* 8015E11C-8015E20C       .text move__13daSpcItem01_cFv */
void daSpcItem01_c::move() {
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());
    switch (m_itemNo) {
    case dItem_SHIELD_e:
        break;
    case dItem_JOY_PENDANT_e:
        if (mAcch.ChkGroundLanding()) {
            speed.x = 0.0f;
            speed.y = 0.0f;
            speed.z = 0.0f;
            speedF = 0.0f;
        }
        break;
    default:
        if (mAcch.ChkGroundLanding()) {
            field_0x642 += 1;
            f32 newGravity = field_0x63C * 0.62f;
            if (newGravity > gravity - 0.5f) {
                speedF = 0.0f;
            } else {
                speed.x = 0.0f;
                speed.y = -newGravity;
                speed.z = 0.0f;
            }
        }
        break;
    }

    if (speed.y != 0.0f) {
        field_0x63C = speed.y;
    }
}

/* 8015E20C-8015E278       .text rotate_item__13daSpcItem01_cFv */
void daSpcItem01_c::rotate_item() {
    if (isRupee(m_itemNo)) {
        if (field_0x642 == 0) {
            field_0x640 = current.angle.x + 0x2000;
        } else {
            field_0x640 = 0;
        }
        cLib_chaseAngleS(&current.angle.x, field_0x640, 0x2000);
    }
}

/* 8015E278-8015E27C       .text setCol__13daSpcItem01_cFv */
void daSpcItem01_c::setCol() {
    /* Empty Function */
}

/* 8015E27C-8015E2A8       .text _draw__13daSpcItem01_cFv */
BOOL daSpcItem01_c::_draw() {
    return DrawBase();
}

/* 8015E2A8-8015E368       .text setTevStr__13daSpcItem01_cFv */
void daSpcItem01_c::setTevStr() {
    if (m_itemNo == BOKO_BELT) {
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);
    } else {
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    }
    dKy_getEnvlight().setLightTevColorType(mpModel, &tevStr);

    for (s32 modelIndex = 0; modelIndex < (s32)ARRAY_SIZE(mpModelArrow); modelIndex++) {
        J3DModel* modelArrow = mpModelArrow[modelIndex];
        if (modelArrow != NULL) {
            dKy_getEnvlight().setLightTevColorType(modelArrow, &tevStr);
        }
    }
}

/* 8015E368-8015E388       .text daSpcItem01_Draw__FP13daSpcItem01_c */
static BOOL daSpcItem01_Draw(daSpcItem01_c* i_this) {
    return i_this->_draw();
}

/* 8015E388-8015E3A8       .text daSpcItem01_Execute__FP13daSpcItem01_c */
static BOOL daSpcItem01_Execute(daSpcItem01_c* i_this) {
    return i_this->_execute();
}

/* 8015E3A8-8015E3B0       .text daSpcItem01_IsDelete__FP13daSpcItem01_c */
static BOOL daSpcItem01_IsDelete(daSpcItem01_c* ignored) {
    return TRUE;
}

/* 8015E3B0-8015E3D0       .text daSpcItem01_Delete__FP13daSpcItem01_c */
static BOOL daSpcItem01_Delete(daSpcItem01_c* i_this) {
    return i_this->_delete();
}

/* 8015E3D0-8015E3F0       .text daSpcItem01_Create__FP10fopAc_ac_c */
static s32 daSpcItem01_Create(fopAc_ac_c* i_this) {
    return ((daSpcItem01_c*)i_this)->_create();
}

static actor_method_class l_daSpcItem01_Method = {
    (process_method_func)daSpcItem01_Create,
    (process_method_func)daSpcItem01_Delete,
    (process_method_func)daSpcItem01_Execute,
    (process_method_func)daSpcItem01_IsDelete,
    (process_method_func)daSpcItem01_Draw,
};

actor_process_profile_definition g_profile_SPC_ITEM01 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SPC_ITEM01,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daSpcItem01_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0100,
    /* Actor SubMtd */ &l_daSpcItem01_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
