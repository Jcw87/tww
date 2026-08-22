
#include "global.h"
#include "dolphin/gx/GX.h"
#include "dolphin/gx/GXInit.h"

#undef GXBegin
#undef GXEnd

// GXInit
GXFifoObj* GXInit(void* base, u32 size) { return 0; }

// GXFifo
void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size) { }
void GXInitFifoPtrs(GXFifoObj* fifo, void* read_ptr, void* write_ptr) { }
void GXSetCPUFifo(GXFifoObj* fifo) { }
void GXSetGPFifo(GXFifoObj* fifo) { }
void GXSaveCPUFifo(GXFifoObj* fifo) { }
void GXGetGPStatus(GXBool* overhi, GXBool* underlo, GXBool* read_idle, GXBool* cmd_idle, GXBool* breakpoint) { }
OSThread* GXSetCurrentGXThread() { return 0; }
OSThread* GXGetCurrentGXThread() { return 0; }
GXFifoObj* GXGetCPUFifo() { return 0; }
GXFifoObj* GXGetGPFifo() { return 0; }

// GXAttr
void GXSetVtxDesc(GXAttr attr, GXAttrType type) { }
void GXClearVtxDesc(void) { }
void GXSetVtxAttrFmt(GXVtxFmt fmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac) { }
void GXSetVtxAttrFmtv(GXVtxFmt fmt, GXVtxAttrFmtList* list) { }
void GXGetVtxAttrFmt(GXVtxFmt param_0, int param_1, GXCompCnt* param_2, GXCompType* param_3, u8* param_4) { }
void GXGetVtxAttrFmtv(GXVtxFmt param_0, GXVtxAttrFmtList* param_1) { }
void GXSetArray(GXAttr attr, void* basePtr, u8 stride) { }
void GXInvalidateVtxCache(void) { }
void GXSetTexCoordGen2(GXTexCoordID dst, GXTexGenType type, GXTexGenSrc src, u32 mtx, GXBool renormalize, u32 pt_mtx) { }
void GXSetNumTexGens(u8 numTexGens) { }

// GXMisc
void GXSetMisc(GXMiscToken token, u32 val) { }
void GXFlush() { }
void GXAbortFrame() { }
void GXSetDrawSync(u16 token) { }
void GXSetDrawDone() { }
void GXDrawDone() { }
void GXPixModeSync() { }
void GXPokeAlphaMode(GXCompare comp, u8 threshold) { }
void GXPokeAlphaRead(GXAlphaReadMode mode) { }
void GXPokeAlphaUpdate(GXBool enable_update) { }
void GXPokeBlendMode(GXBlendMode mode, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op) { }
void GXPokeColorUpdate(GXBool enable_update) { }
void GXPokeDstAlpha(GXBool enable, u8 alpha) { }
void GXPokeDither(GXBool enable) { }
void GXPokeZMode(GXBool enable_compare, GXCompare comp, GXBool update_enable) { }
void GXPeekARGB(u16 x, u16 y, u32* color) { }
void GXPeekZ(u16 x, u16 y, u32* z) { }
GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback callback) { return 0; }
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback callback) { return 0; }

// GXGeometry
void GXBegin(GXPrimitive type, GXVtxFmt fmt, u16 vert_num) { }
void GXEnd() { }
void GXSetLineWidth(u8 width, GXTexOffset offsets) { }
void GXSetPointSize(u8 size, GXTexOffset offsets) { }
void GXEnableTexOffsets(GXTexCoordID coord, GXBool line, GXBool point) { }
void GXSetCullMode(GXCullMode mode) { }
void GXSetCoPlanar(GXBool enable) { }

// GXFrameBuf
GXRenderModeObj GXNtsc480IntDf = {
    VI_TVMODE_NTSC_INT,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFBMODE_DF,
    GX_FALSE,
    GX_FALSE,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    8,
    8,
    10,
    12,
    10,
    8,
    8,
};

GXRenderModeObj GXNtsc480Int = {
    VI_TVMODE_NTSC_INT,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    VI_XFBMODE_DF,
    GX_FALSE,
    GX_FALSE,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    6,
    0,
    0,
    21,
    22,
    21,
    0,
    0,
};

