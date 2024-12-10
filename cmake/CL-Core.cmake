include(../mod/ae2f/Core/cmake/Core.cmake)

# @brief 
# Copies all files under wanted include path to /pyinclude
# 
# @param ... 
# Absolute path where the files will be collected.
#
# @warning
# Notice that this must be absolute path
function(ae2fCL_AppendInclude)
    foreach(prm_IncludeDir ${ARGN})
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
    endforeach()
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
function(ae2fCL_AddConfProjTarDep prm_ProjName prm_SrcScanTar)
    if(NOT OpenCL_FOUND)
        message("I am finding OpenCL")
        find_package(OpenCL REQUIRED)
        link_libraries(OpenCL::OpenCL)
    endif()
    if(NOT TARGET "${prm_ProjName}-CLConfig")
        target_link_libraries(${prm_ProjName} PUBLIC OpenCL::OpenCL)

        add_custom_target(
            "${prm_ProjName}-CLConfig" COMMAND python3 
            ${ae2fCL_Core_Dir}/PyConfig.py 
            ${prm_SrcScanTar} ${OpenCL_INCLUDE_DIR} 
            ${CMAKE_C_COMPILER}
        )

        add_dependencies("${prm_ProjName}" "${prm_ProjName}-CLConfig")
        add_dependencies("${prm_ProjName}" OpenCL::OpenCL)
    endif()
endfunction()

# @brief
# Makes a Library installable. \n
# 
# 
# @param prm_TarName
# Library name you want.
# 
# @param prm_TarPrefix
# [STATIC | SHARED | INTERFACE]
# 
# @param prm_includeDir
# The include directory relative to the project CMakeLists.txt
# 
# @param ...
# The sources for the project.
function(ae2fCL_LibTent prm_TarName prm_TarPreFix prm_includeDir)
    ae2f_CoreLibProjTent(${prm_TarName} ${prm_TarPreFix} ${prm_includeDir})
    ae2fCL_AppendInclude(${PROJECT_SOURCE_DIR}/${prm_includeDir})
endfunction()