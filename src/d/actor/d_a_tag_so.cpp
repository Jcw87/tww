//
// Generated by dtk
// Translation Unit: d_a_tag_so.cpp
//

#include "d/actor/d_a_tag_so.h"
#include "d/d_procname.h"

/* 000000EC-0000010C       .text __ct__14daTag_So_HIO_cFv */
daTag_So_HIO_c::daTag_So_HIO_c() {
    /* Nonmatching */
}

/* 0000010C-00000114       .text _execute__10daTag_So_cFv */
bool daTag_So_c::_execute() {
    /* Nonmatching */
}

/* 00000114-0000018C       .text debugDraw__10daTag_So_cFv */
void daTag_So_c::debugDraw() {
    /* Nonmatching */
}

/* 0000018C-000001C4       .text _draw__10daTag_So_cFv */
bool daTag_So_c::_draw() {
    /* Nonmatching */
}

/* 000001C4-00000224       .text getArg__10daTag_So_cFv */
void daTag_So_c::getArg() {
    /* Nonmatching */
}

/* 00000224-0000027C       .text _create__10daTag_So_cFv */
s32 daTag_So_c::_create() {
    /* Nonmatching */
}

/* 0000027C-00000284       .text _delete__10daTag_So_cFv */
bool daTag_So_c::_delete() {
    /* Nonmatching */
}

/* 00000284-000002A4       .text daTag_SoCreate__FPv */
static s32 daTag_SoCreate(void*) {
    /* Nonmatching */
}

/* 000002A4-000002C8       .text daTag_SoDelete__FPv */
static BOOL daTag_SoDelete(void*) {
    /* Nonmatching */
}

/* 000002C8-000002EC       .text daTag_SoExecute__FPv */
static BOOL daTag_SoExecute(void*) {
    /* Nonmatching */
}

/* 000002EC-00000310       .text daTag_SoDraw__FPv */
static BOOL daTag_SoDraw(void*) {
    /* Nonmatching */
}

/* 00000310-00000318       .text daTag_SoIsDelete__FPv */
static BOOL daTag_SoIsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daTag_SoMethodTable = {
    (process_method_func)daTag_SoCreate,
    (process_method_func)daTag_SoDelete,
    (process_method_func)daTag_SoExecute,
    (process_method_func)daTag_SoIsDelete,
    (process_method_func)daTag_SoDraw,
};

actor_process_profile_definition g_profile_TAG_SO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TAG_SO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTag_So_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0065,
    /* Actor SubMtd */ &daTag_SoMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
