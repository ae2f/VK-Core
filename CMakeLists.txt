option(ae2fVK_needed	"Is Vulkan needed"	ON)
option(ae2f_MAC_BUILD	"" ON)
option(ae2f_DEVEL	"" OFF)
option(ae2f_TEST	"" ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

cmake_minimum_required(VERSION 3.10)

project(VK-Core VERSION 5.15.22)
enable_testing()

if(ae2f_MAC_BUILD)
	function(ae2f_titil tar)
		target_link_libraries(${tar} PUBLIC ${ARGN})
	endfunction()
else()
	function(ae2f_titil tar)
		target_link_libraries(${tar} INTERFACE ${ARGN})
	endfunction()
endif()

include(cmake/VK-Core.cmake)
ae2f_CoreLibFetch(ae2f Core		main)
ae2f_CoreLibFetch(ae2f Preproc		main)

if(ae2fVK_needed)
	find_package(Vulkan REQUIRED)
endif()

option(ae2fVK_need_glslang "" OFF)
if(ae2fVK_need_glslang AND NOT TARGET ae2fVK::Spvc)
	find_package(glslang)

	if(glslang_FOUND)
		set(ae2f-glslang glslang::glslang)
	else()
		message("[glslang] not found.")
		option(ALLOW_EXTERNAL_SPIRV_TOOLS	"" ON)
		option(GLSLANG_ENABLE_INSTALL		"" ON)

		if(NOT spirvtool)
			set(spirvtool ON)
			ae2f_CoreLibFetch_NS(KhronosGroup KhronosGroup SPIRV-Headers	main)
			ae2f_CoreLibFetch_NS(KhronosGroup KhronosGroup SPIRV-Tools	main)
		endif()

		option(ALLOW_EXTERNAL_SPIRV_TOOLS "" ON)

		ae2f_CoreLibFetch_NS(KhronosGroup glslang glslang main)
		set(ae2f-glslang glslang)
	endif()

	if(ae2f_DEVEL)
		file(GLOB_RECURSE Spvc-defcc ${PROJECT_SOURCE_DIR}/src/Spvc.def.cc)
	else()
		set(Spvc-defcc "")
	endif()

	ae2f_Macro_Lib_V(
		ae2fVK Spvc ${ae2f_LIBPREFIX}
		${PROJECT_SOURCE_DIR}/src "Spvc.imp.c"
		${PROJECT_SOURCE_DIR}/src "Spvc.def.c*"
		${PROJECT_SOURCE_DIR}/inc/ae2fVK ".h"
		${PROJECT_SOURCE_DIR}/Config.cmake.in
		inc ${Spvc-defcc}
	)

	ae2f_titil(${ae2fVK__Spvc__TENT} ae2f::Core)
	ae2f_titil(${ae2fVK__Spvc__TENT} ae2f::Preproc)
	ae2f_titil(${ae2fVK__Spvc__TENT} ${ae2f-glslang})
	ae2f_titil(${ae2fVK__Spvc__TENT} glslang::glslang-default-resource-limits)

	if(ae2f_TEST)
		ae2f_FileRaw_init(ON 1)
		ae2f_FileRaw_Run_One(
			${PROJECT_SOURCE_DIR}/test-shader/compute.glsl 
			${PROJECT_SOURCE_DIR}/test/compute.auto.glsl.h
		)

		ae2f_CoreTestTent(
			${ae2fVK__Spvc__TENT}
			test/spvc/
		)
	endif()
endif()

option(ae2fVK_need_clspv "" OFF)
if(ae2fVK_need_clspv)
	add_library(ae2fVK_clspv INTERFACE "inc/ae2fVK/clspv_clkeys.h" "inc/ae2fVK/clspv.h")
	add_library(ae2fVK::clspv ALIAS ae2fVK_clspv)
	option(CLSPV_SHARED_LIB "" ${ae2f_TEST})

	if(NOT EXISTS ${ae2f_ProjRoot}/${ae2f_submod}/google/clspv)
		execute_process(
			WORKING_DIRECTORY
			${ae2f_ProjRoot}

			COMMAND 
			git clone --recursive 
			https://github.com/ae2f/clspv ${ae2f_submod}/google/clspv
		)
	endif()

	option(CLSPV_USE_SYSTEM_LLVM "Use system LLVM" OFF)
	if(NOT CLSPV_USE_SYSTEM_LLVM)
		if(NOT EXISTS ${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/third_party)
			execute_process(
				WORKING_DIRECTORY
				${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/

				COMMAND
				git clone https://codeberg.org/dalmurii/llvm third_party/llvm --depth 1
				)
		endif()

		if(NOT EXISTS ${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/third_party/llvm)
			execute_process(
				WORKING_DIRECTORY
				${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/third_party

				COMMAND
				git clone https://codeberg.org/dalmurii/llvm --depth 1
				)
		endif()
	endif()

	if(NOT EXISTS ${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/third_party/SPIRV-Tools)
		execute_process(
			WORKING_DIRECTORY
			${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/third_party

			COMMAND
			git clone https://github.com/KhronosGroup/SPIRV-Tools SPIRV-Tools
			)
	endif()

	if(NOT EXISTS ${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/third_party/SPIRV-Headers)
		execute_process(
			WORKING_DIRECTORY
			${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/third_party

			COMMAND
			git clone https://github.com/KhronosGroup/SPIRV-Headers SPIRV-Headers
			)
	endif()

	option(ENABLE_CLSPV_TOOLS_INSTALL ""	ON)
	option(ENABLE_CLSPV_INSTALL ""		ON)

  set(CLSPV_SHARED_LIB ${ae2f_IS_SHARED} CACHE BOOL "")
  set(LLVM_BUILD_LLVM_DYLIB ${ae2f_IS_SHARED} CACHE BOOL "")
  set(LLVM_LINK_LLVM_DYLIB ${ae2f_IS_SHARED} CACHE BOOL "")

  message("LNKLLVMDYLIB: ${LLVM_LINK_LLVM_DYLIB}")

	add_subdirectory(
		${ae2f_ProjRoot}/${ae2f_submod}/google/clspv
		${ae2f_BinRoot}/${ae2f_submod}/google/clspv
	)

	install(TARGETS clspv_core clspv_passes
	 	EXPORT ae2fVK_clspvTargets
	 	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	 	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	 	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

	target_link_libraries(ae2fVK_clspv INTERFACE clspv_core)
  target_include_directories(
    ae2fVK_clspv INTERFACE 
    $<BUILD_INTERFACE:${ae2f_ProjRoot}/${ae2f_submod}/google/clspv/include/>
    $<INSTALL_INTERFACE:include/>
  )
	ae2f_CoreTestTent(ae2fVK_clspv test/clspv/)
endif()

option(ae2fVK_need_slang "" OFF) # on test.
if(OFF AND ae2fVK_needed AND ae2fVK_need_slang AND NOT TARGET ae2fVK::Slang)

	if(ae2f_DEVEL)
		file(GLOB_RECURSE Slang-defcc ${PROJECT_SOURCE_DIR}/src/Slang.def.cc)
	else()
		set(Slang-defcc "")
	endif()

	ae2f_CoreLibFetch_NS(KhronosGroup KhronosGroup SPIRV-Headers	main)
	ae2f_CoreLibFetch_NS(KhronosGroup KhronosGroup SPIRV-Tools	main)
	find_package(Vulkan REQUIRED)
	# ae2f_CoreLibFetch_NS(shader-slang slang slang master --preset release)

	ae2f_Macro_Lib_V(
		ae2fVK Slang ${ae2f_LIBPREFIX}
		${PROJECT_SOURCE_DIR}/src "Slang.imp.c"
		${PROJECT_SOURCE_DIR}/src "Slang.def.c*"
		${PROJECT_SOURCE_DIR}/inc/ae2fVK ".h"
		${PROJECT_SOURCE_DIR}/Config.cmake.in
		inc ${Slang-defcc}
	)

	ae2f_titil(${ae2fVK__Slang__TENT} Vulkan::Vulkan)
endif()

if(NOT TARGET ae2fVK::Core)
	file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/inc/ae2fVK)
  file(GLOB_RECURSE vkcore-inc ${PROJECT_SOURCE_DIR}/inc/ae2fVK/*)
	ae2f_CoreLibTent(Core INTERFACE inc ae2fVK ${vkcore-inc})

	add_library(ae2f::VK-Core ALIAS ${ae2fVK__Core__TENT})
	add_library(ae2fVK::VK-Core ALIAS ${ae2fVK__Core__TENT})

	target_link_libraries(${ae2fVK__Core__TENT} 
		INTERFACE ae2f::Core
		INTERFACE ae2f::Preproc
	)

	if(ae2fVK_needed)
		target_link_libraries(${ae2fVK__Core__TENT} INTERFACE Vulkan::Vulkan)
	endif()

	if(ae2fVK_need_glslang)
		target_link_libraries(${ae2fVK__Core__TENT} INTERFACE ae2fVK::Spvc)
	endif()

	if(ae2fVK_need_slang)
		target_link_libraries(${ae2fVK__Core__TENT} INTERFACE ae2fVK::Slang)
	endif()

	if(ae2fVK_need_clspv)
		target_link_libraries(${ae2fVK__Core__TENT} INTERFACE ae2fVK::clspv)
		install(TARGETS ae2fVK_clspv clspv_core clspv_passes
			EXPORT ${ae2fVK__Core__TENT}Targets
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		)
	endif()

	ae2fVK_CoreAppendInclude(${PROJECT_SOURCE_DIR}/inc)
endif()
