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

#include "./sclr.h"

#if !ae2fVK_clspv_IS_OPENCL 

uint atom_cmpxchg_u(volatile uint *p, uint cmp, uint val);
int atom_cmpxchg_i(volatile int *p, int cmp, int val);

int atom_xchg_i(volatile int *p, int val);
int atom_xchg_u(volatile uint *p, uint val);


#else

#define atom_cmpxchg_i	atom_cmpxchg
#define atom_cmpxchg_u	atom_cmpxchg

#define atom_xchg_u	atom_xchg
#define atom_xchg_i	atom_xchg

#endif

#endif
