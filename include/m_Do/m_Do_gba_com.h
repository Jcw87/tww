#ifndef M_DO_GBA_COM_H
#define M_DO_GBA_COM_H

#include "dolphin/types.h"

class mDoGaC_DataManag_c {
public:
    /* 0x0 */ u32 field_0x0;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
};

struct mDoGaC_unk_data {
    /* 0x00 */ u32* field_0x0;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ u8 field_0x8;
    /* 0x0C */ u32 field_0xc;
};

class mDoGaC_agbCom_c {
public:
    void mDoGaC_Initial(mDoGaC_DataManag_c*, u8);
    void mDoGaC_ComOpen();
    void mDoGaC_ComClose();
    void mDoGaC_ComStart();
    void mDoGaC_ComStop();
    void mDoGaC_GbaReboot();
    void mDoGaC_GbaReset();
    void mDoGaC_ComRestart();
    void mDoGaC_Connect();
    void mDoGaC_ConnectSleep();
    void mDoGaC_ConnectWake();
    int mDoGaC_GbaLink();
    int mDoGaC_SendDataSet(u32*, int, u8, u32);
    void mDoGaC_SendDataWrite();
    int mDoGaC_SendEntry(u8, u32);
    int mDoGaC_SendStatusCheck(u8);
    int mDoGaC_SendEndCheck(u8);
    bool mDoGaC_RecvStatusCheck(u8);
    void mDoGaC_DataStatusReset(u8);
    int mDoGaC_StatusSendSet(u8);
    void mDoGaC_ProbeCheck0();
    void mDoGaC_ProbeCheck1();
    void mDoGaC_CodeExchange0();
    void mDoGaC_CodeExchange1();
    void mDoGaC_CodeExchange2();
    void mDoGaC_CodeExchange3();
    void mDoGaC_CodeExchange4();
    void mDoGaC_ContextCheck();
    void mDoGaC_ContextSend();
    void mDoGaC_ContextRead();
    void mDoGaC_GbaWrite();
    void mDoGaC_WriteResult();
    void mDoGaC_GbaRead();
    void mDoGaC_ReadResult();

    ~mDoGaC_agbCom_c();

    u8 getPortNo() { return mPortNo; }

    /* 0x000 */ u8 field_0x0;
    /* 0x001 */ u8 field_0x1;
    /* 0x002 */ u8 field_0x2;
    /* 0x003 */ u8 field_0x3;
    /* 0x004 */ u8 field_0x4;
    /* 0x005 */ u8 field_0x5;
    /* 0x006 */ u8 field_0x6;
    /* 0x007 */ u8 field_0x7;
    /* 0x008 */ u8 field_0x8;
    /* 0x009 */ u8 field_0x9;
    /* 0x00A */ u8 field_0xa;
    /* 0x00B */ u8 field_0xb;
    /* 0x00C */ mDoGaC_unk_data field_0xc[16];
    /* 0x10C */ u8 field_0x10c;
    /* 0x10D */ u8 mPortNo;
    /* 0x10E */ u8 field_0x10e;
    /* 0x10F */ u8 field_0x10F[0x110 - 0x10F];
    /* 0x110 */ mDoGaC_DataManag_c* field_0x110;
    /* 0x114 */ u32 field_0x114;
    /* 0x118 */ u32 field_0x118;
    /* 0x11C */ u32 field_0x11C;
    /* 0x120 */ u32 field_0x120;
    /* 0x124 */ u8 field_0x124[0x128 - 0x124];
    /* 0x128 */ u8 field_0x128;
    /* 0x129 */ u8 field_0x129[0x12C - 0x129];
    union {
        /* 0x12C */ u32 U32;
        /* 0x12C */ u8 U8;
        struct {
            /* 0x12C */ u16 _12c;
            /* 0x12C */ u16 _12e;
        } U16;
    } field_0x12c;
};

extern mDoGaC_agbCom_c g_mDoGaC_gbaCom;
extern mDoGaC_DataManag_c TestDataManager[16];

inline u8 mDoGaC_getPortNo() {
    return g_mDoGaC_gbaCom.getPortNo();
}

#endif /* M_DO_GBA_COM_H */