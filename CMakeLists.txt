cmake_minimum_required(VERSION 3.10)

project(CL-Core VERSION 4.4.10)
enable_testing()
if(NOT TARGET ${PROJECT_NAME})

add_subdirectory(mod/ae2f/Core)
include(cmake/CL-Core.cmake)

set(ae2fCL_Core_Dir "${PROJECT_SOURCE_DIR}" CACHE STRING "Do not touch it. It is a pre-defined source directory.")

# clean
file(REMOVE_RECURSE ${ae2fCL_Core_Dir}/pyinclude)

ae2f_CoreLibTent(
    ${PROJECT_NAME} INTERFACE
    include ae2fCL
    "include/ae2fCL/Loc.h"
    "include/ae2fCL/Scenario.h"
)

ae2fCL_CoreAppendInclude(${PROJECT_SOURCE_DIR}/include)
ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2fCL Core)

endif()