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

#ifndef ae2fCL_Loc_h
#define ae2fCL_Loc_h

#ifndef ae2fCL_LocAsCL

/// @brief opencl keyword
#define __kernel

/// @brief opencl keyword
#define __global

#include <ae2f/Cast.h>

#ifndef ae2fCL_Scenario
#include "Scenario.h"
#endif

/// @brief
/// Shows when the code is running on CL code, not C.
#define ae2fCL_whenCL(...)

/// @brief
/// Shows when the code is running on C, not CL.
#define ae2fCL_whenC(...) __VA_ARGS__

#include <stdint.h>
#include <stdbool.h>
#else
typedef int int32_t;
typedef uint uint32_t;

typedef short int16_t;
typedef ushort uint16_t;

typedef char int8_t;
typedef uchar uint8_t;

typedef long long int64_t;
typedef unsigned long long uint64_t;

/// @brief
/// Shows when the code is running on CL code, not C.
#define ae2fCL_whenCL(...) __VA_ARGS__

/// @brief
/// Shows when the code is running on C, not CL.
#define ae2fCL_whenC(...)

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
#define ae2fCL_HostPtr(__flag, __type) ae2fCL_whenC(cl_mem) ae2fCL_whenCL(__flag __type*)

#endif