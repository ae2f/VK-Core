/**
 * @file CL-Core.cmake.hpp
 * @author ae2f
 * @brief 
 * @version 0.1
 * @date 2025-02-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "cmake.hpp"

namespace ___DOC_CMAKE {
    /// @brief 
    /// Is OpenCL needed.
    option ae2fCL_needed = ON;

    /// @brief
    /// Makes a Library installable.
    /// 
    /// Will be disabled when @ref ae2fCL_needed is @ref OFF. \n
    /// See @ref ae2f_CoreLibTent
    /// @param prm_TarName
    /// Library name you want.
    /// 
    /// @param prm_TarPrefix
    /// [STATIC | SHARED | INTERFACE]
    /// 
    /// @param prm_includeDir
    /// The include directory relative to the project CMakeLists.txt
    /// 
    /// @param prm_namespace
    /// Namespace (or header root directory after include)
    /// 
    /// @param ...
    /// The sources for the project.
    function ae2fCL_CoreLibTent(
        param prm_TarName, 
        param prm_TarPreFix, 
        param prm_includeDir, 
        param prm_namespace, 
        ...
    );

    /// @brief
    /// Note they functions defined on CMake, not C/C++.
    /// 
    /// Will be disabled when @ref ae2fCL_needed is @ref OFF. \n
    /// See @ref ae2f_CoreLibTent
    /// @brief
    /// Iterates a directory `prm_TestSourcesDir` and 
    /// Make a test case for every source.
    /// 
    /// @param prm_LibName
    /// Base Library name
    /// 
    /// @param prm_TestSourcesDir
    /// A directory where the stand-alone test codes locate. \n
    /// Every sources under that directory must be stand-alone, which means it must not depends on another memory, function, etc.
    /// 
    /// @param ...
    /// Additional Libraries if you want
    /// 
    /// @see ___DOC_CMAKE::ae2f_TEST
    function ae2fCL_CoreTestTent(
        param prm_LibName,
        param prm_TestSourcesDir,
        ...
    );

    /// @brief 
    /// Copies all files under wanted include path to /pyinclude
    ///
    /// @param ...
    /// Absolute path where the files will be collected.
    ///
    /// @warning
    /// Notice that this must be absolute path
    function ae2fCL_CoreAppendInclude(...);

    /// @brief 
    /// Make a configuration target for a ae2fCL Projects
    ///
    /// @param prm_ProjName 
    /// Your project name
    ///
    /// @param prm_SrcScanTar 
    /// The directory where your project's cl code exists.
    ///
    /// @warning
    /// Notice that this must be absolute.
    function ae2fCL_CoreAddConfProjTarDep(
        param prm_ProjName, 
        param prm_SrcScanTar
    );
}