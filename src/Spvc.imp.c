#include "ae2f/Call.h"
#include <ae2fVK/Spvc.h>

#if !ae2f_MAC_BUILD
#error "This is not possible."
#endif

ae2f_SHAREDEXPORT void ae2fVK_SpvcMk(
		ae2f_err_t* restrict		reterr
		, ae2fVK_Spvc* restrict const	ret
		, const glslang_input_t* const	restrict inp
		, const glslang_stage_t		stage
		) {
	__ae2fVK_SpvcMk_C(reterr, ret, inp, stage);
}

ae2f_SHAREDEXPORT void ae2fVK_SpvcDel(
		ae2f_err_t* restrict		reterr
		, ae2fVK_Spvc* restrict const	block
		) {
	__ae2fVK_SpvcDel_C(reterr, block);
}
