#ifndef ae2fVK_clspv_stdint_h
#define ae2fVK_clspv_stdint_h

#include "./key.h"

#if ae2fVK_NCL(!)0
#include <stdint.h>
#endif

#define int8_t		ae2fVK_CL(char)		ae2fVK_NCL(int8_t)
#define uint8_t		ae2fVK_CL(uchar)	ae2fVK_NCL(uint8_t)
#define uchar		ae2fVK_CL(uchar)	ae2fVK_NCL(uint8_t)

#define int16_t		ae2fVK_CL(short)	ae2fVK_NCL(int16_t)
#define uint16_t	ae2fVK_CL(ushort)	ae2fVK_NCL(uint16_t)
#define ushort		ae2fVK_CL(ushort)	ae2fVK_NCL(uint16_t)

#define int32_t		ae2fVK_CL(int)		ae2fVK_NCL(int32_t)
#define uint32_t	ae2fVK_CL(uint)		ae2fVK_NCL(uint32_t)
#define uint		ae2fVK_CL(uint)		ae2fVK_NCL(uint32_t)

#define int64_t		ae2fVK_CL(long)		ae2fVK_NCL(int64_t)
#define uint64_t	ae2fVK_CL(ulong)	ae2fVK_NCL(uint64_t)
#define ulong		ae2fVK_CL(ulong)	ae2fVK_NCL(uint64_t)

#endif
