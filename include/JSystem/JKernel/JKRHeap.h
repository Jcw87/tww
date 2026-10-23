#ifndef JKRHEAP_H
#define JKRHEAP_H

#include "JSystem/JKernel/JKRDisposer.h"
#include "dolphin/os/OSMutex.h"
#include "global.h"
#include <utility>

#ifdef TARGET_PC
#define THREAD_LOCAL thread_local
#else
#define THREAD_LOCAL
#endif

class JKRHeap;
typedef void (*JKRErrorHandler)(void*, u32, int);

class JKRHeap : public JKRDisposer {
public:
    class TState {
    public:
        /* 0x00 */ u32 mUsedSize;
        /* 0x04 */ u32 mCheckCode;
        /* 0x08 */ u32 mBuf;
        /* 0x0C */ u32 field_0xc;
        /* 0x10 */ JKRHeap* mHeap;
        /* 0x14 */ u32 mId;

    public:
        u32 getUsedSize() const { return mUsedSize; }
        u32 getCheckCode() const { return mCheckCode; }
        JKRHeap* getHeap() const { return mHeap; }
        u32 getId() const { return mId; }
    };

public:
    JKRHeap(void* data, u32 size, JKRHeap* parent, bool errorFlag);
    virtual ~JKRHeap();

    JKRHeap* becomeSystemHeap();
    JKRHeap* becomeCurrentHeap();
    void destroy();

    void* alloc(u32 size, int alignment);
    void free(void* ptr);
    void freeAll();
    void freeTail();
    s32 resize(void* ptr, u32 size);
    s32 getSize(void* ptr);
    s32 getFreeSize();
    void* getMaxFreeBlock();
    s32 getTotalFreeSize();
    u8 getCurrentGroupId();
    u8 changeGroupID(u8 newGroupId);
    u32 getMaxAllocatableSize(int alignment);

    JKRHeap* find(void* ptr) const;
    JKRHeap* findAllHeap(void* ptr) const;

    void dispose_subroutine(uintptr_t start, uintptr_t end);
    bool dispose(void* ptr, u32 size);
    void dispose(void* begin, void* end);
    void dispose();

    bool setErrorFlag(bool errorFlag);
    bool isSubHeap(JKRHeap* heap) const;

    /* vt[03] */ virtual void callAllDisposer();
    /* vt[04] */ virtual u32 getHeapType() = 0;
    /* vt[05] */ virtual bool check() = 0;
    /* vt[06] */ virtual bool dump_sort() { return true; }
    /* vt[07] */ virtual bool dump() = 0;
    /* vt[08] */ virtual void do_destroy() = 0;
    /* vt[09] */ virtual void* do_alloc(u32 size, int alignment) = 0;
    /* vt[10] */ virtual void do_free(void* ptr) = 0;
    /* vt[11] */ virtual void do_freeAll() = 0;
    /* vt[12] */ virtual void do_freeTail() = 0;
#if VERSION > VERSION_DEMO
    /* vt[13] */ virtual void do_freeFill() = 0;
#endif
    /* vt[14] */ virtual s32 do_resize(void* ptr, u32 size) = 0;
    /* vt[15] */ virtual s32 do_getSize(void* ptr) = 0;
    /* vt[16] */ virtual s32 do_getFreeSize() = 0;
    /* vt[17] */ virtual void* do_getMaxFreeBlock() = 0;
    /* vt[18] */ virtual s32 do_getTotalFreeSize() = 0;
    /* vt[19] */ virtual u8 do_changeGroupID(u8 newGroupID);
    /* vt[20] */ virtual u8 do_getCurrentGroupId();
    /* vt[21] */ virtual void state_register(JKRHeap::TState* p, u32 id) const;
    /* vt[22] */ virtual bool state_compare(JKRHeap::TState const& r1, JKRHeap::TState const& r2) const;
    /* vt[23] */ virtual void state_dump(JKRHeap::TState const& p) const;

    void setDebugFill(bool debugFill) { mDebugFill = debugFill; }
    void* getStartAddr() { return (void*)mStart; }
    void* getEndAddr() { return (void*)mEnd; }
    bool getErrorFlag() const { return mErrorFlag; }
    void callErrorHandler(void* heap, u32 size, int alignment) {
        if (mErrorHandler) {
            (*mErrorHandler)(heap, size, alignment);
        }
    }

    JKRHeap* getParent() {
        JSUTree<JKRHeap>* parent = mChildTree.getParent();
        return parent->getObject();
    }

