
#include "global.h"
#include "dolphin/dvd/dvd.h"
#include <dolphin/os/OS.h>
#include "port/dvd_fs.h"
#include "port/dvd_iso.h"

static OSBootInfo* bootInfo;
u32 __DVDLongFileNameFlag;

static DVDBase* DVD;

int DVDConvertPathToEntrynum(const char* pathPtr) { return DVD->DVDConvertPathToEntrynum(pathPtr); }
BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo) { return DVD->DVDFastOpen(entrynum, fileInfo); }
BOOL DVDOpen(const char* fileName, DVDFileInfo* fileInfo) { return DVD->DVDOpen(fileName, fileInfo); }
BOOL DVDClose(DVDFileInfo* fileInfo) { return DVD->DVDClose(fileInfo); }
BOOL DVDChangeDir(const char* dir) { return DVD->DVDChangeDir(dir); }
BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio) { return DVD->DVDReadAsyncPrio(fileInfo, addr, length, offset, callback, prio); }
int DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio) { return DVD->DVDReadPrio(fileInfo, addr, length, offset, prio); }
BOOL DVDOpenDir(const char* dirName, DVDDirectory* dir) { return DVD->DVDOpenDir(dirName, dir); }
BOOL DVDReadDir(DVDDirectory* dir, DVDDirectoryEntry* dirent) { return DVD->DVDReadDir(dir, dirent); }
BOOL DVDCloseDir(DVDDirectory* dir) { return DVD->DVDCloseDir(dir); }

BOOL DVDPrepareStreamAsync(DVDFileInfo* fileinfo, u32 length, u32 offset, DVDCallback callback) { NOT_IMPLEMENTED; return 0; }

BOOL DVDInitialized;
const char* __DVDVersion = "<< Dolphin SDK - DVD\trelease build: " __DATE__ " " __TIME__ " (0x2301) >>";

void DVDInit(void) {
    if (DVDInitialized != 0) {
        return;
    }
    OSRegisterVersion(__DVDVersion);
    DVDInitialized = 1;
    bootInfo = (OSBootInfo*)OSPhysicalToCached(0);
    //DVD = new DVDFs("GZLE01/files");
    DVD = new DVDIso("D:\\Emulation\\Dolphin\\iso\\Legend of Zelda, The - The Wind Waker (USA).iso");
}

BOOL DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback) { NOT_IMPLEMENTED; return 0; }
BOOL DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback) { NOT_IMPLEMENTED; return 0; }
BOOL DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback) { NOT_IMPLEMENTED; return 0; }

s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block) {
    return 0;
}

s32 DVDGetDriveStatus(void) {
    return 0;
}

s32 DVDCancel(DVDCommandBlock* block) { NOT_IMPLEMENTED; return 0; }
DVDDiskID* DVDGetCurrentDiskID() { return &bootInfo->disk_info; }
BOOL DVDCheckDisk(void) { NOT_IMPLEMENTED; return 0; }
