
#include <dolphin/os/OS.h>
#include "port/dvd_iso.h"
#include "ctype.h"
#include <algorithm>
#include <bit>

struct FSTEntry {
    u32 isDirAndStringOff;
    u32 parentOrPosition;
    u32 nextEntryOrLength;
};

static void byteswap(u32& val) { val = std::byteswap(val); }

static void byteswap(DVDBB2& bb2) {
    byteswap(bb2.bootFilePosition);
    byteswap(bb2.FSTPosition);
    byteswap(bb2.FSTLength);
    byteswap(bb2.FSTMaxLength);
}

static void byteswap(FSTEntry& entry) {
    byteswap(entry.isDirAndStringOff);
    byteswap(entry.parentOrPosition);
    byteswap(entry.nextEntryOrLength);
}

#define entryIsDir(i) (((FstStart[i].isDirAndStringOff & 0xff000000) == 0) ? FALSE : TRUE)
#define stringOff(i) (FstStart[i].isDirAndStringOff & ~0xff000000)
#define parentDir(i) (FstStart[i].parentOrPosition)
#define nextDir(i) (FstStart[i].nextEntryOrLength)
#define filePosition(i) (FstStart[i].parentOrPosition)
#define fileLength(i) (FstStart[i].nextEntryOrLength)

DVDIso::DVDIso(const char* path) {
    OSBootInfo* bootInfo = (OSBootInfo*)OSPhysicalToCached(0);
    DVDDiskID idTmp;
    DVDBB2 bb2;

    dvd_iso = fopen(path, "rb");
    fseek(dvd_iso, 0, SEEK_SET);
    fread(&idTmp, sizeof(DVDDiskID), 1, dvd_iso);
    fseek(dvd_iso, 0x0420, SEEK_SET);
    fread(&bb2, sizeof(DVDBB2), 1, dvd_iso);
    byteswap(bb2);

    bb2.FSTAddress = (void*)OSRoundDown32B(u32(bootInfo) + bootInfo->memory_size - bb2.FSTMaxLength);
    fseek(dvd_iso, bb2.FSTPosition, SEEK_SET);
    fread(bb2.FSTAddress, 1, bb2.FSTLength, dvd_iso);
    FSTEntry* entries = (FSTEntry*)bb2.FSTAddress;
    byteswap(entries[0]);
    for (int i = 1; i < entries[0].nextEntryOrLength; i++) {
        byteswap(entries[i]);
    }

    bootInfo->fst_location = bb2.FSTAddress;
    bootInfo->fst_max_length = bb2.FSTMaxLength;

    DVDDiskID* id = &bootInfo->disk_info;
    memcpy(id, &idTmp, sizeof(DVDDiskID));
    OSReport("\n");
    OSReport("  Game Name ... %c%c%c%c\n", id->game_name[0], id->game_name[1], id->game_name[2], id->game_name[3]);
    OSReport("  Company ..... %c%c\n", id->company[0], id->company[1]);
    OSReport("  Disk # ...... %d\n", id->disk_number);
    OSReport("  Game ver .... %d\n", id->game_version);
    OSReport("  Streaming ... %s\n", (id->is_streaming == 0) ? "OFF" : "ON");
    OSReport("\n");
    OSSetArenaHi(bb2.FSTAddress);

    FstStart = (FSTEntry*)bootInfo->fst_location;
    if (FstStart) {
        MaxEntryNum = nextDir(0);
        FstStringStart = (char*)&FstStart[MaxEntryNum];
    }
    else {
        MaxEntryNum = 0;
        FstStringStart = NULL;
    }
}

static BOOL isSame(const char* path, const char* string) {
    while (*string != '\0') {
        if (tolower(*path++) != tolower(*string++)) {
            return FALSE;
        }
    }

    if ((*path == '/') || (*path == '\0')) {
        return TRUE;
    }

    return FALSE;
}

