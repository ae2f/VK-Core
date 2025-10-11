/**
 * @file wrkgroup.h
 * @brief 
 * Work Item Functions
 *
 * @see https://registry.khronos.org/OpenCL/sdk/3.0/docs/man/html/get_work_dim.html
 * */

#ifndef ae2fVK_clspv_wrkitem_h
#define ae2fVK_clspv_wrkitem_h

#include "./sclr.h"

#if ae2fVK_NCL(!)0
/** 
 * @brief 
 * Returns the number of dimensions in use. \n
 * This is the value given to the work_dim argument specified in clEnqueueNDRangeKernel.
 * */
uint get_work_dim();

/** 
 * @brief
 * Returns the number of global work-items specified for dimension identified by dimindx. \n
 * This value is given by the global_work_size argument to clEnqueueNDRangeKernel.
 *
 * @param dimindx
 * Valid values of dimindx are 0 to get_work_dim() - 1. \n
 * For other values of dimindx, get_global_size() returns 1.
 * */
size_t get_global_size(uint dimindx);

/**
 * @brief
 * Returns the unique global work-item ID value for dimension identified by dimindx. \n
 * The global work-item ID specifies the work-item ID based on the number of global work-items specified to execute the kernel.
 *
 * @param dimindx
 * Valid values of dimindx are 0 to get_work_dim() - 1.  \n
 * For other values of dimindx, get_global_id() returns 0.
 * */
size_t get_global_id(uint dimindx);

/**
 * @returns
 * Returns the number of local work-items specified in dimension identified by dimindx.  \n
 *
 * @details
 * This value is at most the value given by the local_work_size argument to clEnqueueNDRangeKernel if local_work_size is not NULL; \n
 * otherwise the OpenCL implementation chooses an appropriate local_work_size value which is returned by this function. 
 *
 * If the kernel is executed with a non-uniform work-group size [1], \n
 * calls to this built-in from some work-groups may return different values than calls to this built-in from other work-groups.
 *
 * @param dimindx
 * Valid values of dimindx are 0 to get_work_dim() - 1. \n
 * For other values of dimindx, get_local_size() returns 1.
 * */
size_t get_local_size(uint dimindx);

/**
 * @brief
 * Returns the unique local work-item ID, \n
 * i.e. a work-item within a specific work-group for dimension identified by dimindx.
 *
 * @param dimindx
 * Valid values of dimindx are 0 to get_work_dim() - 1. \n
 * For other values of dimindx, get_local_id() returns 0.
 * */
size_t get_local_id(uint dimindx);

/**
 * @returns
 * Returns the number of work-groups that will execute a kernel for dimension identified by dimindx.
 *
 * @param dimindx
 * Valid values of dimindx are 0 to get_work_dim() - 1. \n
 * For other values of dimindx, get_num_groups() returns 1.
 * */
size_t get_num_groups(uint dimindx);


/**
 * @returns 
 * the offset values specified in global_work_offset argument to clEnqueueNDRangeKernel.
 *
 * @param dimindx
 * Valid values of dimindx are 0 to get_work_dim() - 1. \n
 * For other values, get_global_offset() returns 0.
 * */
size_t get_global_offset(uint dimindx);

/**
 * @returns the work-group ID which is a number from 0 .. get_num_groups(dimindx) - 1.
 *
 * @param dimindx
 * Valid values of dimindx are 0 to get_work_dim() - 1. \n
 * For other values, get_group_id() returns 0.
 * */
size_t get_group_id(uint dimindx);
#endif

#if ae2fVK_NCL(!)0

/**
 * @returns 
 * Returns the number of work-items in the sub-group. \n
 *
 * @details
 * This value is no more than the maximum sub-group size, \n
 * and is implementation-defined based on a combination of the compiled kernel and the dispatch dimensions. 
 *
 * This will be a constant value for the lifetime of the sub-group.
 * */
uint get_sub_group_size();

/**
 * @returns
 * Returns the maximum size of a sub-group within the dispatch. \n
 * This value will be invariant for a given set of dispatch dimensions and a kernel object compiled for a given device.
*/
uint get_max_sub_group_size();

/**
 * @returns
 * Returns the number of sub-groups that the current work-group is divided into. \n
 * This number will be constant for the duration of a work-group’s execution. 
 *
 * @details
 * If the kernel is executed with a non-uniform work-group size					\n
 * (i.e. the global_work_size values specified to clEnqueueNDRangeKernel			\n
 * 	are not evenly divisible by the local_work_size values for any dimension)		\n
 * , calls to this built-in from some work-groups may return different values than calls to this built-in from other work-groups.
 * */
uint get_num_sub_groups();

/**
 * @returns
 * Returns the same value as that returned by get_num_sub_groups if the kernel is executed with a uniform work-group size.
 *
 * @details 
 * If the kernel is executed with a non-uniform work-group size, \n
 * returns the number of sub-groups in each of the work-groups that make up the uniform region of the global range.
 * */
uint get_enqueued_num_sub_groups();

/**
 * @returns 
 * the sub-group ID which is a number from 0 .. get_num_sub_groups() - 1.
 *
 * @details
 * For clEnqueueTask, this returns 0.
 * */
uint get_sub_group_id();

/** 
 * @returns 
 * Returns the unique work-item ID within the current sub-group. 
 *
 * @details
 * The mapping from get_local_id(dimindx) to get_sub_group_local_id will be invariant for the lifetime of the work-group.
 * */
uint get_sub_group_local_id();
#endif

#endif
