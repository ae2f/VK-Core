include(cmake/Core.cmake)

option(ae2fCL_needed "Is OpenCL needed" ON)
set(ae2fCL_CoreDir ${PROJECT_SOURCE_DIR} CACHE STRING "")

if(NOT ae2f_clincludecleaned)
    set(ae2f_clincludecleaned ON CACHE STRING "")
    file(REMOVE_RECURSE ${ae2f_ProjRoot}/clinclude)
endif()

# @brief
# Check if opencl is found and you are desired to activate it. 
function(ae2fCL_CheckNeeded)
    message("ae2fCL_CheckNeeded is deprecated.")
endfunction()

# @brief
# target_link_libraries for ae2fCL.
function(ae2fCL_target_link_libraries)
    if(ae2fCL_needed)
        target_link_libraries(${ARGN})
    endif()
endfunction()

# @brief 
# Copies all files under wanted include path to /clinclude
# 
# @param ... 
# Absolute path where the files will be collected.
#
# @warning
# Notice that this must be absolute path
function(ae2fCL_CoreAppendInclude)
    foreach(prm_IncludeDir ${ARGN})
        file(GLOB_RECURSE INCLUDE_TAR "${prm_IncludeDir}/**")
        
        foreach(tar IN LISTS INCLUDE_TAR)
            file(RELATIVE_PATH tar_rel "${prm_IncludeDir}" "${tar}")
            configure_file("${prm_IncludeDir}/${tar_rel}" "${ae2f_ProjRoot}/clinclude/${tar_rel}")
        endforeach()

        unset (INCLUDE_TAR)
        unset (tar_rel)
    endforeach()
endfunction()

# @brief
# Makes a Library installable. \n
# Will be disabled when @ref ae2fCL_needed is @ref OFF.
# 
# See @ref ae2f_CoreLibTent
# @param prm_TarName
# Library name you want.
# 
# @param prm_TarPrefix
# [STATIC | SHARED | INTERFACE]
# 
# @param prm_includeDir
# The include directory relative to the project CMakeLists.txt
# 
# @param prm_namespace
# Namespace (or header root directory after include)
# 
# @param ...
# The sources for the project.
function(ae2fCL_CoreLibTent prm_TarName prm_TarPreFix prm_includeDir prm_namespace)
    if(ae2fCL_needed)
        ae2f_CoreLibTent(
            ${prm_TarName} 
            ${prm_TarPreFix} 
            ${prm_includeDir} 
            ${prm_namespace} 
            ${ARGN}
        )
    endif()
endfunction()

# @brief
# Note they functions defined on CMake, not C/C++.
# 
# Will be disabled when @ref ae2fCL_needed is @ref OFF. \n
# See @ref ae2f_CoreLibTent
# @brief
# Iterates a directory `prm_TestSourcesDir` and 
# Make a test case for every source.
# 
# @param prm_LibName
# Base Library name
# 
# @param prm_TestSourcesDir
# A directory where the stand-alone test codes locate. \n
# Every sources under that directory must be stand-alone, which means it must not depends on another memory, function, etc.
# 
# @param ...
# Additional Libraries if you want
# 
# @see ___DOC_CMAKE::ae2f_TEST
function(ae2fCL_CoreTestTent prm_LibName prm_TestSourcesDir)
    if(ae2fCL_needed)
        ae2f_CoreTestTent(
            ${prm_LibName} 
            ${prm_TestSourcesDir} 
            ${ARGN}
        )
    endif()
endfunction()


# @brief 
# Make a configuration target for a ae2fCL Projects
#
# @param prm_ProjName 
# Your project name
#
# @param prm_SrcScanTar 
# The directory where your project's cl code exists.
#
# @warning
# Notice that this must be absolute.
function(ae2fCL_CoreAddConfProjTarDep prm_ProjName prm_SrcScanTar)
    if(ae2fCL_needed)
        if(NOT OpenCL_FOUND)
            find_package(OpenCL REQUIRED)
        endif()
        if(NOT TARGET "${prm_ProjName}-CLConfig")
            target_link_libraries(${prm_ProjName} PUBLIC OpenCL::OpenCL)

            add_custom_target(
                "${prm_ProjName}-CLConfig" COMMAND sh
                ${ae2fCL_CoreDir}/cmake/CL-CoreConfig.sh
                ${prm_SrcScanTar} ${OpenCL_INCLUDE_DIR} 
                ${CMAKE_C_COMPILER}
                ${ae2f_ProjRoot}
            )

            add_dependencies("${prm_ProjName}" "${prm_ProjName}-CLConfig")
            add_dependencies("${prm_ProjName}" OpenCL::OpenCL)
        endif()
    endif()
endfunction()