//------------------------------------------------------------------------
//
//  $Workfile:: MultipleAdd16.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   MultipleAdd16.Asm
//! \author Сергей Мушкаев
//! \brief  Функции умножения с накоплением для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------
//#include "vArithm.h"


data ".data_nmplv_G"
	 VEC_TBL_Diagonal_2:	long[4] = (
		0000_0000_0000_0002hl,
		0000_0000_0002_0000hl,
		0000_0002_0000_0000hl,
		0002_0000_0000_0000hl);	
end ".data_nmplv_G";

extern vec_vsum_data_add2V:label;
begin ".text_nmplv"



/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_Add2VW (nm16s *pSrcVec0,nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize) 
//!

global _void._.8.8VEC_Add2VW.1short._.0.9._short._.0.9._short._.0.9._short._.0.9._int.2 :label;
<_void._.8.8VEC_Add2VW.1short._.0.9._short._.0.9._short._.0.9._short._.0.9._int.2>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0;
	push ar1,gr1;
	push ar2,gr2;
	push ar5,gr5;
	push ar6,gr6;
	
	nb1 = 80008000h;
	sb  = 00020002h;
	ar6 = VEC_TBL_Diagonal_2 with gr0 = gr0-gr0;
	rep 4 wfifo = [ar6++],ftw,wtw;
	
	ar0 = [--ar5] with gr0++;
	ar1 = [--ar5] with gr0++;
	ar2 = [--ar5] with gr1 = gr0;
	ar6 = [--ar5] with gr2 = gr0;	// DstBuffer
	gr5 = [--ar5] with gr6 = gr0;	// Size Of Buffers
	
	call vec_vsum_data_add2V with gr5>>=2;	// nSize in 64-bit longs
	
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
	return ;
.wait;
end ".text_nmplv";
 


