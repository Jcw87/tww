
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dolphin/os/OS.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSArena.h>
#include <dolphin/os/OSError.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

void OSRegisterVersion(const char* version);

extern u32 __DVDLongFileNameFlag;

static OSBootInfo* BootInfo;
bool AreWeInitialized;
const char* __OSVersion = "<< Dolphin SDK - OS\trelease build: " __DATE__ " " __TIME__ " (0x2301) >>";

u32 OSGetConsoleType() {
    return BootInfo->console_type;
}

void ClearArena() {
    void* lo = OSGetArenaLo();
    void* hi = OSGetArenaHi();
    size_t size = (size_t)hi - (size_t)lo;
    memset(lo, 0, size);
}

void __OSThreadInit();

static u8* RAM;

void OSInit() {
    if (AreWeInitialized) {
        return;
    }
    AreWeInitialized = true;

    BootInfo = (OSBootInfo*)OSPhysicalToCached(0);
    __DVDLongFileNameFlag = 1;

    OSSetArenaLo(BootInfo->arena_lo ? BootInfo->arena_lo : OSPhysicalToCached(0x0040cfc0));
    OSSetArenaHi(BootInfo->arena_hi ? BootInfo->arena_hi : OSPhysicalToCached(0x01700000));
    OSInitAlarm();
    __OSThreadInit();
    OSReport("\nDolphin OS $Revision: 58 $.\n");
    OSReport("Kernel built : %s %s\n", __DATE__, __TIME__);
    OSReport("Console Type : ");
    u32 type = OSGetConsoleType();
    bool dev = (type & 0xffff0000) > 0;
    int rev = (type & 0x0000ffff);
    if (!dev) {
        OSReport("Retail %d\n", type);
    } else {
        switch (rev) {
        case 0:
            OSReport("Mac Emulator\n");
            break;
        case 1:
            OSReport("PC Emulator\n");
            break;
        case 2:
            OSReport("EPPC Arthur\n");
            break;
        case 3:
            OSReport("EPPC Minnow\n");
            break;
        default:
            OSReport("Development HW%d (%08x)\n", rev - 3, type);
            break;
        }
    }
    OSReport("Memory %d MB\n", BootInfo->memory_size / (1024 * 1024));
    OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());
    OSRegisterVersion(__OSVersion);
    ClearArena();
    DVDInit();
}

void OSRegisterVersion(const char* version) {
    OSReport("%s\n", version);
}

void* OSPhysicalToCached(u32 paddr) { return RAM + paddr; }
void* OSPhysicalToUncached(u32 paddr) { return RAM + paddr; }
u32 OSCachedToPhysical(void* caddr) { return (u8*)caddr - RAM; }
u32 OSUncachedToPhysical(void* ucaddr) { return (u8*)ucaddr - RAM; }
void* OSCachedToUncached(void* caddr) { return caddr; }
void* OSUncachedToCached(void* ucaddr) { return ucaddr; }

#ifdef _WIN32
void PrintLastError() {
    DWORD errorMessageID = GetLastError();
    if (errorMessageID == 0) {
        return;
    }
    wchar_t buffer[1024];
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorMessageID,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buffer, 1024, NULL);
    wprintf(buffer);
}

void* AllocAt(void* address, u32 size) {
    void* ram = VirtualAlloc(address, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!ram) {
        PrintLastError();
    }
    return ram;
}
#else
void* AllocAt(void* address, u32 size) { return malloc(size); }
#endif

void OSInitRAM(u32 size) {
    if (RAM) {
        return;
    }
    size = size ? size : 1024 * 1024 * 24;
    RAM = (u8*)AllocAt((void*)0x80000000, size);
    if (!RAM) {
        OSPanic(__FILE__, __LINE__, "Failed to allocate system RAM");
    }
    OSBootInfo* bootInfo = (OSBootInfo*)OSPhysicalToCached(0);
    memcpy(bootInfo->disk_info.game_name, "GZLE", 4);
    memcpy(bootInfo->disk_info.company, "01", 2);
    bootInfo->disk_info.game_name;
    bootInfo->boot_code = 0x0d15ea5e;
    bootInfo->version = 1;
    bootInfo->memory_size = size;
    bootInfo->console_type = OS_CONSOLE_PC_EMULATOR;
}