void GXSetDispCopySrc(u16 left, u16 top, u16 width, u16 height) { }
void GXSetTexCopySrc(u16 left, u16 top, u16 width, u16 height) { }
void GXSetDispCopyDst(u16 arg0, u16 arg1) { }
void GXSetTexCopyDst(u16 width, u16 height, GXTexFmt format, GXBool useMIPmap) { }
void GXSetDispCopyFrame2Field(GXCopyMode mode) { }
void GXSetCopyClamp(GXFBClamp clamp) { }
u16 GXGetNumXfbLines(u16 efb_height, f32 y_scale) { return 0; }
f32 GXGetYScaleFactor(u16 efb_height, u16 xfb_height) { return 0; }
u32 GXSetDispCopyYScale(f32 y_scale) { return 0; }
void GXSetCopyClear(GXColor color, u32 clear_z) { }
void GXSetCopyFilter(GXBool antialias, u8 pattern[12][2], GXBool vf, u8 vfilter[7]) { }
void GXSetDispCopyGamma(GXGamma gamma) { }
void GXCopyDisp(void* dst, GXBool clear) { }
void GXCopyTex(void* dst, GXBool clear) { }
void GXClearBoundingBox(void) { }

// GXLight
void GXInitLightAttn(GXLightObj* obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2) { }
void GXInitLightSpot(GXLightObj* obj, f32 cutoff, GXSpotFn spot_fn) { }
void GXInitLightDistAttn(GXLightObj* obj, f32 dist, f32 brightness, GXDistAttnFn dist_fn) { }
void GXInitLightPos(GXLightObj* obj, f32 x, f32 y, f32 z) { }
void GXInitLightDir(GXLightObj* obj, f32 x, f32 y, f32 z) { }
void GXInitLightColor(GXLightObj* obj, GXColor color) { }
void GXLoadLightObjImm(GXLightObj* obj, GXLightID light) { }
void GXSetChanAmbColor(GXChannelID channel, GXColor color) { }
void GXSetChanMatColor(GXChannelID channel, GXColor color) { }
void GXSetNumChans(u8 chan_num) { }
void GXSetChanCtrl(GXChannelID channel, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn) { }

// GXTexture
static void __GXGetTexTileShift(u32 fmt, u32* rowTileS, u32* colTileS) {
    switch (fmt) {
    case GX_TF_I4:
    case GX_TF_C4:
    case GX_TF_CMPR:
    case GX_CTF_R4:
    case GX_CTF_Z4:
        *rowTileS = 3;
        *colTileS = 3;
        break;
    case GX_TF_I8:
    case GX_TF_IA4:
    case GX_TF_C8:
    case GX_TF_Z8:
    case GX_CTF_RA4:
    case GX_CTF_A8:
    case GX_CTF_R8:
    case GX_CTF_G8:
    case GX_CTF_B8:
    case GX_CTF_Z8M:
    case GX_CTF_Z8L:
        *rowTileS = 3;
        *colTileS = 2;
        break;
    case GX_TF_IA8:
    case GX_TF_RGB565:
    case GX_TF_RGB5A3:
    case GX_TF_RGBA8:
    case GX_TF_C14X2:
    case GX_TF_Z16:
    case GX_TF_Z24X8:
    case GX_CTF_RA8:
    case GX_CTF_RG8:
    case GX_CTF_GB8:
    case GX_CTF_Z16L:
        *rowTileS = 2;
        *colTileS = 2;
        break;
    default:
        *rowTileS = *colTileS = 0;
        break;
    }
}

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, GXBool mipmap, u8 max_lod) {
    u32 tileShiftX;
    u32 tileShiftY;
    u32 tileBytes;
    u32 bufferSize;
    u32 nx;
    u32 ny;
    u32 level;

    __GXGetTexTileShift(format, &tileShiftX, &tileShiftY);
    if (format == GX_TF_RGBA8 || format == GX_TF_Z24X8) {
        tileBytes = 64;
    } else {
        tileBytes = 32;
    }

    if (mipmap == GX_TRUE) {
        bufferSize = 0;
        for (level = 0; level < max_lod; level++) {
            nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
            ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
            bufferSize += tileBytes * (nx * ny);
            if (width == 1 && height == 1) {
                break;
            }
            width = (width > 1) ? width >> 1 : 1;
            height = (height > 1) ? height >> 1 : 1;
        }
    } else {
        nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
        ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
        bufferSize = nx * ny * tileBytes;
    }

    return bufferSize;
}

