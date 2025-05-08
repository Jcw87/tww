
#include "dolphin/os/OSReboot.h"

void* SaveStart;
void* SaveEnd;

void OSSetSaveRegion(void* start, void* end) {
	SaveStart = start;
	SaveEnd = end;
}