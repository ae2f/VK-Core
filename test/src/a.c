#include <glslang/Include/glslang_c_shader_types.h>
#include <stdio.h>

#include <glslang/Include/glslang_c_interface.h>
#include <glslang/Public/resource_limits_c.h>
#include <ae2f/Cast.h>
#include <stdint.h>
#include <stddef.h>

typedef struct SpirVBinary {
    unsigned int*	words; // SPIR-V words
    size_t		size; // number of words in SPIR-V binary
} SpirVBinary;

glslang_program_t* program;

SpirVBinary compileShaderToSPIRV_Vulkan(glslang_stage_t stage, const char* restrict shaderSource) {
    const glslang_input_t input = {
        .language = GLSLANG_SOURCE_GLSL,
        .stage = stage,
        .client = GLSLANG_CLIENT_VULKAN,
        .client_version = GLSLANG_TARGET_VULKAN_1_2,
        .target_language = GLSLANG_TARGET_SPV,
        .target_language_version = GLSLANG_TARGET_SPV_1_5,
        .code = shaderSource,
        .default_version = 450,
        .default_profile = GLSLANG_NO_PROFILE,
        .force_default_version_and_profile = false,
        .forward_compatible = false,
        .messages = GLSLANG_MSG_DEFAULT_BIT,
        .resource = glslang_default_resource(),
    };
    
    glslang_shader_t* shader = glslang_shader_create(&input);

    SpirVBinary bin = {
        .words = NULL,
        .size = 0,
    };
    if (!glslang_shader_preprocess(shader, &input)) {
        puts("GLSL preprocessing failed");
        printf("%s\n", glslang_shader_get_info_log(shader));
        printf("%s\n", glslang_shader_get_info_debug_log(shader));
        printf("%s\n", input.code);
        glslang_shader_delete(shader);
        return bin;
    }

    if (!glslang_shader_parse(shader, &input)) {
        puts("GLSL parsing failed");
        printf("%s\n", glslang_shader_get_info_log(shader));
        printf("%s\n", glslang_shader_get_info_debug_log(shader));
        printf("%s\n", glslang_shader_get_preprocessed_code(shader));
        glslang_shader_delete(shader);
        return bin;
    }

    program = glslang_program_create();
    glslang_program_add_shader(program, shader);

    if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT)) {
        puts("GLSL linking failed");
        printf("%s\n", glslang_program_get_info_log(program));
        printf("%s\n", glslang_program_get_info_debug_log(program));
        glslang_program_delete(program);
        glslang_shader_delete(shader);
        return bin;
    }

    glslang_program_SPIRV_generate(program, stage);

    bin.size = glslang_program_SPIRV_get_size(program);
    bin.words = glslang_program_SPIRV_get_ptr(program);
    glslang_program_SPIRV_get(program, bin.words);

    const char* spirv_messages = glslang_program_SPIRV_get_messages(program);
    if (spirv_messages)
        printf("%s\b", spirv_messages);

    puts("Done");

    glslang_shader_delete(shader);

    return bin;
}

int main() {
	glslang_stage_t stage = GLSLANG_STAGE_COMPUTE;

	SpirVBinary bin = compileShaderToSPIRV_Vulkan(stage,
#include "../compute.auto.glsl.h"
			);

	printf(
			"SayLen: %lu\n"
			"bin2check %d %d\n"
			, bin.size

			, bin.words[0]
			, bin.words[1]
	      );


	glslang_program_delete(program);
	return 0;
}
