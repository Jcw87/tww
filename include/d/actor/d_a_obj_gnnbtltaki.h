#ifndef D_A_OBJ_GNNBTLTAKI_H
#define D_A_OBJ_GNNBTLTAKI_H

#include "f_op/f_op_actor.h"

class daObjGnnbtaki_c : public fopAc_ac_c {
public:
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void _create();
    void _delete();
    void init_mtx();
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_GNNBTLTAKI_H */
