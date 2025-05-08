#ifndef DVD_FS_H
#define DVD_FS_H

#include "port/dvd_base.h"

#ifndef PATH_MAX
#define PATH_MAX 256
#endif

class DVDFs : public DVDBase {
public:
    DVDFs(const char* path);
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
    char (*s_pathEntries)[PATH_MAX] = NULL;
    int s_pathEntriesCount = 0;
    char s_rootDir[PATH_MAX];
};

#endif