    JSUTree<JKRHeap>& getHeapTree() { return mChildTree; }
    void appendDisposer(JKRDisposer* disposer) { mDisposerList.append(&disposer->mLink); }
    void removeDisposer(JKRDisposer* disposer) { mDisposerList.remove(&disposer->mLink); }
    void lock() const { OSLockMutex(const_cast<OSMutex*>(&mMutex)); }
    void unlock() const { OSUnlockMutex(const_cast<OSMutex*>(&mMutex)); }
    u32 getHeapSize() { return mSize; }

protected:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRDisposer
    /* 0x18 */ OSMutex mMutex;
    /* 0x30 */ u8* mStart;
    /* 0x34 */ u8* mEnd;
    /* 0x38 */ u32 mSize;
    /* 0x3C */ bool mDebugFill;
    /* 0x3D */ bool mCheckMemoryFilled;
    /* 0x3E */ u8 mAllocationMode;  // EAllocMode?
    /* 0x3F */ u8 mGroupId;
    /* 0x40 */ JSUTree<JKRHeap> mChildTree;
    /* 0x5C */ JSUList<JKRDisposer> mDisposerList;
    /* 0x68 */ bool mErrorFlag;
    /* 0x69 */ bool mInitFlag;
    /* 0x6A */ u8 padding_0x6a[2];

public:
    static bool initArena(char** memory, u32* size, int maxHeaps);
    static void* alloc(u32 size, int alignment, JKRHeap* heap);
    static void free(void* ptr, JKRHeap* heap);
    static s32 resize(void* ptr, u32 size, JKRHeap* heap);
    static s32 getSize(void* ptr, JKRHeap* heap);
    static JKRHeap* findFromRoot(void* ptr);

    static void copyMemory(void* dst, void* src, u32 size);
    static void fillMemory(void* dst, u32 size, u8 value);  // NOTE: never used

    static JKRErrorHandler setErrorHandler(JKRErrorHandler errorHandler);

    static bool isDefaultDebugFill() { return sDefaultFillFlag; }
    static void setDefaultDebugFill(bool status) { sDefaultFillFlag = status; }
    static void* getCodeStart(void) { return mCodeStart; }
    static void* getCodeEnd(void) { return mCodeEnd; }
    static void* getUserRamStart(void) { return mUserRamStart; }
    static void* getUserRamEnd(void) { return mUserRamEnd; }
    static u32 getMemorySize(void) { return mMemorySize; }
    static JKRHeap* getRootHeap() { return sRootHeap; }

    static JKRHeap* getSystemHeap() { return sSystemHeap; }
    static JKRHeap* getCurrentHeap() { return sCurrentHeap; }

    static void setState_u32ID_(TState* state, u32 id) { state->mId = id; }
    static void setState_uUsedSize_(TState* state, u32 usedSize) { state->mUsedSize = usedSize; }
    static void setState_u32CheckCode_(TState* state, u32 checkCode) {
        state->mCheckCode = checkCode;
    }
    static void* getState_buf_(TState* state) { return &state->mBuf; }

    static void* mCodeStart;
    static void* mCodeEnd;
    static void* mUserRamStart;
    static void* mUserRamEnd;
    static u32 mMemorySize;

    static JKRHeap* sRootHeap;

    static JKRHeap* sSystemHeap;
    static THREAD_LOCAL JKRHeap* sCurrentHeap;
    static bool sDefaultFillFlag;

    static JKRErrorHandler mErrorHandler;
};

#if TARGET_PC
enum class JKRHeapToken { Dummy };

#define JKR_NEW new (JKRHeapToken::Dummy)
#define JKR_NEW_ARRAY(type, count) jkrNewArray(count, std::in_place_type<type>)
#define JKR_NEW_ARGS(...) new (JKRHeapToken::Dummy, __VA_ARGS__)
#define JKR_NEW_ARRAY_ARGS(type, count, ...) jkrNewArray(count, std::in_place_type<type>, __VA_ARGS__)
#define JKR_DELETE(expr) jkrDelete(expr)
#define JKR_DELETE_ARRAY(expr) jkrDeleteArray(expr)
#define JKR_HEAP_TOKEN_PARAM , JKRHeapToken
#else
#define JKR_NEW new
#define JKR_NEW_ARRAY(type, count) new type[count]
#define JKR_NEW_ARGS(...) new (__VA_ARGS__)
#define JKR_NEW_ARRAY_ARGS(type, count, ...) new (JKRHeapToken::Dummy, __VA_ARGS__ ) type[count]
#define JKR_DELETE(expr) delete (expr)
#define JKR_DELETE_ARRAY(expr) delete[] (expr)
#define JKR_HEAP_TOKEN_PARAM
#endif

void* operator new(size_t size JKR_HEAP_TOKEN_PARAM);
void* operator new(size_t size JKR_HEAP_TOKEN_PARAM, int alignment);
void* operator new(size_t size JKR_HEAP_TOKEN_PARAM, JKRHeap* heap, int alignment);

void* operator new[](size_t size JKR_HEAP_TOKEN_PARAM);
void* operator new[](size_t size JKR_HEAP_TOKEN_PARAM, int alignment);
void* operator new[](size_t size JKR_HEAP_TOKEN_PARAM, JKRHeap* heap, int alignment);

void operator delete(void* ptr JKR_HEAP_TOKEN_PARAM);
void operator delete[](void* ptr JKR_HEAP_TOKEN_PARAM);

