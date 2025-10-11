/**
 * @file sync.h
 * @see https://registry.khronos.org/OpenCL/sdk/3.0/docs/man/html/barrier.html
 * */

#ifndef ae2fVK_clspv_sync_h
#define ae2fVK_clspv_sync_h

#include "./key.h"

#if ae2fVK_NCL(!)0

typedef enum cl_mem_fence_flags {
	CLK_LOCAL_MEM_FENCE =	0b001,
	CLK_GLOBAL_MEM_FENCE =	0b010,
	CLK_IMAGE_MEM_FENCE =	0b100
} cl_mem_fence_flags;

void barrier(cl_mem_fence_flags flags);

#define cl_mem_fence_flags cl_mem_fence_flags
#define barrier barrier

#define CLK_LOCAL_MEM_FENCE	CLK_LOCAL_MEM_FENCE
#define CLK_GLOBAL_MEM_FENCE	CLK_GLOBAL_MEM_FENCE
#define CLK_IMAGE_MEM_FENCE	CLK_IMAGE_MEM_FENCE

/** @brief Contains both LOCAL and GLOBAL */
#define CLK_ALL_MEM_FENCE	(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE)

/** @brief Contains ALL with IMAGE */
#define CLK_ALLIMG_MEM_FENCE	(CLK_LOCAL_MEM_FENCE | CLK_GLOBAL_MEM_FENCE | CLK_IMAGE_MEM_FENCE)

#endif

#endif
