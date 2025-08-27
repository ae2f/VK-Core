#ifndef ae2fVK_clspv_clkeys_h
#define ae2fVK_clspv_clkeys_h

#ifndef ae2fVK_clspv_IS_OPENCL
#define ae2fVK_clspv_IS_OPENCL 0
#endif

#if ae2fVK_clspv_IS_OPENCL

#define ae2f_CL(...)	__VA_ARGS__
#define ae2f_NCL(...)

#else

#define ae2f_CL(...)
#define ae2f_NCL(...)	__VA_ARGS__

#include <stddef.h>
#include <stdint.h>

#define __kernel
#define __global
#define __constant
#define __local

#endif

#define int8_t		ae2f_CL(char)	ae2f_NCL(int8_t)
#define uint8_t		ae2f_CL(uchar)	ae2f_NCL(uint8_t)
#define uchar		ae2f_CL(uchar)	ae2f_NCL(uint8_t)

#define int16_t		ae2f_CL(short)	ae2f_NCL(int16_t)
#define uint16_t	ae2f_CL(ushort)	ae2f_NCL(uint16_t)
#define ushort		ae2f_CL(ushort)	ae2f_NCL(uint16_t)

#define int32_t		ae2f_CL(int)	ae2f_NCL(int32_t)
#define uint32_t	ae2f_CL(uint)	ae2f_NCL(uint32_t)
#define uint		ae2f_CL(uint)	ae2f_NCL(uint32_t)

#define int64_t		ae2f_CL(long)	ae2f_NCL(int64_t)
#define uint64_t	ae2f_CL(ulong)	ae2f_NCL(uint64_t)
#define ulong		ae2f_CL(ulong)	ae2f_NCL(uint64_t)

#define size_t	uint

#if !ae2fVK_clspv_IS_OPENCL
uint get_work_dim();
size_t get_global_size(uint dimindx);
size_t get_global_id(uint dimindx);
size_t get_local_size(uint dimindx);
size_t get_enqueued_local_size( uint dimindx);
size_t get_local_id(uint dimindx);
size_t get_num_groups(uint dimindx);
size_t get_global_offset(uint dimindx);
size_t get_group_id(uint dimindx);
size_t get_global_linear_id();
size_t get_local_linear_id();

typedef enum cl_mem_fence_flags {
	CLK_LOCAL_MEM_FENCE =	0b01,
	CLK_GLOBAL_MEM_FENCE =	0b10
} cl_mem_fence_flags;

void barrier(cl_mem_fence_flags flags);

#endif

/** @brief Contains both LOCAL and GLOBAL */
#define CLK_ALL_MEM_FENCE	(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE)

#define work_group_reduce_add(x) 0

#endif
