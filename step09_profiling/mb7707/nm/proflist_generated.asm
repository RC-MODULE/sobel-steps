//****************************************************************************************
// This is automaticly generated asm-file by generate_proflist.bat (generate_proflist.tcl 
// Use this script to parse map-file to extract functions from abs-file 
// and to generate initial asm-template for profiling.
// It is recommended to remove  all unnecessary functions to make profiling more precise.
//****************************************************************************************
import from profiler.mlb;

PROFILE_BEGIN(16);

	PROFILE_FUNC(_CSobel.8.8CSobel.1int.9._int.2, "_CSobel.8.8CSobel.1int.9._int.2");
	PROFILE_FUNC(_CSobel.8.8.aCSobel.1.2, "_CSobel.8.8.aCSobel.1.2");
	PROFILE_FUNC(_int._CSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2, "_int._CSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2");
	PROFILE_FUNC(__main, "__main");
	PROFILE_FUNC(_nmppsConvert_16s8s, "_nmppsConvert_16s8s");
	PROFILE_FUNC(_nmppsMalloc_16s, "_nmppsMalloc_16s");
	PROFILE_FUNC(_nmppsMallocFrame_8s, "_nmppsMallocFrame_8s");
	PROFILE_FUNC(_nmppsMallocFrame_16s, "_nmppsMallocFrame_16s");
	PROFILE_FUNC(_nmppsFreeFrame, "_nmppsFreeFrame");
	PROFILE_FUNC(_nmppsMallocSuccess, "_nmppsMallocSuccess");
	PROFILE_FUNC(_nmppsFree, "_nmppsFree");
	PROFILE_FUNC(_nmppsAbs_16s, "_nmppsAbs_16s");
	PROFILE_FUNC(_nmppsAdd_16s, "_nmppsAdd_16s");
	PROFILE_FUNC(_nmppsAdd4V_16s, "_nmppsAdd4V_16s");
	PROFILE_FUNC(_nmppsSubC_8s, "_nmppsSubC_8s");
	PROFILE_FUNC(_nmppsSub_16s, "_nmppsSub_16s");
	PROFILE_FUNC(_nmppsClipPowC_16s, "_nmppsClipPowC_16s");
	PROFILE_FUNC(_nmppsFIR_8s16s, "_nmppsFIR_8s16s");
	PROFILE_FUNC(_nmppsFIRInitAlloc_8s16s, "_nmppsFIRInitAlloc_8s16s");
	PROFILE_FUNC(_nmppsFIRFree, "_nmppsFIRFree");
	PROFILE_NONSTD_FUNC(Mul32, "Mul32");
	PROFILE_NONSTD_FUNC(IDiv32, "IDiv32");
	PROFILE_FUNC(_CBaseSobel.8.8CBaseSobel.1.2, "_CBaseSobel.8.8CBaseSobel.1.2");
	PROFILE_FUNC(_CBaseSobel.8.8.aCBaseSobel.1.2, "_CBaseSobel.8.8.aCBaseSobel.1.2");
	PROFILE_FUNC(_int._CBaseSobel.8.8init.1int.9._int.2, "_int._CBaseSobel.8.8init.1int.9._int.2");
	PROFILE_FUNC(_int._CBaseSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2, "_int._CBaseSobel.8.8filter.1unsigned._char._const._.0.9._unsigned._char._.0.2");
	PROFILE_FUNC(_malloc0, "_malloc0");
	PROFILE_FUNC(_malloc1, "_malloc1");
	PROFILE_FUNC(_malloc2, "_malloc2");
	PROFILE_FUNC(_malloc3, "_malloc3");
	PROFILE_FUNC(_free, "_free");
	PROFILE_FUNC(_nmppsPut_4s, "_nmppsPut_4s");
	PROFILE_FUNC(_nmppsGet_4u, "_nmppsGet_4u");
	PROFILE_FUNC(_nmppsSet_64sp, "_nmppsSet_64sp");
	PROFILE_FUNC(_nmppsRandUniform_64s, "_nmppsRandUniform_64s");
	PROFILE_FUNC(_nmppsCopy_64s, "_nmppsCopy_64s");
	PROFILE_FUNC(_nmppsAndC_32u, "_nmppsAndC_32u");
	PROFILE_FUNC(_nmppsMalloc32, "_nmppsMalloc32");
	PROFILE_FUNC(_nmppsMallocTimerResume, "_nmppsMallocTimerResume");
	PROFILE_FUNC(_nmppsMallocTimerStop, "_nmppsMallocTimerStop");
	PROFILE_FUNC(_nmppsMallocSetRouteMode, "_nmppsMallocSetRouteMode");
	PROFILE_FUNC(_nmppsMallocResetPos, "_nmppsMallocResetPos");
	PROFILE_FUNC(_nmppsMalloc_32s, "_nmppsMalloc_32s");
	PROFILE_FUNC(_nmppsPut_16s, "_nmppsPut_16s");
	PROFILE_FUNC(_nmppsSet_32s, "_nmppsSet_32s");
	PROFILE_FUNC(_nmppsFIRInit_8s16s, "_nmppsFIRInit_8s16s");
	PROFILE_FUNC(_nmppsFIRGetStateSize_8s16s, "_nmppsFIRGetStateSize_8s16s");
	PROFILE_NONSTD_FUNC(LShift32, "LShift32");
	PROFILE_NONSTD_FUNC(ARShift32, "ARShift32");
	PROFILE_NONSTD_FUNC(UMod32, "UMod32");
	PROFILE_FUNC(_memcpy, "_memcpy");
	PROFILE_FUNC(_memset, "_memset");
	PROFILE_NONSTD_FUNC(RShift32, "RShift32");
	PROFILE_FUNC(_malloc, "_malloc");
	PROFILE_FUNC(_memmove, "_memmove");
PROFILE_END();
