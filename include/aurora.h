
#include <stdint.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_joystick.h>

typedef enum {
    SAMPLER_BILINEAR,
    SAMPLER_AREA,
} AuroraSampler;

typedef enum {
    BACKEND_AUTO,
    BACKEND_D3D11,
    BACKEND_D3D12,
    BACKEND_METAL,
    BACKEND_VULKAN,
    BACKEND_OPENGL,
    BACKEND_OPENGLES,
    BACKEND_WEBGPU,
    BACKEND_NULL,
} AuroraBackend;

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL,
} AuroraLogLevel;

typedef enum {
  /* Process GX commands asynchronously on a worker thread */
  GX_PROCESSING_THREAD,
  /* Process GX commands synchronously on the calling thread after each draw (useful for debugging) */
  GX_PROCESSING_INLINE,
  /* Process GX commands synchronously only when the FIFO is drained */
  GX_PROCESSING_DRAIN,
} AuroraGxProcessingMode;

typedef struct {
    int32_t x;
    int32_t y;
} AuroraWindowPos;

typedef struct {
    uint32_t width;
    uint32_t height;

    /**
   * Width of the main GX framebuffer.
   */
    uint32_t fb_width;

    /**
   * Height of the main GX framebuffer.
   */
    uint32_t fb_height;

    /**
   * The size of the framebuffer used to present to the operating system.
   * May differ from fb_width if Aurora is instructed to force an aspect ratio or resolution configuration.
   */
    uint32_t native_fb_width;

    /**
   * The size of the framebuffer used to present to the operating system.
   * May differ from fb_height if Aurora is instructed to force an aspect ratio or resolution configuration.
   */
    uint32_t native_fb_height;
    float scale;
} AuroraWindowSize;

typedef struct SDL_Window SDL_Window;
typedef struct AuroraEvent AuroraEvent;

typedef enum {
  /// Default: Aurora creates and manages an internal SDL_Window.
  AURORA_SURFACE_SDL_MANAGED = 0,
  /// HWND + optional HINSTANCE (Windows)
  AURORA_SURFACE_WIN32,
  /// CAMetalLayer* (macOS or iOS)
  AURORA_SURFACE_METAL_LAYER,
  /// NSView* (macOS)
  AURORA_SURFACE_COCOA_VIEW,
  /// Wayland wl_display* + wl_surface* (Linux)
  AURORA_SURFACE_WAYLAND,
  /// X11 Display* + Window XID (Linux)
  AURORA_SURFACE_X11,
  /// ANativeWindow* (Android)
  AURORA_SURFACE_ANDROID,
  /// No window or surface; EFB renders offscreen
  AURORA_SURFACE_HEADLESS,
} AuroraSurfaceType;

typedef struct {
  AuroraSurfaceType type;
  uint32_t width;  // Zero defaults to VIConfigure fbWidth
  uint32_t height; // Zero defaults to VIConfigure efbHeight
  float scale;     // Zero defaults to 1
  union {
    struct {
      void* hinstance; // HINSTANCE
      void* hwnd;      // HWND
    } win32;
    struct {
      void* layer; // CAMetalLayer*
    } metal;
    struct {
      void* nsView; // NSView*
    } cocoa;
    struct {
      void* display; // wl_display*
      void* surface; // wl_surface*
    } wayland;
    struct {
      void* display;   // Display*
      uint64_t window; // Window
    } x11;
    struct {
      void* window; // ANativeWindow*
    } android;
  };
} AuroraSurfaceDesc;

typedef void (*AuroraLogCallback)(AuroraLogLevel level, const char* module, const char* message, unsigned int len);
typedef void (*AuroraImGuiInitCallback)(const AuroraWindowSize* size);

typedef struct {
  const char* appName;
  const char* userPath;
  const char* cachePath;
  const char* resourcesPath;
  AuroraBackend desiredBackend;
  uint32_t msaa;
  uint16_t maxTextureAnisotropy;
  bool vsync;
  bool startFullscreen;
  bool allowJoystickBackgroundEvents;
  bool pauseOnFocusLost;
  bool allowTextureDumps;
  bool allowCpuAdapter;
  int32_t windowPosX;
  int32_t windowPosY;
  uint32_t windowWidth;
  uint32_t windowHeight;
  void* iconRGBA8;
  uint32_t iconWidth;
  uint32_t iconHeight;
  AuroraLogCallback logCallback;
  AuroraLogLevel logLevel;
  AuroraImGuiInitCallback imGuiInitCallback;
  AuroraGxProcessingMode gxProcessingMode;

  /*
   * The size of the GameCube's main memory, or MEM1 on the Wii.
   * Note that it will not be allocated at the exact 0x80000000 address, as that cannot be guaranteed.
   * This can be set to 0 to disable allocating this region.
   */
  uint32_t mem1Size;

  /*
   * The size of the GameCube's ARAM, or MEM2 on the Wii.
   * This can be set to 0 to disable allocating this region.
   */
  uint32_t mem2Size;

  AuroraSurfaceDesc surface;
} AuroraConfig;

typedef struct {
    AuroraBackend backend;
    const char* userPath;
    const char* cachePath;
    SDL_Window* window;
    AuroraWindowSize windowSize;
} AuroraInfo;

typedef enum {
    AURORA_NONE,
    AURORA_EXIT,
    AURORA_SDL_EVENT,
    AURORA_WINDOW_MOVED,
    AURORA_WINDOW_RESIZED,
    AURORA_CONTROLLER_ADDED,
    AURORA_CONTROLLER_REMOVED,
    AURORA_PAUSED,
    AURORA_UNPAUSED,
    AURORA_DISPLAY_SCALE_CHANGED,
} AuroraEventType;

struct AuroraEvent {
    AuroraEventType type;
    union {
        SDL_Event sdl;
        AuroraWindowPos windowPos;
        AuroraWindowSize windowSize;
        SDL_JoystickID controller;
    };
};

extern "C" {
AuroraInfo aurora_initialize(int argc, char* argv[], const AuroraConfig* config);
void aurora_shutdown();
const AuroraEvent* aurora_update();
bool aurora_begin_frame();
void aurora_end_frame();
}