s32 DVDIso::DVDConvertPathToEntrynum(const char* pathPtr) {
    const char* origPathPtr = pathPtr;
    u32 dirLookAt = currentDirectory;
    while (1) {
        if (pathPtr[0] == '\0') {
            return dirLookAt;
        } else if (pathPtr[0] == '/') {
            dirLookAt = 0;
            pathPtr++;
            continue;
        } else if (pathPtr[0] == '.') {
            if (pathPtr[1] == '.') {
                if (pathPtr[2] == '/') {
                    dirLookAt = parentDir(dirLookAt);
                    pathPtr += 3;
                    continue;
                } else if (pathPtr[2] == '\0') {
                    return parentDir(dirLookAt);
                }
            } else if (pathPtr[1] == '/') {
                pathPtr += 2;
                continue;
            } else if (pathPtr[1] == '\0') {
                return dirLookAt;
            }
        }
        const char* ptr;
        const char* extentionStart = NULL;
        BOOL extension;
        BOOL illegal;
        if (__DVDLongFileNameFlag == 0) {
            extension = FALSE;
            illegal = FALSE;

            for (ptr = pathPtr; ptr[0] != '\0' && ptr[0] != '/'; ptr++) {
                if (ptr[0] == '.') {
                    if (ptr - pathPtr > 8 || extension) {
                        illegal = TRUE;
                        break;
                    }
                    extension = TRUE;
                    extentionStart = ptr + 1;

                } else if (ptr[0] == ' ') {
                    illegal = TRUE;
                }
            }
            if ((extension == TRUE) && (ptr - extentionStart > 3)) {
                illegal = TRUE;
            }
            if (illegal) {
                OSPanic(__FILE__, __LINE__, "DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): specified directory or file (%s) doesn't match standard 8.3 format. This is a temporary restriction and will be removed soon\n", origPathPtr);
            }
        } else {
            for (ptr = pathPtr; ptr[0] != '\0' && ptr[0] != '/'; ptr++) { }
        }

        BOOL isDir = ptr[0] == '\0' ? FALSE : TRUE;
        u32 length = (u32)(ptr - pathPtr);
        ptr = pathPtr;

        s32 i;
        for (i = dirLookAt + 1; i < nextDir(dirLookAt); i = entryIsDir(i) ? nextDir(i) : (i + 1)) {
            if ((entryIsDir(i) == FALSE) && (isDir == TRUE)) {
                continue;
            }

            const char* stringPtr = FstStringStart + stringOff(i);
            if (isSame(ptr, stringPtr) == TRUE) {
                goto next_hier;
            }
        }
        return -1;
next_hier:
        if (!isDir) {
            return i;
        }
        dirLookAt = i;
        pathPtr += length + 1;
    }
}

BOOL DVDIso::DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo) {
    OSReport("DVDFastOpen: %li (%s)\n", entrynum, FstStringStart + stringOff(entrynum));
    if (entrynum < 0 || entrynum >= MaxEntryNum || entryIsDir(entrynum)) {
        return FALSE;
    }

    fileInfo->start_address = filePosition(entrynum);
    fileInfo->length = fileLength(entrynum);
    fileInfo->callback = NULL;
    fileInfo->block.state = DVD_STATE_END;

    return TRUE;
}

BOOL DVDIso::DVDOpen(const char* fileName, DVDFileInfo* fileInfo) {
    OSReport("DVDOpen: %s\n", fileName);
    s32 entry = DVDConvertPathToEntrynum(fileName);

    if (entry < 0) {
        char currentDir[0x80];
        DVDGetCurrentDir(currentDir, sizeof(currentDir));
        OSReport("Warning: DVDOpen(): file \'%s\' was not found under %s.\n", fileName, currentDir);
        return FALSE;
    }

    if (entryIsDir(entry)) {
        return FALSE;
    }

    fileInfo->start_address = filePosition(entry);
    fileInfo->length = fileLength(entry);
    fileInfo->callback = NULL;
    fileInfo->block.state = DVD_STATE_END;

    return TRUE;
}

BOOL DVDIso::DVDClose(DVDFileInfo* fileInfo) {
    return TRUE;
}

static u32 myStrncpy(char* dest, char* src, u32 maxlen) {
    u32 i = maxlen;

    while ((i > 0) && (*src != 0)) {
        *dest++ = *src++;
        i--;
    }

    return (maxlen - i);
}

