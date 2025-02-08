cmake_minimum_required(VERSION 3.10)

project(CL-Core VERSION 4.13.14)
enable_testing()

if(NOT TARGET ${PROJECT_NAME})
    include(cmake/CL-Core.cmake)
    ae2f_CoreLibFetch(ae2f Core Rel-v6.18.11)

    ae2fCL_CoreLibTent(
        ${PROJECT_NAME} INTERFACE
        include ae2fCL
        "include/ae2fCL/Loc.h"
        "include/ae2fCL/Scenario.h"
    )

    ae2fCL_target_link_libraries(${PROJECT_NAME} INTERFACE Core)

    ae2fCL_CoreAppendInclude(${PROJECT_SOURCE_DIR}/include)
    ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2fCL Core)

    if(${ae2f_TEST})
        find_package(OpenCL REQUIRED) 
        ae2fCL_CoreTestTent(${PROJECT_NAME} test OpenCL::OpenCL)
    endif()
endif()