
#include <dolphin/os/OS.h>
#include <dolphin/gx/GXGeometry.h>
#include "aurora.h"
#include <string>

#if _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#undef GXBegin
#undef GXEnd

static bool sBegin = false;
static const char* sFile = NULL;
static int sLine = 0;
void GXBeginDebug(GXPrimitive type, GXVtxFmt fmt, u16 vert_num, const char* file, int line) {
    if (sBegin) {
        OSReport("GXBegin without end %s:%d\n", sFile, sLine);
    }
    sBegin = true;
    sFile = file;
    sLine = line;
    GXBegin(type, fmt, vert_num);
}
void GXEndDebug() {
    sBegin = false;
    sFile = NULL;
    sLine = 0;
    GXEnd();
}

void OSInitRAM(u32 size);
int gc_main(int argc, const char* argv[]);

static constexpr std::string_view log_ignore[] = {
    "is not supported",
    "Unhandled BP register",
    "Unhandled XF register",
    "Unhandled XF memory write",
};

bool should_ignore(const char* message) {
    std::string_view msg_view(message);

    for (int i = 0; i < ARRAY_SIZE(log_ignore); i++) {
        if (msg_view.find(log_ignore[i]) != std::string_view::npos) {
            return true;
        }
    }

    return false;
}

static void log_callback(AuroraLogLevel level, const char* module, const char* message, unsigned int len) {
    if (should_ignore(message)) {
        return;
    }

    const char* levelStr;
    FILE* out = stdout;
    switch (level) {
        case LOG_DEBUG:
            levelStr = "DEBUG";
            break;
        case LOG_INFO:
            levelStr = "INFO";
            break;
        case LOG_WARNING:
            levelStr = "WARNING";
            break;
        case LOG_ERROR:
            levelStr = "ERROR";
            out = stderr;
            break;
        case LOG_FATAL:
            levelStr = "FATAL";
            out = stderr;
            break;
    }
    fprintf(out, "[%s: %s;%s]\n", levelStr, module, message);
    if (level == LOG_FATAL) {
        fflush(out);
        abort();
    }
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    //const UINT codepage = 932;
    const UINT codepage = CP_UTF8;
    if (IsValidCodePage(codepage)) {
        SetConsoleOutputCP(codepage);
    }
#endif
    OSInitRAM(0);
    OSInit();

    AuroraConfig config = {};
    config.appName = "Wind Waker";
    config.desiredBackend = BACKEND_VULKAN;
    config.windowPosX = -1;
    config.windowPosY = -1;
    config.windowWidth = 640;
    config.windowHeight = 480;
    config.logCallback = &log_callback;
    AuroraInfo initInfo = aurora_initialize(argc, argv, &config);

    DVDDiskID* disk = DVDGetCurrentDiskID();
    disk->game_version = 0xff; // will enable developer mode
    gc_main(argc, (const char**)argv);
    aurora_shutdown();
}
