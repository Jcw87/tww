#ifndef D_A_OBJ_WARPT_H
#define D_A_OBJ_WARPT_H

#include "f_op/f_op_actor.h"

class daObj_Warpt_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    void modeProcInit(int) {}

    void _createHeap();
    void createHutaHeap();
    void createBodyHeap();
    void _ride(fopAc_ac_c*);
    void isHuta();
    void isSp();
    void isOtherHuta();
    void isRealHuta();
    void warp(int);
    void onWarpBit(unsigned char);
    void isWarpBit(unsigned char);
    void setMtx();
    void initCollision();
    void setCollision();
    void breakHuta(int);
    void openHuta();
    void checkHitSE();
    void modeOpenInit();
    void modeOpen();
    void modeCloseInit();
    void modeClose();
    void modeBreakFireInit();
    void modeBreakFire();
    void modeEventWarpInit();
    void modeEventWarp();
    void normalWarp();
    void spWarp();
    void modeEventOpenInit();
    void modeEventOpen();
    void modeProc(Proc_e, int);
    bool _execute();
    bool _draw();
    void getArg();
    void createInit();
    s32 _create();
    bool _delete();

public:
    /* Place member variables here */
};

class daObj_Warpt_HIO_c {
public:
    daObj_Warpt_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_WARPT_H */
