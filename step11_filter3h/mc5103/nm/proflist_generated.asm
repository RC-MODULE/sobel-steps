
//****************************************************************************************
// This is automaticly generated asm-file by generate_proflist.bat (generate_proflist.tcl )
// Use this script to parse map-file to extract functions from abs-file 
// and to generate initial asm-template for profiling.
// It is recommended to remove  all unnecessary functions to make profiling more precise.
//****************************************************************************************
import from profiler.mlb;

PROFILE_BEGIN(16);



	// place here macros with function name for each function you wish to profile like:
	// PROFILE_FUNC(_myfunc,"myfunc");

	PROFILE_FUNC(_CSobel.8.8CSobel.1int.9._int.2,"_CSobel.8.8CSobel.1int.9._int.2");
	PROFILE_FUNC(_CSobel.8.8.aCSobel.1.2,"_CSobel.8.8.aCSobel.1.2");
	PROFILE_FUNC(_int._CSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2,"_int._CSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2");
	PROFILE_FUNC(_void._.0.8.8shared_malloc32.1unsigned._int.2,"_void._.0.8.8shared_malloc32.1unsigned._int.2");
	PROFILE_FUNC(_void._.8.8free32.1void._.0.2,"_void._.8.8free32.1void._.0.2");
	PROFILE_NONSTD_FUNC(Mul32,"Mul32");
	PROFILE_FUNC(_malloc0,"_malloc0");
	PROFILE_FUNC(_malloc1,"_malloc1");
	PROFILE_FUNC(_malloc2,"_malloc2");
	PROFILE_FUNC(_malloc3,"_malloc3");
	PROFILE_FUNC(_void._.0.8.8malloc32.1unsigned._int.2,"_void._.0.8.8malloc32.1unsigned._int.2");
	PROFILE_FUNC(_char._.0.8.8VEC_Addr.1char._const._.0.9._int.2,"_char._.0.8.8VEC_Addr.1char._const._.0.9._int.2");
	PROFILE_FUNC(_short._.0.8.8VEC_Addr.1short._.0.9._int.2,"_short._.0.8.8VEC_Addr.1short._.0.9._int.2");
	PROFILE_FUNC(_void._.8.8VEC_Abs1.1short._.0.9._short._.0.9._int.2,"_void._.8.8VEC_Abs1.1short._.0.9._short._.0.9._int.2");
	PROFILE_FUNC(_void._.8.8VEC_AddV.1short._.0.9._short._.0.9._short._.0.9._int.2,"_void._.8.8VEC_AddV.1short._.0.9._short._.0.9._short._.0.9._int.2");
	PROFILE_FUNC(_void._.8.8VEC_SubC.1char._.0.9._int.9._char._.0.9._int.2,"_void._.8.8VEC_SubC.1char._.0.9._int.9._char._.0.9._int.2");
	PROFILE_FUNC(_void._.8.8VEC_SubV.1short._.0.9._short._.0.9._short._.0.9._int.2,"_void._.8.8VEC_SubV.1short._.0.9._short._.0.9._short._.0.9._int.2");
	PROFILE_FUNC(_void._.8.8VEC_ClipCnv_AddC.1short._.0.9._int.9._int.9._char._.0.9._int.9._unsigned._long._.0.2,"_void._.8.8VEC_ClipCnv_AddC.1short._.0.9._int.9._int.9._char._.0.9._int.9._unsigned._long._.0.2");
	PROFILE_FUNC(_CSIG_FIR.3char.9._short.4.8.8.aCSIG_FIR.1.2,"_CSIG_FIR.3char.9._short.4.8.8.aCSIG_FIR.1.2");
	PROFILE_FUNC(_void._.8.8VEC_Add2VW.1short._.0.9._short._.0.9._short._.0.9._short._.0.9._int.2,"_void._.8.8VEC_Add2VW.1short._.0.9._short._.0.9._short._.0.9._short._.0.9._int.2");
	PROFILE_FUNC(_filter3h,"_filter3h");
	PROFILE_FUNC(_filter3h,"_filter3h");
	PROFILE_FUNC(_CBaseSobel.8.8CBaseSobel.1.2,"_CBaseSobel.8.8CBaseSobel.1.2");
	PROFILE_FUNC(_CBaseSobel.8.8.aCBaseSobel.1.2,"_CBaseSobel.8.8.aCBaseSobel.1.2");
	PROFILE_FUNC(_int._CBaseSobel.8.8init.1int.9._int.2,"_int._CBaseSobel.8.8init.1int.9._int.2");
	PROFILE_FUNC(_int._CBaseSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2,"_int._CBaseSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2");
	PROFILE_FUNC(_unsigned._char._.0.8.8VEC_Addr.1unsigned._char._const._.0.9._int.2,"_unsigned._char._.0.8.8VEC_Addr.1unsigned._char._const._.0.9._int.2");
	PROFILE_FUNC(_CSIG_FIR.3char.9._short.4.8.8CSIG_FIR.1.2,"_CSIG_FIR.3char.9._short.4.8.8CSIG_FIR.1.2");
	PROFILE_FUNC(_memcpy,"_memcpy");
	PROFILE_FUNC(_memset,"_memset");
	PROFILE_NONSTD_FUNC(RShift32,"RShift32");
	PROFILE_NONSTD_FUNC(ARShift32,"ARShift32");
	PROFILE_NONSTD_FUNC(LShift32,"LShift32");
	PROFILE_NONSTD_FUNC(UMod32,"UMod32");
	PROFILE_FUNC(_void._.8.8SIG_Filter.1char._.0.9._short._.0.9._int.9._long._.0.2,"_void._.8.8SIG_Filter.1char._.0.9._short._.0.9._int.9._long._.0.2");
	PROFILE_FUNC(_int._.0.8.8VEC_Addr.1int._.0.9._int.2,"_int._.0.8.8VEC_Addr.1int._.0.9._int.2");
	PROFILE_FUNC(_void._.8.8VEC_SetVal.1short._.0.9._int.9._int.2,"_void._.8.8VEC_SetVal.1short._.0.9._int.9._int.2");
	PROFILE_FUNC(_void._.8.8VEC_Fill.1int._.0.9._int.9._int.2,"_void._.8.8VEC_Fill.1int._.0.9._int.9._int.2");
	PROFILE_FUNC(_int._CSIG_FIR.3char.9._short.4.8.8init.1int.9._void._.0.1.0.2.1unsigned._int.2.9._void._.1.0.2.1void._.0.2.2,"_int._CSIG_FIR.3char.9._short.4.8.8init.1int.9._void._.0.1.0.2.1unsigned._int.2.9._void._.1.0.2.1void._.0.2.2");
	PROFILE_FUNC(_int._.8.8SIG_SetFilter_8s16s.1int._.0.9._int.9._long._.0.2,"_int._.8.8SIG_SetFilter_8s16s.1int._.0.9._int.9._long._.0.2");
	PROFILE_FUNC(_void._.8.8VEC_SetVal.1int._.0.9._int.9._int.2,"_void._.8.8VEC_SetVal.1int._.0.9._int.9._int.2");
	PROFILE_FUNC(_int._.8.8GetDisp0.1int.2,"_int._.8.8GetDisp0.1int.2");
	PROFILE_FUNC(_int._.8.8GetDisp1.1int.2,"_int._.8.8GetDisp1.1int.2");
	PROFILE_FUNC(_memmove,"_memmove");

PROFILE_END();

