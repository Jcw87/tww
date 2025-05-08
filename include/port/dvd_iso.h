#ifndef DVD_ISO_H
#define DVD_ISO_H

#include "port/dvd_base.h"
#include <stdio.h>

struct FSTEntry;

class DVDIso : public DVDBase {
public:
    DVDIso(const char* path);
    virtual s32 DVDConvertPathToEntrynum(const char* pathPtr);
    virtual BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo);
    virtual BOOL DVDOpen(const char* fileName, DVDFileInfo* fileInfo);
    virtual BOOL DVDClose(DVDFileInfo* fileInfo);
    virtual BOOL DVDGetCurrentDir(char* path, u32 maxlen);
    virtual BOOL DVDChangeDir(const char* dirName);
    virtual BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio);
    virtual s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);
    virtual BOOL DVDFastOpenDir(s32 entrynum, DVDDirectory* dir);
    virtual BOOL DVDOpenDir(const char* dirName, DVDDirectory* dir);
    virtual BOOL DVDReadDir(DVDDirectory* dir, DVDDirectoryEntry* dirent);
    virtual BOOL DVDCloseDir(DVDDirectory* dir);

private:
    u32 entryToPath(u32 entry, char* path, u32 maxlen);
    BOOL DVDConvertEntrynumToPath(s32 entrynum, char* path, u32 maxlen);
    BOOL DVDReadAbsAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCBCallback callback, s32 prio);

    FILE* dvd_iso;
    FSTEntry* FstStart;
    char* FstStringStart;
    u32 MaxEntryNum;
    u32 currentDirectory = 0;
};

#endif
