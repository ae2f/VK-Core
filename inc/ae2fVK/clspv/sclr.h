#ifndef ae2fVK_clspv_sclr_h
#define ae2fVK_clspv_sclr_h

#include "./key.h"
#include "./stdint.h"

#if ae2fVK_NCL(!)0
#include <stdbool.h>
#include <stddef.h>
#else
#define bool	unsigned
#endif

#define half	ae2fVK_NCL(float) ae2fVK_CL(half)

#endif
