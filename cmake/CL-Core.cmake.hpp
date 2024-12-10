#include <Core.cmake.hpp>

namespace ___DOC_CMAKE {
    /// @brief 
    /// Pre-defined CL-Core's Directory
    CACHE STRING ae2fCL_Core_Dir;

    /// @brief 
    /// Copies all files under wanted include path to /pyinclude
    ///
    /// @param ...
    /// Absolute path where the files will be collected.
    ///
    /// @warning
    /// Notice that this must be absolute path
    constexpr void ae2fCL_CoreAppendInclude(...);

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
    constexpr void ae2fCL_CoreAddConfProjTarDep(auto prm_ProjName, auto prm_SrcScanTar);
}