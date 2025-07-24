include(cmake/Core.cmake)

option(ae2fVK_needed	"Is Vulkan needed" ON)
set(ae2fVK_CoreDir	${PROJECT_SOURCE_DIR} CACHE STRING "")
set(ae2fVK_IncList	"")

# @brief 
# Copies all files under wanted include path to /clinclude
# 
# @param ... 
# Absolute path where the files will be collected.
#
# @warning
# Notice that this must be absolute path
function(ae2fVK_CoreAppendInclude)
	string(APPEND ae2fVK_IncList " ${ARGN}")
endfunction()

# Convert a c-like code into glsl compilable, removing the include.
function(ae2fVK_Cvrt_one prm_in prm_out)
	ae2f_Inc_Run_One(${prm_in} ${prm_out})
endfunction()