u32 DVDIso::entryToPath(u32 entry, char* path, u32 maxlen) {
    char* name;
    u32 loc;

    if (entry == 0) {
        return 0;
    }

    name = FstStringStart + stringOff(entry);

    loc = entryToPath(parentDir(entry), path, maxlen);

    if (loc == maxlen) {
        return loc;
    }

    *(path + loc++) = '/';

    loc += myStrncpy(path + loc, name, maxlen - loc);

    return loc;
}

BOOL DVDIso::DVDConvertEntrynumToPath(s32 entrynum, char* path, u32 maxlen) {
    u32 loc = entryToPath((u32)entrynum, path, maxlen);

    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return FALSE;
    }

    if (entryIsDir(entrynum)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return FALSE;
        }

        path[loc++] = '/';
    }

    path[loc] = '\0';
    return TRUE;
}

BOOL DVDIso::DVDGetCurrentDir(char* path, u32 maxlen) {
    return DVDConvertEntrynumToPath(currentDirectory, path, maxlen);
}

BOOL DVDIso::DVDChangeDir(const char* dirName) {
    s32 entry = DVDConvertPathToEntrynum(dirName);

    if (entry < 0 || entryIsDir(entry) == FALSE) {
        return FALSE;
    }

    currentDirectory = entry;

    return TRUE;
}

static void cbForReadAsync(s32 result, DVDCommandBlock* block);

BOOL DVDIso::DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio) {
    if (offset < 0 || offset >= fileInfo->length) {
        OSPanic(__FILE__, __LINE__, "DVDReadAsync(): specified area is out of the file  ");
    }
    if (offset + length < 0 || offset + length >= fileInfo->length + 0x20) {
        OSPanic(__FILE__, __LINE__, "DVDReadAsync(): specified area is out of the file  ");
    }
    fileInfo->callback = callback;
    DVDReadAbsAsyncPrio(fileInfo, addr, length, fileInfo->start_address + offset, cbForReadAsync, prio);
    return true;
}

void cbForReadAsync(s32 result, DVDCommandBlock* block) {
    DVDFileInfo* fileInfo = (DVDFileInfo*)block;
    if (fileInfo->callback) {
        fileInfo->callback(result, fileInfo);
    }
}

static void cbForReadSync(s32 result, DVDCommandBlock* block);

s32 DVDIso::DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio) {
    if (offset < 0 || offset >= fileInfo->length) {
        OSPanic(__FILE__, __LINE__, "DVDRead(): specified area is out of the file  ");
    }
    if (offset + length < 0 || offset + length >= fileInfo->length + 0x20) {
        OSPanic(__FILE__, __LINE__, "DVDRead(): specified area is out of the file  ");
    }
    DVDReadAbsAsyncPrio(fileInfo, addr, length, fileInfo->start_address + offset, cbForReadSync, prio);
    return fileInfo->block.transferred_size;
}

static void cbForReadSync(s32 result, DVDCommandBlock* block) {};

BOOL DVDIso::DVDFastOpenDir(s32 entrynum, DVDDirectory* dir) {
    NOT_IMPLEMENTED_CONTINUE;
    return false;
}

BOOL DVDIso::DVDOpenDir(const char* param_1, DVDDirectory* param_2) {
    NOT_IMPLEMENTED_CONTINUE;
    return false;
}

BOOL DVDIso::DVDReadDir(DVDDirectory* param_1, DVDDirectoryEntry* param_2) {
    NOT_IMPLEMENTED_CONTINUE;
    return false;
}

BOOL DVDIso::DVDCloseDir(DVDDirectory* param_1) {
    NOT_IMPLEMENTED_CONTINUE;
    return false;
}

BOOL DVDIso::DVDReadAbsAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCBCallback callback, s32 prio) {
    fileInfo->block.command = 1;
    fileInfo->block.buffer = addr;
    fileInfo->block.length = length;
    fileInfo->block.offset = offset;
    fileInfo->block.transferred_size = 0;
    fileInfo->block.callback = callback;
    s32 fileOffset = offset - fileInfo->start_address;
    fseek(dvd_iso, offset, SEEK_SET);
    size_t readSize = std::min((s32)fileInfo->length - fileOffset, length);
    size_t actualReadSize = fread(addr, 1, readSize, dvd_iso);
    fileInfo->block.transferred_size = readSize == actualReadSize ? length : actualReadSize;
    callback(fileInfo->block.transferred_size, &fileInfo->block);
    return true;
}