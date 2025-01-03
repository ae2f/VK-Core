cmake_minimum_required(VERSION 3.10)

project(CL-Core VERSION 4.4.13)
enable_testing()

if(NOT TARGET ${PROJECT_NAME})
    include(cmake/CL-Core.cmake)

    ae2f_CoreLibFetch(ae2f Core Rel-v6.14.11)

    ae2f_CoreLibTent(
        ${PROJECT_NAME} INTERFACE
        include ae2fCL
        "include/ae2fCL/Loc.h"
        "include/ae2fCL/Scenario.h"
    )

    target_link_libraries(${PROJECT_NAME} INTERFACE Core)

    ae2fCL_CoreAppendInclude(${PROJECT_SOURCE_DIR}/include)
    ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2fCL Core)

endif()