void GXInitTexObj(GXTexObj* obj, void* image, u16 width, u16 height, GXTexFmt fmt, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXBool mipmap) { }
void GXInitTexObjCI(GXTexObj* obj, void* image, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXBool mipmap, u32 tlut_name) { }
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filter, GXTexFilter max_filter, f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp, GXBool edge_lod, GXAnisotropy aniso) { }
void* GXGetTexObjData(GXTexObj* obj) { return 0; }
u16 GXGetTexObjWidth(const GXTexObj* obj) { return 0; }
u16 GXGetTexObjHeight(const GXTexObj* obj) { return 0; }
GXTexFmt GXGetTexObjFmt(const GXTexObj* obj) { return GX_TF_I4; }
GXTexWrapMode GXGetTexObjWrapS(GXTexObj* obj) { return GX_CLAMP; }
GXTexWrapMode GXGetTexObjWrapT(GXTexObj* obj) { return GX_CLAMP; }
u32 GXGetTexObjTlut(GXTexObj* obj) { return 0; }
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id) { }
void GXInitTlutObj(GXTlutObj* obj, void* lut, GXTlutFmt fmt, u16 entry_num) { }
void GXLoadTlut(GXTlutObj* obj, u32 tlut_name) { }
void GXInitTexCacheRegion(GXTexRegion* region, GXBool is_32b_mipmap, u32 tmem_even, GXTexCacheSize size_even, u32 tmem_odd, GXTexCacheSize size_odd) { }
void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize tlut_size) { }
void GXInvalidateTexAll(void) { }
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback callback) { return 0; }
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback callback) { return 0; }
void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 s_scale, u16 t_scale) { }
void GXSetTexCoordBias(GXTexCoordID coord, GXBool s_enable, GXBool t_enable) { }

// GXBump
void GXSetTevIndirect(GXTevStageID tevStage, GXIndTexStageID texStage, GXIndTexFormat texFmt, GXIndTexBiasSel biasSel, GXIndTexMtxID mtxID, GXIndTexWrap wrapS, GXIndTexWrap wrapT, u8 addPrev, u8 utcLod, GXIndTexAlphaSel alphaSel) { }
void GXSetIndTexMtx(GXIndTexMtxID mtxID, f32 offset[6], s8 scale_exp) { }
void GXSetIndTexCoordScale(GXIndTexStageID texStage, GXIndTexScale scaleS, GXIndTexScale scaleT) { }
void GXSetIndTexOrder(GXIndTexStageID stage, GXTexCoordID coord, GXTexMapID map) { }
void GXSetNumIndStages(u8 num) { }
void GXSetTevDirect(GXTevStageID stage) { }
void GXSetTevIndWarp(GXTevStageID tevStage, GXIndTexStageID texStage, GXBool, GXBool, GXIndTexMtxID mtxID) { }

// GXTev
void GXSetTevOp(GXTevStageID id, GXTevMode mode) { }
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d) { }
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d) { }
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg) { }
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg) { }
void GXSetTevColor(GXTevRegID id, GXColor color) { }
void GXSetTevColorS10(GXTevRegID id, GXColorS10 color) { }
void GXSetTevKColor(GXTevKColorID id, GXColor color) { }
void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel color_sel) { }
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel alpha_sel) { }
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel) { }
void GXSetTevSwapModeTable(GXTevSwapSel select, GXTevColorChan r, GXTevColorChan g, GXTevColorChan b, GXTevColorChan a) { }
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1) { }
void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias) { }
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color) { }
void GXSetNumTevStages(u8 num_stages) { }

