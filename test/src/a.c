#include <stdio.h>
#include <assert.h>

#include <ae2fVK/Spvc.h>

glslang_input_t input = {
	.language = GLSLANG_SOURCE_GLSL,
	.stage = GLSLANG_STAGE_COMPUTE,
	.client = GLSLANG_CLIENT_VULKAN,
	.client_version = GLSLANG_TARGET_VULKAN_1_2,
	.target_language = GLSLANG_TARGET_SPV,
	.target_language_version = GLSLANG_TARGET_SPV_1_5,
	.code = 
#include "../compute.auto.glsl.h"
		,
	.default_version = 450,
	.default_profile = GLSLANG_NO_PROFILE,
	.force_default_version_and_profile = false,
	.forward_compatible = false,
	.messages = GLSLANG_MSG_DEFAULT_BIT,
};

int main() {
	glslang_stage_t stage = GLSLANG_STAGE_COMPUTE;
	input.resource = glslang_default_resource();
	ae2fVK_Spvc spvc;
	ae2f_err_t err[1];

	ae2fVK_SpvcMk(
			err
			, &spvc, &input
			);

	assert(err[0]);

	printf(
			"SayLen: %lu\n"
			"bin2check %d %d\n"
			, spvc.m_spirv_sz
			, spvc.m_spirv_words[0]
			, spvc.m_spirv_words[1]
	      );

	ae2fVK_SpvcDel(&spvc);
	return 0;
}
