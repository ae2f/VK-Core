include(cmake/Core.cmake)

option(ae2fVK_needed "Is Vulkan needed" ON)
set(ae2fVK_CoreDir ${PROJECT_SOURCE_DIR} CACHE STRING "")

if(NOT ae2f_vkincludecleaned)
    set(ae2f_vkincludecleaned ON CACHE STRING "")
    file(REMOVE_RECURSE ${ae2f_ProjRoot}/.vkinclude)
endif()

# @brief
# target_link_libraries for ae2fVK.
function(ae2fVK_target_link_libraries)
    if(ae2fVK_needed)
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
function(ae2fVK_CoreAppendInclude)
    foreach(prm_IncludeDir ${ARGN})
        file(GLOB_RECURSE INVKUDE_TAR "${prm_IncludeDir}/**")
        
        foreach(tar IN LISTS INVKUDE_TAR)
            file(RELATIVE_PATH tar_rel "${prm_IncludeDir}" "${tar}")
            configure_file("${prm_IncludeDir}/${tar_rel}" "${ae2f_ProjRoot}/.vkinclude/${tar_rel}")
        endforeach()

        unset (INVKUDE_TAR)
        unset (tar_rel)
    endforeach()
endfunction()

# @brief
# Makes a Library installable. \n
# Will be disabled when @ref ae2fVK_needed is @ref OFF.
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
function(ae2fVK_CoreLibTent prm_TarName prm_TarPreFix prm_includeDir prm_namespace)
    if(ae2fVK_needed)
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
# Will be disabled when @ref ae2fVK_needed is @ref OFF. \n
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
function(ae2fVK_CoreTestTent prm_LibName prm_TestSourcesDir)
    if(ae2fVK_needed)
        ae2f_CoreTestTent(
            ${prm_LibName} 
            ${prm_TestSourcesDir} 
            ${ARGN}
        )
    endif()
endfunction()



# @brief 
# Make a configuration target for a ae2fVK Projects
#
# @param prm_ProjName 
# Your project name
#
# @param prm_SrcScanTar 
# The directory where your project's vulkan code exists.
#
# @warning
# Notice that this must be absolute.
function(ae2fVK_CoreAddConfProjTarDep prm_ProjName prm_SrcScanTar)
    if(ae2fVK_needed)
        if(NOT Vulkan_FOUND)
            find_package(Vulkan REQUIRED)
        endif()
        if(NOT TARGET "${prm_ProjName}-VKConfig")
        	target_link_libraries(${prm_ProjName} PUBLIC Vulkan::Vulkan)

        	add_custom_target(
                	"${prm_ProjName}-VKConfig" 

			COMMAND 
			sh
			${ae2fVK_CoreDir}/cmake/VKDir.sh
                	${prm_SrcScanTar} ${Vulkan_INCLUDE_DIR} 
                	${CMAKE_C_COMPILER}
                	${ae2f_ProjRoot}

			WORKING_DIRECTORY 
			${ae2fVK_CoreDir}/cmake
		)

            add_dependencies("${prm_ProjName}" "${prm_ProjName}-VKConfig")
            add_dependencies("${prm_ProjName}" Vulkan::Vulkan)
        endif()
    endif()
endfunction()
