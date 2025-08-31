#ifndef ANNEX_H_
#define ANNEX_H_

#include <inttypes.h>

// Platform related

#if defined(_MSC_VER)
    #define ANN_COMPILER_MSVC 1
    #define ANN_COMPILER_GCC 0
    #define ANN_COMPILER_CLANG 0
#elif defined(__GNUC__) || defined(__GNUG__)
    #define ANN_COMPILER_MSVC 0
    #define ANN_COMPILER_GCC 1
    #define ANN_COMPILER_CLANG 0
#elif defined(__clang__)
    #define ANN_COMPILER_MSVC 0
    #define ANN_COMPILER_GCC 0
    #define ANN_COMPILER_CLANG 1
#else
    #error "Unknown compiler"
#endif

#if ANN_COMPILER_MSVC || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

    #define ANN_OS_WINDOWS 1
    #define ANN_OS_LINUX 0
    #define ANN_OS_MAC 0

    #ifdef _WIN64
        //define something for Windows (64-bit only)
    #else
        //define something for Windows (32-bit only)
    #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS, tvOS, or watchOS Simulator
    #elif TARGET_OS_MACCATALYST

        #define ANN_OS_WINDOWS 0
        #define ANN_OS_LINUX 0
        #define ANN_OS_MAC 1

    #elif TARGET_OS_IPHONE
        // iOS, tvOS, or watchOS device
    #elif TARGET_OS_MAC
    
        #define ANN_OS_WINDOWS 0
        #define ANN_OS_LINUX 0
        #define ANN_OS_MAC 1

    #else
        #error "Unknown Apple platform"
    #endif
#elif __ANDROID__
    // Below __linux__ check should be enough to handle Android,
    // but something may be unique to Android.
#elif __linux__

    #define ANN_OS_WINDOWS 0
    #define ANN_OS_LINUX 1
    #define ANN_OS_MAC 0

#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
    #error "Unknown platform"
#endif

#ifdef NDEBUG
    #define ANN_BUILD_RELEASE 1
    #define ANN_BUILD_DEBUG 0
#else
    #define ANN_BUILD_RELEASE 0
    #define ANN_BUILD_DEBUG 1
#endif

#if defined(__BYTE_ORDER) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__ || \
    defined(__BIG_ENDIAN__) || \
    defined(__ARMEB__) || \
    defined(__THUMBEB__) || \
    defined(__AARCH64EB__) || \
    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
    #define ANN_IS_BIG_ENDIAN 1
#elif defined(__BYTE_ORDER) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || \
    defined(__LITTLE_ENDIAN__) || \
    defined(__ARMEL__) || \
    defined(__THUMBEL__) || \
    defined(__AARCH64EL__) || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__) || \
    ANN_COMPILER_MSVC || defined(__i386__) || defined(__x86_64__)
    #define ANN_IS_BIG_ENDIAN 0
#else
    #error "Could not determine endianness"
#endif

#if ANN_COMPILER_MSVC
    #define ANN_MAYBE_UNUSED 
#else
    #define ANN_MAYBE_UNUSED __attribute__ ((unused))
#endif

// Meta programming

#define __ANN_STR_VALUE(x) #x
#define ANN_STR_VALUE(x) __ANN_STR_VALUE(x)

#define __ANN_CONCAT(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,...) a##b##c##d##e##f##g##h##i##j##k##l##m##n##o##p##q##r##s##t##u##v##w##x##y##z
#define ANN_CONCAT(...) __ANN_CONCAT(__VA_ARGS__,,,,,,,,,,,,,,,,,,,,,,,,,,)

#define ANN_DUMMY(value) value

#define __ANN_GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,NAME,...) NAME 

#define __ANN_JOIN_1(separator, it) it
#define __ANN_JOIN_2(separator, it, ...) it separator __ANN_JOIN_1(separator, __VA_ARGS__)
#define __ANN_JOIN_3(separator, it, ...) it separator __ANN_JOIN_2(separator, __VA_ARGS__)
#define __ANN_JOIN_4(separator, it, ...) it separator __ANN_JOIN_3(separator, __VA_ARGS__)
#define __ANN_JOIN_5(separator, it, ...) it separator __ANN_JOIN_4(separator, __VA_ARGS__)
#define __ANN_JOIN_6(separator, it, ...) it separator __ANN_JOIN_5(separator, __VA_ARGS__)
#define __ANN_JOIN_7(separator, it, ...) it separator __ANN_JOIN_6(separator, __VA_ARGS__)
#define __ANN_JOIN_8(separator, it, ...) it separator __ANN_JOIN_7(separator, __VA_ARGS__)
#define __ANN_JOIN_9(separator, it, ...) it separator __ANN_JOIN_8(separator, __VA_ARGS__)
#define __ANN_JOIN_10(separator, it, ...) it separator __ANN_JOIN_9(separator, __VA_ARGS__)
#define __ANN_JOIN_11(separator, it, ...) it separator __ANN_JOIN_10(separator, __VA_ARGS__)
#define __ANN_JOIN_12(separator, it, ...) it separator __ANN_JOIN_11(separator, __VA_ARGS__)

#define ANN_JOIN(separator,...) \
  __ANN_GET_MACRO(_0,__VA_ARGS__,__ANN_JOIN_12,__ANN_JOIN_11,__ANN_JOIN_10,__ANN_JOIN_9,__ANN_JOIN_8,__ANN_JOIN_7,__ANN_JOIN_6,__ANN_JOIN_5,__ANN_JOIN_4,__ANN_JOIN_3,__ANN_JOIN_2,__ANN_JOIN_1)(separator,__VA_ARGS__)

