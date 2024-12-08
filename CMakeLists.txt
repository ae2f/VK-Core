cmake_minimum_required(VERSION 3.20)

project(CL-Core VERSION 1.2.2)
enable_testing()
if(NOT TARGET ${PROJECT_NAME})

# Namespace Package
include(GNUInstallDirs)

add_subdirectory(mod/ae2f/Core)
link_libraries(Core)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    "include/ae2fCL/Loc.h"
    "include/ae2fCL/Scenario.h"
)

set(ae2fCL_Core_Dir "${PROJECT_SOURCE_DIR}" CACHE STRING "Do not touch it. It is a pre-defined source directory.")
message("ae2fCL_Core_Dir: ${ae2fCL_Core_Dir}")
set(ae2fCL_PyConfigPath "${ae2fCL_Core_Dir}/PyConfig.py" CACHE STRING "Do not touch it. It is a pre-defined path for config function (ae2fCL-Core)")

# clean
file(REMOVE_RECURSE ${ae2fCL_Core_Dir}/pyinclude)

# copies all files under wanted include path to /pyinclude
# 
# prm_IncludeDir: must be absolute path to include.
function(ae2fCL_AppendInclude prm_IncludeDir)
    message(STATUS "ae2fCL_AppendInclude is activating.")
    message(STATUS "Searching for ${prm_IncludeDir}...")
    message(STATUS "")
    file(GLOB_RECURSE INCLUDE_TAR "${prm_IncludeDir}/**")
    
    foreach(tar IN LISTS INCLUDE_TAR)
        file(RELATIVE_PATH tar_rel "${prm_IncludeDir}" "${tar}")
        message(STATUS "We are configuring ${tar_rel}.")
        configure_file("${prm_IncludeDir}/${tar_rel}" "${ae2fCL_Core_Dir}/pyinclude/${tar_rel}")
    endforeach()

    unset (INCLUDE_TAR)
    unset (tar_rel)

    message(STATUS "")
    message(STATUS "ae2fCL_AppendInclude is over.")
endfunction()

# Make a configuration file for a ae2fCL Projects
# 
# prm_ProjName: Your project name
# prm_SrcScanTar: The directory where your project's cl code exists. It must be absolute
function(ae2fCL_AddConfProjTarDep prm_ProjName prm_SrcScanTar)
    if(NOT OpenCL_FOUND)
        message("I am finding OpenCL")
        find_package(OpenCL REQUIRED)
        link_libraries(OpenCL::OpenCL)
    endif()
    if(NOT TARGET "${prm_ProjName}-ae2fCLConfig")
        target_link_libraries(${prm_ProjName} PUBLIC OpenCL::OpenCL)

        add_custom_target("${prm_ProjName}-ae2fCLConfig" COMMAND python3 ${ae2fCL_PyConfigPath} ${prm_SrcScanTar} ${OpenCL_INCLUDE_DIR})
        add_dependencies("${prm_ProjName}" "${prm_ProjName}-ae2fCLConfig")
        add_dependencies("${prm_ProjName}" OpenCL::OpenCL)
    endif()
endfunction()

ae2fCL_AppendInclude(${PROJECT_SOURCE_DIR}/include)

include_directories(include)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/ae2f/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ae2f
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ae2f::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

endif()