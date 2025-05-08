
#include "global.h"
#include "dolphin/dsp.h"

DSPTaskInfo* __DSP_tmp_task;
DSPTaskInfo* __DSP_last_task;
DSPTaskInfo* __DSP_first_task;
DSPTaskInfo* __DSP_curr_task;

u32 DSPCheckMailToDSP() { NOT_IMPLEMENTED_CONTINUE; return 0; }
u32 DSPCheckMailFromDSP() { NOT_IMPLEMENTED_CONTINUE; return 0; }
u32 DSPReadMailFromDSP() { NOT_IMPLEMENTED_CONTINUE; return 0; }
void DSPSendMailToDSP(u32 mail) { NOT_IMPLEMENTED_CONTINUE; }
void DSPAssertInt() { NOT_IMPLEMENTED_CONTINUE; }
void DSPInit() { NOT_IMPLEMENTED_CONTINUE; }

void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next) { NOT_IMPLEMENTED_CONTINUE; }
void __DSP_boot_task(DSPTaskInfo* task) { NOT_IMPLEMENTED_CONTINUE; }
void __DSP_insert_task(DSPTaskInfo* task) { NOT_IMPLEMENTED_CONTINUE; }
void __DSP_remove_task(DSPTaskInfo* task) { NOT_IMPLEMENTED_CONTINUE; }
