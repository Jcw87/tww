#ifndef D_A_OBJ_VTENG_H
#define D_A_OBJ_VTENG_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daObjVteng_c : public fopAc_ac_c {
public:
    void init_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_McaMorf* mpMorf;
    /* 0x2A0 */ dBgW* mpBgW;
    /* 0x2A4 */ Mtx mMtx;
};

#endif /* D_A_OBJ_VTENG_H */
