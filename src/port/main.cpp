
#include <dolphin/os/OS.h>

#if _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

void OSInitRAM(u32 size);
int gc_main(int argc, const char* argv[]);

int main(int argc, const char* argv[]) {
#ifdef _WIN32
    //const UINT codepage = 932;
    const UINT codepage = CP_UTF8;
    if (IsValidCodePage(codepage)) {
        SetConsoleOutputCP(codepage);
    }
#endif
    OSInitRAM(0);
    OSInit();
    DVDDiskID* disk = DVDGetCurrentDiskID();
    disk->game_version = 0xff; // will enable developer mode
    gc_main(argc, argv);
}
