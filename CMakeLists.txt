cmake_minimum_required(VERSION 3.10)

project(VK-Core VERSION 5.15.21)
enable_testing()

set(Vulkan_FOUND OFF)

if(NOT TARGET ${PROJECT_NAME})
    include(cmake/VK-Core.cmake)
    ae2f_CoreLibFetch(ae2f Core Rel-v6.19.12)

    ae2f_CoreLibTent(
        ${PROJECT_NAME} INTERFACE
        include ae2fVK
        "include/ae2fVK/Loc.h"
    )

    target_link_libraries(${PROJECT_NAME} INTERFACE Core)

    ae2fVK_CoreAppendInclude(${PROJECT_SOURCE_DIR}/include)
    ae2f_CoreUtilityDocTent(${PROJECT_NAME} cmake ae2fVK Core)

    if(${ae2f_TEST})
        find_package(Vulkan REQUIRED) 
        ae2fVK_CoreTestTent(${PROJECT_NAME} test)
    endif()
endif()
