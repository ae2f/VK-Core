#if __ae2f_MACRO_GENERATED

#define ae2f_CL(...) __VA_ARGS__
#define ae2f_NCL(...)

typedef	uchar	uint8_t;
typedef ushort	uint16_t;
typedef uint	uint32_t;
typedef ulong	uint64_t;

typedef char	int8_t;
typedef short	int16_t;
typedef int	int32_t;
typedef long	int64_t;

#else

#define ae2f_CL(...)
#define ae2f_NCL(...) __VA_ARGS__


#define ae2f_MAC(...)	void

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

#define __kernel
#define __global
#define __constant
#define __local

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

#endif
