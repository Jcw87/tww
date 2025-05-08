
#include "port/dvd_fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include "minimal_windows.h"
#include <direct.h>
#include <fileapi.h>
#else
#include <unistd.h>
#endif

DVDFs::DVDFs(const char* path) {
    chdir(path);
    if (getcwd(s_rootDir, sizeof(s_rootDir)) == NULL) {
        exit(1);
    }
}

s32 DVDFs::DVDConvertPathToEntrynum(const char* pathPtr) {
    int i;
    FILE* f;
    char absolute[PATH_MAX];

    printf("DVDConvertPathToEntrynum: %s\n", pathPtr);
#ifdef _WIN32
    if (GetFullPathNameA(pathPtr, sizeof(absolute), absolute, NULL) == 0)
        return -1;
#else
    if (realpath(pathPtr, absolute) == NULL)
        return -1;
#endif
    for (i = 0; i < s_pathEntriesCount; i++) {
        if (strcmp(absolute, s_pathEntries[i]) == 0)
            return i;
    }

    if (strlen(absolute) + 1 > PATH_MAX)
        return -1;

    // check if file exists
    f = fopen(absolute, "rb");
    if (f == NULL)
        return -1;
    fclose(f);

    // add new entry
    printf("size = %i\n", sizeof(*s_pathEntries));
    s_pathEntries = (char(*)[256])realloc(s_pathEntries, (s_pathEntriesCount + 1) * sizeof(*s_pathEntries));
    strcpy(s_pathEntries[s_pathEntriesCount], absolute);
    return s_pathEntriesCount++;
}

BOOL DVDFs::DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo) {
    printf("DVDFastOpen: %li\n", entrynum);
    if (entrynum < s_pathEntriesCount) {
        return DVDOpen(s_pathEntries[entrynum], fileInfo);
    }
    return FALSE;
}

BOOL DVDFs::DVDOpen(const char* fileName, DVDFileInfo* fileInfo) {
    FILE* f;

    printf("DVDOpen: %s\n", fileName);
    f = fopen(fileName, "rb");
    if (f == NULL) {
        puts("open failed\n");
        return FALSE;
    }
    fileInfo->block.buffer = f;
    fseek(f, 0, SEEK_END);
    fileInfo->length = ftell(f);
    return TRUE;
}

BOOL DVDFs::DVDClose(DVDFileInfo* fileInfo) {
    FILE* f = (FILE*)fileInfo->block.buffer;

    if (f != NULL) {
        fclose(f);
    }
    fileInfo->block.buffer = NULL;
    return TRUE;
}

BOOL DVDFs::DVDGetCurrentDir(char* path, u32 maxlen) {
    NOT_IMPLEMENTED_CONTINUE;
    return false;
}

BOOL DVDFs::DVDChangeDir(const char* dir) {
    printf("DVDChangeDir: %s\n", dir);
    if (dir[0] == '/') {
        char path[PATH_MAX];
        if (snprintf(path, sizeof(path), "%s/%s", s_rootDir, dir) >= PATH_MAX) {
            return FALSE;
        }
        return chdir(path) == 0;
    }
    else {
        return chdir(dir) == 0;
    }
}

BOOL DVDFs::DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio) {
    FILE* f = (FILE*)fileInfo->block.buffer;
    BOOL success;

    printf("DVDReadAsyncPrio: length %li, offset %li\n", length, offset);
    fseek(f, offset, SEEK_SET);
    success = (fread(addr, length, 1, f) == 1) || feof(f);
    if (!success)
        puts("read failed");
    callback(success ? 0 : -1, fileInfo);
    return TRUE;
}

s32 DVDFs::DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio) {
    FILE* f = (FILE*)fileInfo->block.buffer;
    BOOL success;

    printf("DVDReadPrio: length %li, offset %li\n", length, offset);
    fseek(f, offset, SEEK_SET);
    success = (fread(addr, length, 1, f) == 1) || feof(f);
    if (!success)
        puts("read failed");
    return TRUE;
}

BOOL DVDFs::DVDFastOpenDir(s32 entrynum, DVDDirectory* dir) {
    NOT_IMPLEMENTED_CONTINUE;
    return FALSE;
}

BOOL DVDFs::DVDOpenDir(const char* dirName, DVDDirectory* dir) {
    NOT_IMPLEMENTED_CONTINUE;
    return FALSE;
}

BOOL DVDFs::DVDReadDir(DVDDirectory* dir, DVDDirectoryEntry* dirent) {
    NOT_IMPLEMENTED_CONTINUE;
    return FALSE;
}

BOOL DVDFs::DVDCloseDir(DVDDirectory* dir) {
    NOT_IMPLEMENTED_CONTINUE;
    return FALSE;
}
