#undef	__ae2f_MACRO_GENERATED
#define	__ae2f_MACRO_GENERATED	1
#ifndef ae2fVK_Spvc_h
#define ae2fVK_Spvc_h

#include <glslang/Include/glslang_c_interface.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1
#include <glslang/Public/resource_limits_c.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1

#include <ae2f/Call.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1
#include <ae2f/Cast.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1
#include <ae2f/errGlob.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1

#include <stdint.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1
#include <ae2f/Macro.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1

ae2f_structdef(struct, ae2fVK_Spvc) {
	glslang_shader_t*	restrict m_shader;
	glslang_program_t*	restrict m_programme;
	unsigned int*		restrict m_spirv_words;
	size_t			m_spirv_sz;
};

#if ae2f_MAC_BUILD

ae2f_extern ae2f_SHAREDCALL void ae2fVK_SpvcMk(
		ae2f_err_t* restrict		reterr
		, ae2fVK_Spvc* restrict const	ret
		, const glslang_input_t* const	restrict inp
		, const glslang_stage_t		stage
		);

ae2f_extern ae2f_SHAREDCALL void ae2fVK_SpvcDel(
		ae2f_err_t* restrict		reterr
		, ae2fVK_Spvc* restrict const	block
		);

#else

#define ae2fVK_SpvcMk	__ae2fVK_SpvcMk_C
#define ae2fVK_SpvcDel	__ae2fVK_SpvcDel_C

#endif // ae2f_MAC_BUILD

#endif

#ifndef ae2fVK_Spvc_c

#if !__ae2f_MACRO_GENERATED
#include <ae2fVK/Spvc.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1
#endif
#define ae2fVK_Spvc_c

#include <ae2f/Macro.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1
#include <assert.h>
#undef __ae2f_MACRO_GENERATED
#define __ae2f_MACRO_GENERATED 1

#define __ae2fVK_SpvcMk_imp( \
	/** tparam */ \
		 \
 \
	/** param */ \
		/*    ,    int    */ v_ret_isgood, \
		/*     ae2fVK_Spvc    */ v_ret, \
		/*   constglslang_input_t*  const restrict    */ inp, \
		/*   const  glslang_stage_t    */ stage \
) \
{ \
	do { \
		assert(inp); \
		(v_ret).m_shader = glslang_shader_create(inp); \
		(v_ret).m_programme = glslang_program_create(); \
 \
		assert(((v_ret).m_shader && (v_ret).m_programme) && "initiating has failed."); \
		if(!(v_ret).m_shader) { \
			break; \
		} \
 \
		(v_ret_isgood) = glslang_shader_preprocess((v_ret).m_shader, inp); \
		assert((v_ret_isgood) && "GLSL preprocessing failed."); \
		if(!v_ret_isgood) { \
			break; \
		} \
 \
		(v_ret_isgood) = glslang_shader_parse((v_ret).m_shader, inp); \
		assert((v_ret_isgood) && "GLSL parsing failed."); \
		if(!v_ret_isgood) { \
			break; \
		} \
 \
		glslang_program_add_shader( \
				(v_ret).m_programme \
				, (v_ret).m_shader \
				); \
 \
		(v_ret_isgood) = glslang_program_link( \
				(v_ret).m_programme \
				, stage \
				); \
 \
		(v_ret_isgood) = glslang_shader_parse((v_ret).m_shader, inp); \
		assert((v_ret_isgood) && "GLSL linking failed."); \
		if(!v_ret_isgood) { \
			break; \
		} \
 \
		glslang_program_SPIRV_generate((v_ret).m_programme, stage); \
		(v_ret).m_spirv_words = glslang_program_SPIRV_get_ptr((v_ret).m_programme); \
		(v_ret).m_spirv_sz = glslang_program_SPIRV_get_size((v_ret).m_programme); \
 \
		assert((v_ret).m_spirv_words); \
		assert((v_ret).m_spirv_sz); \
	} while(0); \
}

#define __ae2fVK_SpvcMk( \
	/** tparam */ \
		 \
 \
	/** param */ \
		/*    ,ae2f_err_t*   restrict    */ reterr, \
		/*  ae2fVK_Spvc*  restrict const    */ ret, \
		/*   constglslang_input_t*  const restrict    */ inp, \
		/*   const  glslang_stage_t    */ stage \
) \
{ \
	assert(ret); \
	if((reterr) && *(reterr)) \
		; \
	else unless(ret) { \
		(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL); \
	} else { \
		int v_isgood; \
		__ae2fVK_SpvcMk_imp(v_isgood, *(ret), inp, stage); \
		assert(v_isgood); \
		v_isgood || (*(reterr) |= ae2f_errGlob_ALLOC_FAILED); \
	} \
}

#define __ae2fVK_SpvcMk_C	__ae2fVK_SpvcMk

#define __ae2fVK_SpvcDel_imp( \
	/** tparam */ \
		 \
 \
	/** param */ \
		/* , ae2fVK_Spvc */ v_block \
) { \
	if((v_block).m_programme)  \
		glslang_program_delete((v_block).m_programme); \
	if((v_block).m_shader)  \
		glslang_shader_delete((v_block).m_shader); \
 \
}

#define __ae2fVK_SpvcDel( \
	/** tparam */ \
		 \
 \
	/** param */ \
		/*    ,ae2f_err_t*   restrict    */ reterr, \
		/*  ae2fVK_Spvc*  restrict const    */ block \
) { \
	assert(block); \
 \
	if((reterr) && *(reterr)); \
	else unless(block) { \
		(reterr) && (*(reterr) |= ae2f_errGlob_PTR_IS_NULL); \
	} else { \
		__ae2fVK_SpvcDel_imp(*(block)); \
		(block)->m_programme = 0; \
		(block)->m_shader = 0; \
		(block)->m_spirv_words = 0; \
		(block)->m_spirv_sz = 0; \
	} \
}

#define __ae2fVK_SpvcDel_C __ae2fVK_SpvcDel

#endif

#undef	__ae2f_MACRO_GENERATED

#define	__ae2f_MACRO_GENERATED	0

