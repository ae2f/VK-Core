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
#else
#include <stdint.h>
#endif

#endif
