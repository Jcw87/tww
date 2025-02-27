//
// Generated by dtk
// Translation Unit: d_a_branch.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/types.h"


class daBranch_c : public fopAc_ac_c {
public:
    ~daBranch_c() {
        for (int i = 0; i < 2; i++) {
            mDoExt_McaMorf* anim = mAnims[i];
            if (anim != 0) {
                anim->stopZelAnime();
            }
        }

        dComIfG_resDelete(&mPhs, m_arcname);
    }

    void set_mtx();
    void set_anim(int, int, int);
    void demoPlay(mDoExt_McaMorf*);

    s32 CreateHeap();
    static s32 solidHeapCB(fopAc_ac_c*);

    /* 0x0290 */ request_of_phase_process_class mPhs;
    /* 0x0298 */ J3DModel* mModels[2];
    /* 0x02A0 */ u8 dummy2[0x08]; 
    /* 0x02A8 */ mDoExt_McaMorf* mAnims[2];
    /* 0x02B0 */ u8 dummy[0x08];
    /* 0x02B8 */ u32 m02B8;
    /* 0x02BC */ u8 m02BC;
    /* 0x02BD */ u8 m02BD;

    static char m_arcname[];
};

char daBranch_c::m_arcname[] = "Kwood_00";

/* 00000078-00000128       .text set_mtx__10daBranch_cFv */
void daBranch_c::set_mtx() {
    J3DModel* pMdl;

    for (int i = 0; i < 2; i ++) {
        pMdl = mModels[i];

        if (pMdl) {
            pMdl->setBaseScale(mScale);

            mDoMtx_stack_c::transS(getPosition());
            mDoMtx_stack_c::XYZrotM(getAngle().x, getAngle().y, getAngle().z);
            
            pMdl->i_setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
}

/* 00000128-000001E4       .text set_anim__10daBranch_cFiii */
void daBranch_c::set_anim(int i_animIdx, int i_bckIdx, int i_basIdx) {
    if (i_bckIdx > 0 && i_basIdx > 0) {
        void* pSnd = dComIfG_getObjectIDRes(m_arcname, i_basIdx);
        J3DAnmTransform* pAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectIDRes(m_arcname, i_bckIdx));
        
        mAnims[i_animIdx]->setAnm(
            pAnm,
            -1,
            0.0f,
            1.0f,
            0.0f,
            -1.0f,
            pSnd
        );
    }
}

/* 000001E4-00000228       .text demoPlay__10daBranch_cFP14mDoExt_McaMorf */
void daBranch_c::demoPlay(mDoExt_McaMorf*) {
    /* Nonmatching */
}

/* 00000228-00000248       .text solidHeapCB__10daBranch_cFP10fopAc_ac_c */
s32 daBranch_c::solidHeapCB(fopAc_ac_c* i_this) {
    daBranch_c* branch = static_cast<daBranch_c*>(i_this);
    return branch->CreateHeap();
}

/* 00000248-0000049C       .text CreateHeap__10daBranch_cFv */
s32 daBranch_c::CreateHeap() {
    /* Nonmatching */
    int basIds[] = { 8, 0 }; 
    int bckIds[] = { 7, 2 };
    int bmdIds[] = { 6, 5 };
    int t[] = {0, 0};

    BOOL status = TRUE;

    for (int i = 0; i < 2; i++) {
        J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectIDRes(m_arcname, bmdIds[i]));
        J3DAnmTransformKey* bck = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectIDRes(m_arcname, bckIds[i]));

        JUT_ASSERT(0x1CC, modelData != 0);
        JUT_ASSERT(0x1CD, bck != 0);

        mDoExt_McaMorf* newMorf = new mDoExt_McaMorf(
            static_cast<J3DModelData*>(dComIfG_getObjectIDRes(m_arcname, bmdIds[i])),
            0,
            0,
            static_cast<J3DAnmTransformKey*>(dComIfG_getObjectIDRes(m_arcname, bckIds[i])),
            0,
            1.0f,
            0,
            -1,
            1,
            0,
            0, 
            0x11020203
        );

        mAnims[i] = newMorf;
        if (!mAnims[i]) {
            status = FALSE;
            break;
        }

        mModels[i] = newMorf->mpModel;
        if (!mModels[i]) {
            status = FALSE;
            break;
        }

        mAnims[i]->setFrame(0.0f);
        set_anim(i, bckIds[i], basIds[i]);
    }

    return status;
}

