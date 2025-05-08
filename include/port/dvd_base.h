#ifndef DVD_BASE_H
#define DVD_BASE_H

#include <dolphin/dvd/dvd.h>

extern u32 __DVDLongFileNameFlag;

class DVDBase {
public:
    // dvdfs
    virtual s32 DVDConvertPathToEntrynum(const char* pathPtr) = 0;
    virtual BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo) = 0;
    virtual BOOL DVDOpen(const char* fileName, DVDFileInfo* fileInfo) = 0;
    virtual BOOL DVDClose(DVDFileInfo* fileInfo) = 0;
    virtual BOOL DVDGetCurrentDir(char* path, u32 maxlen) = 0;
    virtual BOOL DVDChangeDir(const char* dirName) = 0;
    virtual BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio) = 0;
    virtual s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio) = 0;
    // virtual int DVDSeekAsyncPrio(DVDFileInfo* fileInfo, s32 offset, DVDCallback callback, s32 prio) = 0;
    // virtual s32 DVDSeekPrio(DVDFileInfo* fileInfo, s32 offset, s32 prio) = 0;
    // virtual s32 DVDGetFileInfoStatus(const DVDFileInfo* fileInfo) = 0;
    virtual BOOL DVDFastOpenDir(s32 entrynum, DVDDirectory* dir) = 0;
    virtual BOOL DVDOpenDir(const char* dirName, DVDDirectory* dir) = 0;
    virtual BOOL DVDReadDir(DVDDirectory* dir, DVDDirectoryEntry* dirent) = 0;
    virtual BOOL DVDCloseDir(DVDDirectory* dir) = 0;
    // virtual void DVDRewindDir(DVDDirectory* dir) = 0;
    // virtual void* DVDGetFSTLocation(void) = 0;
    // virtual BOOL DVDPrepareStreamAsync(DVDFileInfo* fileInfo, u32 length, u32 offset, DVDCallback callback) = 0;
    // virtual s32 DVDPrepareStream(DVDFileInfo* fileInfo, u32 length, u32 offset) = 0;
    // virtual s32 DVDGetTransferredSize(DVDFileInfo* fileinfo) = 0;

    // dvd
    // virtual BOOL DVDReadAbsAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCBCallback callback, s32 prio) = 0;
    // virtual int DVDSeekAbsAsyncPrio(DVDCommandBlock* block, s32 offset, DVDCBCallback callback, s32 prio) = 0;
    // virtual int DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback) = 0;
    // virtual int DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID, DVDCBCallback callback) = 0;
    // virtual int DVDPrepareStreamAbsAsync(DVDCommandBlock* block, u32 length, u32 offset, DVDCBCallback callback) = 0;
    // virtual int DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDCancelStream(DVDCommandBlock* block) = 0;
    // virtual int DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDStopStreamAtEnd(DVDCommandBlock* block) = 0;
    // virtual int DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDGetStreamErrorStatus(DVDCommandBlock* block) = 0;
    // virtual int DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDGetStreamPlayAddr(DVDCommandBlock* block) = 0;
    // virtual int DVDGetStreamStartAddrAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDGetStreamStartAddr(DVDCommandBlock* block) = 0;
    // virtual int DVDGetStreamLengthAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDGetStreamLength(DVDCommandBlock* block) = 0;
    // virtual int DVDChangeDiskAsyncForBS(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual int DVDChangeDiskAsync(DVDCommandBlock* block, DVDDiskID* id, DVDCBCallback callback) = 0;
    // virtual s32 DVDChangeDisk(DVDCommandBlock* block, DVDDiskID* id) = 0;
    // virtual int DVDStopMotorAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDStopMotor(DVDCommandBlock* block) = 0;
    // virtual int DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info, DVDCBCallback callback) = 0;
    // virtual s32 DVDInquiry(DVDCommandBlock* block, DVDDriveInfo* info) = 0;
    // virtual void DVDReset(void) = 0;
    // virtual int DVDResetRequired(void) = 0;
    // virtual s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block) = 0;
    // virtual s32 DVDGetDriveStatus(void) = 0;
    // virtual BOOL DVDSetAutoInvalidation(BOOL autoInval) = 0;
    // virtual void DVDPause(void) = 0;
    // virtual void DVDResume(void) = 0;
    // virtual int DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback) = 0;
    // virtual s32 DVDCancel(volatile DVDCommandBlock* block) = 0;
    // virtual int DVDCancelAllAsync(DVDCBCallback callback) = 0;
    // virtual s32 DVDCancelAll(void) = 0;
    // virtual DVDDiskID* DVDGetCurrentDiskID(void) = 0;
    // virtual BOOL DVDCheckDisk(void) = 0;
};

#endif