// GXPixel
void GXSetFog(GXFogType type, f32 startZ, f32 endZ, f32 nearZ, f32 farZ, GXColor color) { }
void GXSetFogRangeAdj(GXBool enable, u16 center, GXFogAdjTable* table) { }
void GXSetBlendMode(GXBlendMode mode, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op) { }
void GXSetColorUpdate(GXBool enable_update) { }
void GXSetAlphaUpdate(GXBool enable_update) { }
void GXSetZMode(GXBool enable_compare, GXCompare comp, GXBool enable_update) { }
void GXSetZCompLoc(GXBool z_buf_before_tex) { }
void GXSetPixelFmt(GXPixelFmt pixel_fmt, GXZFmt16 z_fmt) { }
void GXSetDither(GXBool enable_dither) { }
void GXSetDstAlpha(GXBool enable, u8 alpha) { }
void GXSetFieldMask(GXBool odd_mask, GXBool even_mask) { }
void GXSetFieldMode(GXBool field_mode, GXBool half_aspect_ratio) { }

// GXDisplayList
void GXCallDisplayList(void* list, u32 nbytes) { }

// GXTransform
void GXProject(f32 model_x, f32 model_y, f32 model_z, Mtx model_mtx, f32* proj, f32* viewpoint, f32* screen_x, f32* screen_y, f32* screen_z) { }
void GXSetProjection(const Mtx44 proj, GXProjectionType type) { }
void GXSetProjectionv(f32* p) { }
void GXGetProjectionv(f32* p) { }
void GXLoadPosMtxImm(Mtx mtx, u32 id) { }
void GXLoadNrmMtxImm(Mtx mtx, u32 id) { }
void GXSetCurrentMtx(u32 id) { }
void GXLoadTexMtxImm(const Mtx mtx, u32 id, GXTexMtxType type) { }
void GXSetViewport(f32 x_orig, f32 y_orig, f32 width, f32 height, f32 near_z, f32 far_z) { }
void GXGetViewportv(f32* p) { }
void GXSetScissor(u32 left, u32 top, u32 width, u32 height) { }
void GXGetScissor(u32* left, u32* top, u32* width, u32* height) { }
void GXSetScissorBoxOffset(s32 x, s32 y) { }
void GXSetClipMode(GXClipMode mode) { }

// GXPerf
void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1) { }
void GXClearGPMetric(void) { }
void GXReadXfRasMetric(u32*, u32*, u32*, u32*) { }

// inlines
void GXCmd1u8(const u8 x) { }
void GXCmd1u16(const u16 x) { }
void GXCmd1u32(const u32 x) { }
void GXPosition2f32(f32 x, f32 z) { }
void GXPosition3f32(f32 x, f32 y, f32 z) { }
void GXPosition2s8(s8 x, s8 y) { }
void GXPosition3s8(s8 x, s8 y, s8 z) { }
void GXPosition2u16(u16 x, u16 y) { }
void GXPosition2s16(s16 x, s16 y) { }
void GXPosition3s16(s16 x, s16 y, s16 z) { }
void GXNormal3f32(f32 x, f32 y, f32 z) { }
void GXColor1u32(u32 c) { }
void GXTexCoord2f32(f32 s, f32 t) { }
void GXTexCoord2u8(u8 s, u8 t) { }
void GXTexCoord1x8(u8 s) { }
void GXTexCoord2s8(s8 x, s8 y) { }
void GXTexCoord2u16(u16 x, u16 y) { }
void GXTexCoord2s16(const s16 u, const s16 v) { }
void GXPosition1x8(u8 x) { }
void GXPosition1x16(u16 x) { }
void GXNormal1x8(u8 x) { }
void GXNormal1x16(u16 x) { }
void GXColor1x16(u16 x) { }
void GXColor4x8(u8 r, u8 g, u8 b, u8 a) { }
void GXTexCoord1x16(u16 x) { }

// Some structs for natvis
#pragma push
#pragma pack(1)
struct GXBPCmd {
    u8 cmd;
    u32 v1;
};
struct GXCPCmd {
    u8 cmd;
    u8 v1;
    u32 v2;
};
struct GXXFCmd {
    u8 cmd;
    u16 v1;
    u16 v2;
    u32 v3;
};
#pragma pack()
#pragma pop

GXBPCmd debug_bp;
GXCPCmd debug_cp;
GXXFCmd debug_xf;