/* 0000049C-00000524       .text daBranch_Draw__FP10daBranch_c */
BOOL daBranch_Draw(daBranch_c* i_this) {
    int activeIdx = 0;
    if (i_this->m02B8 == 5) {
        activeIdx = 1;
    }

    g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->current.pos, &i_this->mTevStr);
    g_env_light.setLightTevColorType(i_this->mModels[activeIdx], &i_this->mTevStr);

    i_this->mAnims[activeIdx]->updateDL();

    return TRUE;
}

/* 00000524-0000060C       .text daBranch_Execute__FP10daBranch_c */
void daBranch_Execute(daBranch_c* i_this) {
    /* Nonmatching */
    int demoId = i_this->mDemoActorId;

    if (demoId == 0) {
        if (i_this->m02B8 == 5) {
            if (i_this->mAnims[1]) {
                i_this->mAnims[1]->play(0, 0, 0);
            }
        }
        else if (i_this->m02B8 == 6 && i_this->mAnims[0]) {
            i_this->mAnims[0]->play(0, 0, 0);
        }
    }
    else {
        void* demoActor = g_dComIfG_gameInfo.play.mDemo;

        if (demoActor) {
            //i_this->m02B8 = demoActor->mShape;

            if (i_this->m02B8 == 6) {
                i_this->demoPlay(i_this->mAnims[0]);
            }
            else if (i_this->m02B8 == 5) {
                i_this->demoPlay(i_this->mAnims[1]);
            }
        }
    }

    i_this->set_mtx();
}

/* 0000060C-00000614       .text daBranch_IsDelete__FP10daBranch_c */
BOOL daBranch_IsDelete(daBranch_c* i_this) {
    return TRUE;
}

/* 00000614-00000694       .text daBranch_Delete__FP10daBranch_c */
BOOL daBranch_Delete(daBranch_c* i_this) {
    i_this->~daBranch_c();
    return TRUE;
}

/* 00000694-0000080C       .text daBranch_Create__FP10fopAc_ac_c */
s32 daBranch_Create(fopAc_ac_c* i_this) {
    /* Nonmatching */
    daBranch_c* branch = static_cast<daBranch_c*>(i_this);

    fopAcM_SetupActor(branch, daBranch_c);

    s32 state = dComIfG_resLoad(&branch->mPhs, daBranch_c::m_arcname);
    if (state == cPhs_COMPLEATE_e) {
        int solidHeapResult = fopAcM_entrySolidHeap(i_this, (heapCallbackFunc)daBranch_c::solidHeapCB, 0x4000);

        if (solidHeapResult & 0xFF == 0) {
            for (int i = 0; i < 2; i++) {
                branch->mAnims[i] = 0;
            }

            state = cPhs_ERROR_e;
        }
        else {
            branch->mCullMtx = branch->mModels[0]->mBaseTransformMtx;
            fopAcM_setCullSizeBox(i_this, 0.0f, 0.0f, -50.0f, 300.0f, 100.0f, 50.0f);
            
            branch->m02B8 = 6;
            branch->m02BC = 0;
            branch->m02BD = 0;

            for (int i = 0; i < 2; i++) {
                J3DModelData* modelData = branch->mModels[i]->mModelData;

                for (int j = 0; j < modelData->getMaterialNum(); j++) {
                    J3DMaterial* mat = modelData->getMaterialNodePointer(j);
                    if (mat) {
                        J3DFog* fog = mat->getPEBlock()->getFog();
                        fog->field_0x0 = 2;
                    }
                }
            }
        }
    }

    return state;
}

static actor_method_class l_daBranch_Method = {
    (process_method_func)daBranch_Create,
    (process_method_func)daBranch_Delete,
    (process_method_func)daBranch_Execute,
    (process_method_func)daBranch_IsDelete,
    (process_method_func)daBranch_Draw,
};

extern actor_process_profile_definition g_profile_BRANCH = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_BRANCH,
    &g_fpcLf_Method.mBase,
    sizeof(daBranch_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x0193,
    &l_daBranch_Method,
    0x00044000,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_CUSTOM_e,
};