#define __ANN_FOR_EACH_1(action, it) action(it) 
#define __ANN_FOR_EACH_2(action, it, ...) action(it), __ANN_FOR_EACH_1(action, __VA_ARGS__)
#define __ANN_FOR_EACH_3(action, it, ...) action(it), __ANN_FOR_EACH_2(action, __VA_ARGS__)
#define __ANN_FOR_EACH_4(action, it, ...) action(it), __ANN_FOR_EACH_3(action, __VA_ARGS__)
#define __ANN_FOR_EACH_5(action, it, ...) action(it), __ANN_FOR_EACH_4(action, __VA_ARGS__)
#define __ANN_FOR_EACH_6(action, it, ...) action(it), __ANN_FOR_EACH_5(action, __VA_ARGS__)
#define __ANN_FOR_EACH_7(action, it, ...) action(it), __ANN_FOR_EACH_6(action, __VA_ARGS__)
#define __ANN_FOR_EACH_8(action, it, ...) action(it), __ANN_FOR_EACH_7(action, __VA_ARGS__)
#define __ANN_FOR_EACH_9(action, it, ...) action(it), __ANN_FOR_EACH_8(action, __VA_ARGS__)
#define __ANN_FOR_EACH_10(action, it, ...) action(it), __ANN_FOR_EACH_9(action, __VA_ARGS__)
#define __ANN_FOR_EACH_11(action, it, ...) action(it), __ANN_FOR_EACH_10(action, __VA_ARGS__)
#define __ANN_FOR_EACH_12(action, it, ...) action(it), __ANN_FOR_EACH_11(action, __VA_ARGS__)

#define ANN_FOR_EACH(action,...) \
  __ANN_GET_MACRO(_0,__VA_ARGS__,__ANN_FOR_EACH_12,__ANN_FOR_EACH_11,\
    __ANN_FOR_EACH_10,__ANN_FOR_EACH_9,__ANN_FOR_EACH_8,__ANN_FOR_EACH_7,__ANN_FOR_EACH_6,__ANN_FOR_EACH_5,__ANN_FOR_EACH_4,__ANN_FOR_EACH_3,__ANN_FOR_EACH_2,__ANN_FOR_EACH_1)(action,__VA_ARGS__)

// Flow controll

#ifndef ANN_ASSERT
    #ifdef ANN_INCLUDE_DEFAULT_ASSERT
        #include <assert.h>
    #endif
    #define ANN_ASSERT(expr) (assert(expr))
#endif

#if !ANN_BUILD_RELEASE
    #if ANN_COMPILER_MSVC
        #include <debugapi.h>
        #define ANN_DEBUGBREAK() __debugbreak()
    #else
        #define ANN_DEBUGBREAK() do { __asm__ volatile("int $0x03"); int __dummy = 0; (void)__dummy; } while(0) // to stop exactly at the ANN_DEBUGBREAK()
    #endif
#else
    #define ANN_DEBUGBREAK() do {} while(0) // in case compiler would complain about empty ;
#endif

#if ANN_COMPILER_MSVC
    #define __ANN_UNREACHABLE() __assume(0)
#else
    #define __ANN_UNREACHABLE() __builtin_unreachable()
#endif

#if ANN_BUILD_DEBUG
    #define ANN_UNREACHABLE() do { __ANN_UNREACHABLE(); ANN_ASSERT(false && "unreachable"); } while (0)
#else
    #define ANN_UNREACHABLE() __ANN_UNREACHABLE()
#endif

#define ANN_FOREVER while(1)

#define ANN_SWITCH_STRICT(val) switch(val) if (1) { default: ANN_UNREACHABLE(); } else

#define ANN_NODEFAULT() do { default: ANN_UNREACHABLE(); break; } while (0)

// Common

#define __ANN_SWAP_ENDIAN_8(value) (value)
#if ANN_COMPILER_MSVC  
    #define __ANN_SWAP_ENDIAN_16(value) _byteswap_ushort(value)
    #define __ANN_SWAP_ENDIAN_32(value) _byteswap_ulong(value)
    #define __ANN_SWAP_ENDIAN_64(value) _byteswap_uint64(value)
#else
    #define __ANN_SWAP_ENDIAN_16(value) __builtin_bswap16(value)
    #define __ANN_SWAP_ENDIAN_32(value) __builtin_bswap32(value)
    #define __ANN_SWAP_ENDIAN_64(value) __builtin_bswap64(value)
#endif

#if ANN_IS_BIG_ENDIAN
    #define ANN_TO_BE_SWAP(value, size) (value)
    #define ANN_TO_LE_SWAP(value, size) (__ANN_SWAP_ENDIAN_##size(value))
#else
    #define ANN_TO_BE_SWAP(value, size) __ANN_SWAP_ENDIAN_##size(value)
    #define ANN_TO_LE_SWAP(value, size) (value)
#endif

#define ANN_HASH(a) ((uint64_t)(a))
#define ANN_EQUAL(a, b) ((a) == (b))

#define ANN_LESS(a, b) ((a) < (b))

#define ANN_MAX(a, b) ((a) > (b) ? (a) : (b))
#define ANN_MIN(a, b) ((a) < (b) ? (a) : (b))

#define ANN_FORWARD(name) typedef struct name name
#define ANN_DEFINE(name) ANN_FORWARD(name); struct name

#define ANN_ALIGN_FORWARD(size, alignment) (((size) + ((alignment) - 1)) & ~((alignment) - 1))
#define ANN_ALIGNOF(value) (_Alignof(value))
#define ANN_ALIGNOF_FORWARD(size, alignment) (size, ANN_ALIGNOF(alignment))

#define ANN_ARRAY_SIZE(array) (sizeof(array) / sizeof(*(array)))

#endif
