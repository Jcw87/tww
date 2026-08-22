#include "stdio.h"

#include "dolphin/gd.h"
#include "dolphin/gf.h"
#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "dolphin/vi.h"

#define NOT_IMPLEMENTED_CONTINUE                                                                                                                               \
    static bool reported = false;                                                                                                                              \
    if (!reported) {                                                                                                                                           \
        printf("stub %s\n", __FUNCSIG__);                                                                                                                    \
        reported = true;                                                                                                                                       \
    }

typedef enum _GXCopyMode {
    /* 0x0 */ GX_COPY_PROGRESSIVE,
    /* 0x1 */ GX_COPY_INTLC_EVEN,
    /* 0x2 */ GX_COPY_INTLC_ODD,
} GXCopyMode;

typedef GXTlutRegion* (*GXTlutRegionCallback)(u32 idx);

extern "C" {
    // GD
void __GDWrite(u8 data) { *__GDCurrentDL->ptr++ = data; }
void GDSetCurrent(GDLObj* obj) { __GDCurrentDL = obj; }
u32 GDGetGDLObjOffset(GDLObj* obj) { return (u32)(obj->ptr - obj->start); }
void* GDGetCurrPointer() { return __GDCurrentDL->ptr; }
u32 GDGetCurrOffset() { return __GDCurrentDL->ptr - __GDCurrentDL->start; }
void GDSetCurrOffset(s32 offs) { __GDCurrentDL->ptr = __GDCurrentDL->start + offs; }
void GDOverflowCheck(u32 len) { if (__GDCurrentDL->ptr + len > __GDCurrentDL->top) { GDOverflowed(); } }

// GXFifo
OSThread* GXSetCurrentGXThread() { NOT_IMPLEMENTED_CONTINUE; return NULL; }
OSThread* GXGetCurrentGXThread() { NOT_IMPLEMENTED_CONTINUE; return NULL; }

// GXMisc
void GXSetMisc(GXMiscToken token, u32 val) { NOT_IMPLEMENTED_CONTINUE; }
void GXResetWriteGatherPipe(void) { NOT_IMPLEMENTED_CONTINUE; }
void GXAbortFrame(void) { NOT_IMPLEMENTED_CONTINUE; }
void GXSetDrawSync(u16 token) { NOT_IMPLEMENTED_CONTINUE; }
void GXWaitDrawDone(void) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeAlphaMode(GXCompare func, u8 threshold) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeAlphaRead(GXAlphaReadMode mode) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeAlphaUpdate(GXBool update_enable) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeColorUpdate(GXBool update_enable) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeDstAlpha(GXBool enable, u8 alpha) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeDither(GXBool dither) { NOT_IMPLEMENTED_CONTINUE; }
void GXPokeZMode(GXBool compare_enable, GXCompare func, GXBool update_enable) { NOT_IMPLEMENTED_CONTINUE; }
void GXPeekARGB(u16 x, u16 y, u32* color) { NOT_IMPLEMENTED_CONTINUE; }
GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb) { NOT_IMPLEMENTED_CONTINUE; return cb; }

// GXFrameBuf
void GXSetDispCopyFrame2Field(GXCopyMode mode) { NOT_IMPLEMENTED_CONTINUE; }
void GXSetCopyClamp(GXFBClamp clamp) { NOT_IMPLEMENTED_CONTINUE; }
u16 GXGetNumXfbLines(u16 efbHeight, f32 yScale) { NOT_IMPLEMENTED_CONTINUE; return 0; }
f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight) { NOT_IMPLEMENTED_CONTINUE; return 0.0f; }
void GXClearBoundingBox(void) { NOT_IMPLEMENTED_CONTINUE; }

// GXTexture
void GXInitTexCacheRegion(GXTexRegion* region, GXBool is_32b_mipmap, u32 tmem_even, GXTexCacheSize size_even, u32 tmem_odd, GXTexCacheSize size_odd) { NOT_IMPLEMENTED_CONTINUE; }
void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize tlut_size) { NOT_IMPLEMENTED_CONTINUE; }
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback f) { NOT_IMPLEMENTED_CONTINUE; return NULL; }
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback f) { NOT_IMPLEMENTED_CONTINUE; return NULL; }

// GXTransform
void GXSetScissorBoxOffset(s32 x_off, s32 y_off) { NOT_IMPLEMENTED_CONTINUE; }

// GXPerf
void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1) { NOT_IMPLEMENTED_CONTINUE; }
void GXReadGPMetric(u32* cnt0, u32* cnt1) { NOT_IMPLEMENTED_CONTINUE; }
void GXClearGPMetric(void) { NOT_IMPLEMENTED_CONTINUE; }
u32 GXReadGP0Metric(void) { NOT_IMPLEMENTED_CONTINUE; return 0; }
u32 GXReadGP1Metric(void) { NOT_IMPLEMENTED_CONTINUE; return 0; }
void GXReadMemMetric(u32* cp_req, u32* tc_req, u32* cpu_rd_req, u32* cpu_wr_req, u32* dsp_req, u32* io_req, u32* vi_req, u32* pe_req, u32* rf_req, u32* fi_req) { NOT_IMPLEMENTED_CONTINUE; }
void GXClearMemMetric(void) { NOT_IMPLEMENTED_CONTINUE; }
void GXReadPixMetric(u32* top_pixels_in, u32* top_pixels_out, u32* bot_pixels_in, u32* bot_pixels_out, u32* clr_pixels_in, u32* copy_clks) { NOT_IMPLEMENTED_CONTINUE; }
void GXClearPixMetric(void) { NOT_IMPLEMENTED_CONTINUE; }
void GXSetVCacheMetric(GXVCachePerf attr) { NOT_IMPLEMENTED_CONTINUE; }
void GXReadVCacheMetric(u32* check, u32* miss, u32* stall) { NOT_IMPLEMENTED_CONTINUE; }
void GXClearVCacheMetric(void) { NOT_IMPLEMENTED_CONTINUE; }
void GXInitXfRasMetric(void) { NOT_IMPLEMENTED_CONTINUE; }
void GXReadXfRasMetric(u32* xf_wait_in, u32* xf_wait_out, u32* ras_busy, u32* clocks) { NOT_IMPLEMENTED_CONTINUE; }
u32 GXReadClksPerVtx(void) { NOT_IMPLEMENTED_CONTINUE; return 0; }

// VI
static u32 sRetraceCount = 0;
static VIRetraceCallback sVIPreRetraceCallback = NULL;
static VIRetraceCallback sVIPostRetraceCallback = NULL;

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback) {
    VIRetraceCallback old = sVIPostRetraceCallback;
    sVIPostRetraceCallback = callback;
    return old;
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb) {
    VIRetraceCallback old = sVIPreRetraceCallback;
    sVIPreRetraceCallback = cb;
    return old;
}

void VIWaitForRetrace() {
    sRetraceCount++;
    if (sVIPreRetraceCallback) {
        sVIPreRetraceCallback(sRetraceCount);
    }
    if (sVIPostRetraceCallback) {
        sVIPostRetraceCallback(sRetraceCount);
    }
}

void VISetNextFrameBuffer(void* fb) { NOT_IMPLEMENTED_CONTINUE; }
void VISetBlack(BOOL black) { NOT_IMPLEMENTED_CONTINUE; }
u32 VIGetRetraceCount() { return sRetraceCount; }
u32 VIGetNextField() { return 0; }
u32 VIGetDTVStatus(void) { return 0; }
}