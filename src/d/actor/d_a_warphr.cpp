//
// Generated by dtk
// Translation Unit: d_a_warphr.cpp
//

#include "d/actor/d_a_warphr.h"
#include "d/d_procname.h"

/* 000000EC-0000016C       .text _delete__10daWarphr_cFv */
bool daWarphr_c::_delete() {
    /* Nonmatching */
}

/* 0000016C-0000018C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000018C-0000059C       .text CreateHeap__10daWarphr_cFv */
void daWarphr_c::CreateHeap() {
    /* Nonmatching */
}

/* 000005E4-000006BC       .text CreateInit__10daWarphr_cFv */
void daWarphr_c::CreateInit() {
    /* Nonmatching */
}

/* 000006BC-00000768       .text _create__10daWarphr_cFv */
s32 daWarphr_c::_create() {
    /* Nonmatching */
}

/* 00000768-00000808       .text set_mtx__10daWarphr_cFv */
void daWarphr_c::set_mtx() {
    /* Nonmatching */
}

/* 00000808-00000A58       .text _execute__10daWarphr_cFv */
bool daWarphr_c::_execute() {
    /* Nonmatching */
}

/* 00000A58-00000AC8       .text normal_execute__10daWarphr_cFv */
void daWarphr_c::normal_execute() {
    /* Nonmatching */
}

/* 00000AC8-00000B50       .text demo_execute__10daWarphr_cFv */
void daWarphr_c::demo_execute() {
    /* Nonmatching */
}

/* 00000B50-00000C6C       .text demo_proc__10daWarphr_cFv */
void daWarphr_c::demo_proc() {
    /* Nonmatching */
}

/* 00000C6C-00000C70       .text initWait__10daWarphr_cFi */
void daWarphr_c::initWait(int) {
    /* Nonmatching */
}

/* 00000C70-00000C98       .text actWait__10daWarphr_cFi */
void daWarphr_c::actWait(int) {
    /* Nonmatching */
}

/* 00000C98-00000CCC       .text initStartWarp__10daWarphr_cFi */
void daWarphr_c::initStartWarp(int) {
    /* Nonmatching */
}

/* 00000CCC-00000CF4       .text actStartWarp__10daWarphr_cFi */
void daWarphr_c::actStartWarp(int) {
    /* Nonmatching */
}

/* 00000CF4-00000DEC       .text initWarp__10daWarphr_cFi */
void daWarphr_c::initWarp(int) {
    /* Nonmatching */
}

/* 00000DEC-00000E14       .text actWarp__10daWarphr_cFi */
void daWarphr_c::actWarp(int) {
    /* Nonmatching */
}

/* 00000E14-00000F70       .text initWarpArrive__10daWarphr_cFi */
void daWarphr_c::initWarpArrive(int) {
    /* Nonmatching */
}

/* 00000FAC-00000FB4       .text actWarpArrive__10daWarphr_cFi */
void daWarphr_c::actWarpArrive(int) {
    /* Nonmatching */
}

/* 00000FB4-00000FE0       .text initWarpArriveEnd__10daWarphr_cFi */
void daWarphr_c::initWarpArriveEnd(int) {
    /* Nonmatching */
}

/* 00000FE0-00001048       .text actWarpArriveEnd__10daWarphr_cFi */
void daWarphr_c::actWarpArriveEnd(int) {
    /* Nonmatching */
}

/* 00001048-000010A4       .text eventOrder__10daWarphr_cFv */
void daWarphr_c::eventOrder() {
    /* Nonmatching */
}

/* 000010A4-0000115C       .text checkOrder__10daWarphr_cFv */
void daWarphr_c::checkOrder() {
    /* Nonmatching */
}

/* 0000115C-0000127C       .text anim_play__10daWarphr_cFi */
void daWarphr_c::anim_play(int) {
    /* Nonmatching */
}

/* 0000127C-000012F8       .text set_end_anim__10daWarphr_cFv */
void daWarphr_c::set_end_anim() {
    /* Nonmatching */
}

/* 000012F8-0000134C       .text get_return_count__10daWarphr_cFv */
void daWarphr_c::get_return_count() {
    /* Nonmatching */
}

/* 0000134C-000014F0       .text check_warp__10daWarphr_cFv */
void daWarphr_c::check_warp() {
    /* Nonmatching */
}

/* 000014F0-000016E0       .text _draw__10daWarphr_cFv */
bool daWarphr_c::_draw() {
    /* Nonmatching */
}

/* 000016E0-00001700       .text daWarphr_Create__FPv */
static s32 daWarphr_Create(void*) {
    /* Nonmatching */
}

/* 00001700-00001724       .text daWarphr_Delete__FPv */
static BOOL daWarphr_Delete(void*) {
    /* Nonmatching */
}

/* 00001724-00001748       .text daWarphr_Draw__FPv */
static BOOL daWarphr_Draw(void*) {
    /* Nonmatching */
}

/* 00001748-0000176C       .text daWarphr_Execute__FPv */
static BOOL daWarphr_Execute(void*) {
    /* Nonmatching */
}

/* 0000176C-00001774       .text daWarphr_IsDelete__FPv */
static BOOL daWarphr_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daWarphrMethodTable = {
    (process_method_func)daWarphr_Create,
    (process_method_func)daWarphr_Delete,
    (process_method_func)daWarphr_Execute,
    (process_method_func)daWarphr_IsDelete,
    (process_method_func)daWarphr_Draw,
};

actor_process_profile_definition g_profile_WARPHYRULE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_WARPHYRULE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daWarphr_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x01A5,
    /* Actor SubMtd */ &daWarphrMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
