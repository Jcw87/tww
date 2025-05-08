#ifndef JAIINITDATA_H
#define JAIINITDATA_H

#include "dolphin/types.h"
#include "port/byteswap.h"

namespace JAInter {
    namespace InitData {
        BOOL checkInitDataFile();
        void checkInitDataOnMemory();

        extern BE(u32)* aafPointer;
    };
}

#endif /* JAIINITDATA_H */
