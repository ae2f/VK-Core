/**
 * @file atom.h
 * @author dalmurii
 *
 * @brief fetch, store and load.
 *
 * @see https://github.com/google/clspv/blob/main/docs/OpenCLCOnVulkan.md#opencl-20-atomic-functions
 * @see https://registry.khronos.org/OpenCL/sdk/3.0/docs/man/html/atomicFunctions.html
 * */

#ifndef ae2fVK_clspv_atom_h
#define ae2fVK_clspv_atom_h

#include "./key.h"

#if !ae2fVK_clspv_IS_OPENCL 

#define atomic_store(ptr, val)
#define atomic_store_explicit(ptr, val, order)

#define atomic_load(ptr)				0
#define atomic_load_explicit(ptr, order)		0

#define atomic_fetch_add(ptr, val)			0
#define atomic_fetch_add_explicit(ptr, val, order)	0

#define atomic_fetch_sub(ptr, val)			0
#define atomic_fetch_sub_explicit(ptr, val, order)	0

#define atomic_fetch_or(ptr, val)			0
#define atomic_fetch_or_explicit(ptr, val, order)	0

#define atomic_fetch_xor(ptr, val)			0
#define atomic_fetch_xor_explicit(ptr, val, order)	0

#define atomic_fetch_and(ptr, val)			0
#define atomic_fetch_and_explicit(ptr, val, order)	0

#define atomic_fetch_min(ptr, val)			0
#define atomic_fetch_min_explicit(ptr, val, order)	0

#define atomic_fetch_max(ptr, val)			0
#define atomic_fetch_max_explicit(ptr, val, order)	0

#define atomic_add(ptr, val)				0
#define atomic_sub(ptr, val)				0
#define atomic_or(ptr, val)				0
#define atomic_xor(ptr, val)				0
#define atomic_and(ptr, val)				0
#define atomic_min(ptr, val)				0
#define atomic_max(ptr, val)				0

#endif

#endif
