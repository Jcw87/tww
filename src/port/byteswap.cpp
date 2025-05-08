
#include "port/byteswap.h"

#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/mtx/vec.h>
#include "JSystem/JStudio/JStudio/functionvalue.h"
#include "JSystem/JStudio/JStudio/fvb-data.h"
#include <bit>

template <typename E> requires std::is_enum<E>::value
constexpr E byteswap_enum(const E& v) {
    return static_cast<E>(byteswap(static_cast<std::underlying_type<E>::type>(v)));
}

template <> EXPORT constexpr s64 byteswap<s64>(const s64& v) { return std::byteswap(v); }
template <> EXPORT constexpr u64 byteswap<u64>(const u64& v) { return std::byteswap(v); }
template <> EXPORT constexpr s32 byteswap<s32>(const s32& v) { return std::byteswap(v); }
template <> EXPORT constexpr u32 byteswap<u32>(const u32& v) { return std::byteswap(v); }
template <> EXPORT constexpr s16 byteswap<s16>(const s16& v) { return std::byteswap(v); }
template <> EXPORT constexpr u16 byteswap<u16>(const u16& v) { return std::byteswap(v); }
template <> EXPORT constexpr int byteswap<int>(const int& v) { return std::byteswap(v); }
template <> EXPORT constexpr uint byteswap<uint>(const uint& v) { return std::byteswap(v); }
template <> EXPORT constexpr f64 byteswap<f64>(const f64& v) { return std::bit_cast<f64, s64>(std::byteswap(std::bit_cast<s64, f64>(v))); }
template <> EXPORT constexpr f32 byteswap<f32>(const f32& v) { return std::bit_cast<f32, s32>(std::byteswap(std::bit_cast<s32, f32>(v))); }
template <> EXPORT constexpr Vec byteswap<Vec>(const Vec& v) { return {byteswap(v.x), byteswap(v.y), byteswap(v.z)}; }
template <> EXPORT constexpr SVec byteswap<SVec>(const SVec& v) { return {byteswap(v.x), byteswap(v.y), byteswap(v.z)}; }
template <> EXPORT constexpr S16Vec byteswap<S16Vec>(const S16Vec& v) { return {byteswap(v.x), byteswap(v.y), byteswap(v.z)}; }
template <> EXPORT constexpr GXColorS10 byteswap<GXColorS10>(const GXColorS10& v) { return {byteswap(v.r), byteswap(v.g), byteswap(v.b), byteswap(v.a)}; }
template <> EXPORT constexpr GXAttr byteswap<GXAttr>(const GXAttr& v) { return byteswap_enum(v); }
template <> EXPORT constexpr GXAttrType byteswap<GXAttrType>(const GXAttrType& v) { return byteswap_enum(v); }
template <> EXPORT constexpr GXCompCnt byteswap<GXCompCnt>(const GXCompCnt& v) { return byteswap_enum(v); }
template <> EXPORT constexpr GXCompType byteswap<GXCompType>(const GXCompType& v) { return byteswap_enum(v); }
template <> EXPORT constexpr GXCullMode byteswap<GXCullMode>(const GXCullMode& v) { return byteswap_enum(v); }
template <> EXPORT constexpr GXVtxAttrFmtList byteswap<GXVtxAttrFmtList>(const GXVtxAttrFmtList& v) { return {byteswap(v.attr), byteswap(v.cnt), byteswap(v.type), v.frac }; }
template <> EXPORT constexpr JStudio::TFunctionValue::TEAdjust byteswap<JStudio::TFunctionValue::TEAdjust>(const JStudio::TFunctionValue::TEAdjust& v) { return byteswap_enum(v); }
template <> EXPORT constexpr JStudio::TFunctionValue::TEInterpolate byteswap<JStudio::TFunctionValue::TEInterpolate>(const JStudio::TFunctionValue::TEInterpolate& v) { return byteswap_enum(v); }
template <> EXPORT constexpr JStudio::TFunctionValue::TEProgress byteswap<JStudio::TFunctionValue::TEProgress>(const JStudio::TFunctionValue::TEProgress& v) { return byteswap_enum(v); }
template <> EXPORT constexpr JStudio::fvb::data::TEComposite byteswap<JStudio::fvb::data::TEComposite>(const JStudio::fvb::data::TEComposite& v) { return byteswap_enum(v); }
