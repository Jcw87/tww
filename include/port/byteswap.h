#ifndef BYTESWAP_H
#define BYTESWAP_H

#include <dolphin/mtx/mtx.h>
#include <dolphin/mtx/vec.h>
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_sxyz.h"

#if TARGET_PC
#include <type_traits>
#endif

// Platform detection - Little Endian targets
#if defined(_WIN32) || defined(__x86_64__) || defined(__i386__) || defined(__aarch64__) || defined(_M_X64) || defined(_M_IX86)
#define TARGET_LITTLE_ENDIAN 1
#else
#define TARGET_LITTLE_ENDIAN 0
#endif

#define IMPORT __declspec(dllimport)
#define EXPORT __declspec(dllexport)

#if TARGET_LITTLE_ENDIAN
template <typename T> constexpr IMPORT T byteswap(const T& v);

template <typename S, typename T = S>
struct BE {
    S inner;
    BE() = default;
    BE(const T& from) { inner = byteswap(S(from)); }

    // post-ops
    T operator--(int) {
        S orig = inner;
        *this -= 1;
        return byteswap(orig);
    }

    T operator++(int) {
        S orig = inner;
        *this += 1;
        return byteswap(orig);
    }

    operator T() const { return T(byteswap(inner)); }
};

#define BIN_ASSIGN_OP(op)                                                                                                                                      \
                                                                                                                                                               \
    template <typename TA, typename TB> constexpr BE<TA>& operator op(BE<TA>& a, TB b) {                                                                       \
        TA aCopy = a;                                                                                                                                          \
        aCopy op b;                                                                                                                                            \
        a = aCopy;                                                                                                                                             \
        return a;                                                                                                                                              \
    }

BIN_ASSIGN_OP(&=);
BIN_ASSIGN_OP(|=);
BIN_ASSIGN_OP(+=);
BIN_ASSIGN_OP(-=);
BIN_ASSIGN_OP(/=);
BIN_ASSIGN_OP(^=);

#undef BIN_ASSIGN_OP

template <>
struct BE<Vec> {
    BE<f32> x;
    BE<f32> y;
    BE<f32> z;
    BE() = default;
    BE(const Vec& from) {
        x = from.x;
        y = from.y;
        z = from.z;
    }
    BE(f32 x, f32 y, f32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    operator Vec() const { return {x, y, z}; }
};

template <>
struct BE<S16Vec> {
    BE<s16> x;
    BE<s16> y;
    BE<s16> z;
    BE() = default;
    BE(const S16Vec& from) {
        x = from.x;
        y = from.y;
        z = from.z;
    }

    operator S16Vec() const { return {x, y, z}; }
};

template <>
struct BE<Mtx> {
    BE<f32> inner[3][4];
    BE() = default;
    BE(const Mtx& from) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                inner[i][j] = from[i][j];
            }
        }
    }
    void to_host(Mtx& mtx) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                mtx[i][j] = inner[i][j];
            }
        }
    }

    auto& operator[](int x) const { return inner[x]; }
};

template <> struct BE<cXyz> {
    BE<f32> x;
    BE<f32> y;
    BE<f32> z;
    BE() = default;
    BE(const cXyz& from) {
        x = from.x;
        y = from.y;
        z = from.z;
    }
    BE(f32 x, f32 y, f32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    operator cXyz() const { return {x, y, z}; }
    void operator=(const BE<Vec>& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    void set(f32 pX, f32 pY, f32 pZ) {
        x = pX;
        y = pY;
        z = pZ;
    }

    void set(const Vec& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
};

template <> struct BE<csXyz> {
    BE<s16> x;
    BE<s16> y;
    BE<s16> z;
    BE() = default;
    BE(const csXyz& from) {
        x = from.x;
        y = from.y;
        z = from.z;
    }

    operator csXyz() const { return {x, y, z}; }

    void set(s16 oX, s16 oY, s16 oZ) {
        x = oX;
        y = oY;
        z = oZ;
    }
};
#define BE2(S, T) BE<S, T>
#define BE(S) BE<S>
#else
#define BE2(S, Y) S
#define BE(S) S
#endif

#if TARGET_LITTLE_ENDIAN
struct OffsetPtr {
    BE<u32> value;

    bool operator==(u32 o) { return value == o; }
    bool operator!=(u32 o) { return value != o; }
    OffsetPtr& operator+=(u32 o) {
        value += o;
        return *this;
    }
    explicit operator u32() const { return value; }
    explicit operator int() const { return value; }
    explicit operator uintptr_t() const { return value; }
    template <typename TExplicit> explicit operator TExplicit*() const { return (TExplicit*)(uintptr_t)value; }
};

template <typename T>
struct OffsetPtrT : public OffsetPtr {
    OffsetPtrT() = default;
    OffsetPtrT(const T* ptr) { value = (u32)ptr; }
    T* operator->() { return (T*)(u32)value; }
    operator T*() const { return (T*)(u32)value; }
};

#define OFFSET_PTR(T) OffsetPtrT<T>
#define OFFSET_PTR_RAW OffsetPtr
#else
#define OFFSET_PTR(T) T*
#define OFFSET_PTR_RAW u32
#endif

#endif /* BYTESWAP_H */
