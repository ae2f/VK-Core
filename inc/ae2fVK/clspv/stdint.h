#ifndef ae2fVK_clspv_stdint_h
#define ae2fVK_clspv_stdint_h

#include "./sclr.h"

#if ae2fVK_clspv_IS_OPENCL
#define int8_t		char
#define uint8_t		uchar
#define int16_t		short
#define uint16_t	ushort
#define int32_t		int
#define uint32_t	uint
#define int64_t		long
#define uint64_t	ulong

#define int_least8_t    int8_t
#define int_least16_t   int16_t
#define int_least32_t   int32_t
#define int_least64_t   int64_t

#define uint_least8_t   uint8_t
#define uint_least16_t  uint16_t
#define uint_least32_t  uint32_t
#define uint_least64_t  uint64_t

#define int_fast8_t    int32_t
#define int_fast16_t   int32_t
#define int_fast32_t   int32_t
#define int_fast64_t   int64_t

#define uint_fast8_t   uint32_t
#define uint_fast16_t  uint32_t
#define uint_fast32_t  uint32_t
#define uint_fast64_t  uint64_t

#else
#include <stdint.h>
#endif

#endif
