#ifndef ae2fVK_clspv_key_h
#define ae2fVK_clspv_key_h

#ifndef ae2fVK_clspv_IS_OPENCL
#define ae2fVK_clspv_IS_OPENCL 0
#endif

#if ae2fVK_clspv_IS_OPENCL

#define ae2fVK_CL(...)	__VA_ARGS__
#define ae2fVK_NCL(...)

#else

#define ae2fVK_CL(...)
#define ae2fVK_NCL(...)	__VA_ARGS__
#endif

#endif
