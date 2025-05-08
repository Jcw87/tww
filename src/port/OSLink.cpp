
#include "global.h"

#include <dolphin/os/OSLink.h>

OSModuleQueue __OSModuleList;

void OSNotifyLink() {
    NOT_IMPLEMENTED;
}

void OSNotifyUnlink() {
    NOT_IMPLEMENTED;
}

void OSSetStringTable(void* param_1) {
	NOT_IMPLEMENTED_CONTINUE;
}

BOOL OSLink(OSModuleInfo* param_1, void* param_2) {
    NOT_IMPLEMENTED;
    return false;
}

BOOL OSLinkFixed(OSModuleInfo* param_1, void* param_2) {
    NOT_IMPLEMENTED;
    return false;
}

BOOL OSUnlink(OSModuleInfo* param_1) {
    NOT_IMPLEMENTED;
    return false;
}
