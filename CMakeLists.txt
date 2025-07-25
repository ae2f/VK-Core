option(ae2fVK_needed	"Is Vulkan needed"	ON)
option(ae2f_MAC_BUILD	"" ON)
option(ae2f_DEVEL	"" OFF)

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

if(ae2fVK_needed)
	find_package(Vulkan REQUIRED)
	# find_package(glslang)

	if(glslang_FOUND)
		add_library(ae2f-glslang glslang::glslang)
	else()
		message("[glslang] not found.")
		option(ALLOW_EXTERNAL_SPIRV_TOOLS	"" ON)
		option(GLSLANG_ENABLE_INSTALL		"" ON)

		ae2f_CoreLibFetch_NS(KhronosGroup KhronosGroup SPIRV-Headers	main)
		ae2f_CoreLibFetch_NS(KhronosGroup KhronosGroup SPIRV-Tools	main)
		ae2f_CoreLibFetch_NS(KhronosGroup glslang glslang main)

		if(WIN32 AND ae2f_IS_SHARED)
			set(ae2f-glslang glslang)
		else()
			set(ae2f-glslang glslang::glslang)
		endif()
	endif()
endif()

if(NOT TARGET ae2fVK::Core)
	ae2f_CoreLibFetch(ae2f Core		main)
	ae2f_CoreLibFetch(ae2f Preproc		main)

	if(ae2f_DEVEL)
		file(GLOB_RECURSE ae2fVK-Core-defcc ${PROJECT_SOURCE_DIR}/src/*.def.cc)
	else()
		set(ae2fVK-Core-defcc "")
	endif()

	file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/inc/ae2fVK)
	ae2f_Macro_Lib_V(
		ae2fVK Core ${ae2f_LIBPREFIX}
		${PROJECT_SOURCE_DIR}/src "*.imp.c"
		${PROJECT_SOURCE_DIR}/src "*.def.c*"
		${PROJECT_SOURCE_DIR}/inc/ae2fVK ".h"
		${PROJECT_SOURCE_DIR}/Config.cmake.in
		inc ${ae2fVK-Core-defcc}
	)

	ae2f_titil(${ae2fVK__Core__TENT} ae2f::Core)
	ae2f_titil(${ae2fVK__Core__TENT} ae2f::Preproc)

	if(ae2fVK_needed)
		ae2f_titil(${ae2fVK__Core__TENT} Vulkan::Vulkan)
		ae2f_titil(${ae2fVK__Core__TENT} ${ae2f-glslang})
		ae2f_titil(${ae2fVK__Core__TENT} glslang::glslang-default-resource-limits)
	endif()

	ae2fVK_CoreAppendInclude(${PROJECT_SOURCE_DIR}/inc)
	add_dependencies(${ae2fVK__Core__TENT} glslang::glslang)

	if(ae2f_TEST)
		find_package(Vulkan REQUIRED)
		if(ON)
			ae2f_FileRaw_init(ON 1)
			ae2f_FileRaw_Run_One(
				${PROJECT_SOURCE_DIR}/test-shader/compute.glsl 
				${PROJECT_SOURCE_DIR}/test/compute.auto.glsl.h
			)
		endif()
		ae2f_CoreTestTent(${ae2fVK__Core__TENT} test/src)
	endif()
endif()
