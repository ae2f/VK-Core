/**
 * @file Loc.h
 * @author ae2f
 * @brief 
 * @version 0.1
 * @date 2025-02-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ae2fVK_Loc_h
#define ae2fVK_Loc_h

#ifndef ae2fVK_LocAsVK

/// @brief opencl keyword
#define __kernel

/// @brief opencl keyword
#define __global

#include <ae2f/Cast.h>

/// @brief
/// Shows when the code is running on VK code, not C.
#define ae2fVK_whenVK(...)

/// @brief
/// Shows when the code is running on C, not VK.
#define ae2fVK_whenC(...) __VA_ARGS__

#else

/// @brief
/// Shows when the code is running on VK code, not C.
#define ae2fVK_whenVK(...) __VA_ARGS__

/// @brief
/// Shows when the code is running on C, not VK.
#define ae2fVK_whenC(...)

#define _MATH_H
#define _STDBOOL_H
#define __STDC_HOSTED__ 0
#define _GCC_WRAP_STDINT_H

#define _STDDEF_H
#define _STDDEF_H_
#define _ANSI_STDDEF_H
#define __STDDEF_H__
#define ae2f_Cmp_Fun_h
#define _USE_MATH_DEFINES
#define _INC_MATH
#define _INC_STDDEF
#define _MATH_H_
#define _INC_STDDEF_
#define _STDINT
#define _INC_CRTDEFS

#endif

/// @brief pointer type for host code
#define ae2fVK_HostPtr(__flag, __type) ae2fVK_whenC(cl_mem) ae2fVK_whenVK(__flag __type*)

#endif