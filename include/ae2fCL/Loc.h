#ifndef ae2fCL_Loc_h
#define ae2fCL_Loc_h

#ifndef ae2fCL_LocAsCL

/// @brief opencl keyword
#define __kernel

/// @brief opencl keyword
#define __global

#include <CL/cl.h>
#include <ae2f/Cast.h>

#ifndef ae2fCL_Scenario
#pragma message ("You did not choose the scenario. Fetching the interface...")
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

#endif

/// @brief pointer type for host code
#define ae2fCL_HostPtr(__flag, __type) ae2fCL_whenC(cl_mem) ae2fCL_whenCL(__flag __type*)

#endif