#if TARGET_PC
template<typename T>
void jkrDelete(T* ptr) {
    if (ptr == nullptr) {
        return;
    }
    ptr->~T();

    if constexpr (requires { T::operator delete(ptr, JKRHeapToken::Dummy); }) {
        T::operator delete(ptr, JKRHeapToken::Dummy);
    } else if constexpr (requires { T::operator delete(ptr, sizeof(T), JKRHeapToken::Dummy); }) {
        T::operator delete(ptr, sizeof(T), JKRHeapToken::Dummy);
    } else if constexpr (requires { T::operator delete(ptr); }) {
        T::operator delete(ptr);
    } else if constexpr (requires { T::operator delete(ptr, sizeof(T)); }) {
        T::operator delete(ptr, sizeof(T));
    } else {
        operator delete(ptr, JKRHeapToken::Dummy);
    }
}

template<>
inline void jkrDelete(void* ptr) {
    if (ptr == nullptr) {
        return;
    }

    operator delete(ptr, JKRHeapToken::Dummy);
}

template<typename... Args>
bool constexpr newArgsHasCustomAlignment() {
    return false;
}

template<int>
constexpr bool newArgsHasCustomAlignment() {
    return true;
}

template<JKRHeap*, int>
constexpr bool newArgsHasCustomAlignment() {
    return true;
}

template<typename T, typename... Args>
T* jkrNewArray(size_t count, std::in_place_type_t<T>, Args&&... args) {
    size_t allocSize = count * sizeof(T);
    if constexpr (!std::is_trivially_destructible<T>()) {
        static_assert(
            !newArgsHasCustomAlignment<Args...>(),
            "jkrNewArray cannot currently handle non-trivially-destructible array allocations with custom alignment");

        allocSize += sizeof(size_t);
    }

    void* ptr = operator new(allocSize, JKRHeapToken::Dummy, args...);
    if (!ptr) {
        return nullptr;
    }

    T* dataPtr;
    if constexpr (!std::is_trivially_destructible<T>()) {
        auto length = static_cast<size_t*>(ptr);
        *length = count;
        dataPtr = reinterpret_cast<T*>(length + 1);
    } else {
        dataPtr = static_cast<T*>(ptr);
    }

    if constexpr (!std::is_trivially_constructible<T>()) {
        for (int i = 0; i < count; ++i) {
            new (dataPtr + i) T();
        }
    }

    return dataPtr;
}

template<typename T>
void jkrDeleteArray(T* pointer) {
    if (pointer == nullptr) {
        return;
    }

    if constexpr (!std::is_trivially_destructible<T>()) {
        auto countPtr = reinterpret_cast<size_t*>(pointer) - 1;
        auto count = *countPtr;

        for (int i = 0; i < count; ++i) {
            (pointer + i)->~T();
        }

        operator delete(countPtr, JKRHeapToken::Dummy);
    } else {
        operator delete(pointer, JKRHeapToken::Dummy);
    }
}

template<>
inline void jkrDeleteArray(void* pointer) {
    if (pointer == nullptr) {
        return;
    }

    operator delete(pointer, JKRHeapToken::Dummy);
}
#endif

void JKRDefaultMemoryErrorRoutine(void* heap, u32 size, int alignment);

inline void* JKRAllocFromHeap(JKRHeap* heap, u32 size, int alignment) {
    return JKRHeap::alloc(size, alignment, heap);
}

inline void* JKRAllocFromSysHeap(u32 size, int alignment) {
    JKRHeap* systemHeap = JKRHeap::getSystemHeap();
    return systemHeap->alloc(size, alignment);
}

inline void JKRFreeToHeap(JKRHeap* heap, void* ptr) {
    JKRHeap::free(ptr, heap);
}

inline void JKRFreeToSysHeap(void* ptr) {
    JKRHeap* systemHeap = JKRHeap::getSystemHeap();
    systemHeap->free(ptr);
}

inline void JKRFree(void* ptr) {
    JKRHeap::free(ptr, NULL);
}

inline JKRHeap* JKRGetSystemHeap() {
    return JKRHeap::getSystemHeap();
}

inline JKRHeap* JKRGetCurrentHeap() {
    return JKRHeap::getCurrentHeap();
}

inline JKRHeap* JKRSetCurrentHeap(JKRHeap* heap) {
    return heap->becomeCurrentHeap();
}

inline u32 JKRGetMemBlockSize(JKRHeap* heap, void* block) {
    return JKRHeap::getSize(block, heap);
}

inline void* JKRAlloc(u32 size, int alignment) {
    return JKRHeap::alloc(size, alignment, NULL);
}

inline s32 JKRResizeMemBlock(JKRHeap* heap, void* ptr, u32 size) {
    return JKRHeap::resize(ptr, size, heap);
}

inline JKRHeap* JKRGetRootHeap() {
    return JKRHeap::getRootHeap();
}

inline JKRErrorHandler JKRSetErrorHandler(JKRErrorHandler errorHandler) {
    return JKRHeap::setErrorHandler(errorHandler);
}

inline bool JKRSetErrorFlag(JKRHeap* heap, bool flag) {
    return heap->setErrorFlag(flag);
}

inline void JKRSetDebugFillDelete(u8) {}
inline void JKRSetDebugFillNew(u8) {}
inline void JKRSetDebugFillNotuse(u8) {}

#endif /* JKRHEAP_H */
