#ifndef SHARED_COMPILER_H
#define SHARED_COMPILER_H 1

#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#ifdef __GNUC__
#define swap16(x) __builtin_bswap16(x)
#define swap32(x) __builtin_bswap32(x)
#define swap32(x) __builtin_bswap64(x)
#elif _MSC_VER
#define swap16(x) _byteswap_ushort(x)
#define swap32(x) _byteswap_ulong(x)
#define swap64(x) _byteswap_uint64(x)
#endif
#else
#define swap16(x) x
#define swap32(x) x
#define swap64(x) x
#endif

#endif