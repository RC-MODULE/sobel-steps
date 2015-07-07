//------------------------------------------------------------------------
//
//  $Workfile:: Add.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:03 $
//
//! \if file_doc
//!
//! \file   Add.Asm
//! \author ������ �������
//! \brief  ������� ������������ ��� ��������.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vArithm.h"



extern vec_AddAbs1V:label;

begin ".text_nmplv"


/////////////////////////////////////////////////////////////////////////////////////////
//! \fn void VEC_AddAbs1V (nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize) 

global _void._.8.8VEC_AddAbs1V.1short._.0.9._short._.0.9._short._.0.9._int.2 :label;
<_void._.8.8VEC_AddAbs1V.1short._.0.9._short._.0.9._short._.0.9._int.2>
.branch;
	ar5 = sp - 2;
	
	push ar0,gr0 with gr0=false;
	push ar1,gr1 with gr0++;
	push ar5,gr5 with gr0++;		// gr0=2 
	push ar6,gr6 with gr1=gr0;
	ar0 = [--ar5];	// pSrcVec2 
	ar1 = [--ar5];	// pSrcVec1 - for abs1
	ar6 = [--ar5];	// pDstVec
	gr5 = [--ar5];	// nSize in 16-bit elements
	
	nb1 = 80008000h with gr5>>=2;	// nSize in 64-bit words
	f1cr= 80008000h;  
	delayed call vec_AddAbs1V with gr1=gr0;
		wtw;						
		gr6=gr0;					// gr6=2
	pop ar6,gr6;
	pop ar5,gr5;
	pop ar1,gr1;
	pop ar0,gr0;
return with gr7=false;
.wait;



end ".text_nmplv";
