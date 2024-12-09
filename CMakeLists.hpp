namespace ____ae2f_Core_Def_CMAKE {
    /// @brief 
    /// Pre-defined CL-Core's Directory
    constexpr const char* ae2fCL_Core_Dir;

    /// @brief 
    /// Copies all files under wanted include path to /pyinclude
    ///
    /// @param ...
    /// Absolute path where the files will be collected.
    ///
    /// @warning
    /// Notice that this must be absolute path
    constexpr void ae2fCL_AppendInclude(...);

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
    constexpr void ae2fCL_AddConfProjTarDep(auto prm_ProjName, auto prm_SrcScanTar);

    /// @brief
    /// Makes a Library installable. \n
    /// 
    /// 
    /// @param prm_TarName
    /// Library name you want.
    /// 
    /// @param prm_TarPrefix
    /// [STATIC | SHARED | INTERFACE]
    /// 
    /// @param prm_includeDir
    /// The include directory relative to the project CMakeLists.txt
    /// 
    /// @param ...
    /// The sources for the project.
    constexpr void ae2fCL_LibTent(auto prm_TarName, auto prm_TarPreFix, auto prm_includeDir);
}