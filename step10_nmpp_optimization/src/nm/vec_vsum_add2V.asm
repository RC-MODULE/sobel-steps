//------------------------------------------------------------------------
//
//  $Workfile:: vsum_data_0.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:07 $
//
//! \if file_doc
//!
//! \file   vsum_data_0.asm
//! \author ������ �������
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------

begin ".text_nmvcore"


    

macro VEC_MUL_VN_REP(N)
		rep N data = [ar1++gr1] with afifo + data;
		rep N data = [ar2++gr2] with afifo + data;
	delayed return;	
		rep N data = [ar0++gr0] with vsum ,data,0;
		rep N [ar6++gr6] = afifo;
		nul;
	nul;
	nul;
end VEC_MUL_VN_REP;

MulVN_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_vsum_data_add2V(nmreg nb1, nmreg sb, nmreg woper, nmreg ar0, nmreg gr0,nmreg ar1, nmreg gr1,nmreg ar2, nmreg gr2, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_vsum_data_add2V:label;
<vec_vsum_data_add2V>
.branch;
	push ar3,gr3 with gr3=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto MulVN_repN with gr3>>=24;
		ar3 = MulVN_rep0 with gr5--;
	
	<next_MulVN_rep32>
		rep 32 data = [ar0++gr0] with vsum ,data,0;
		rep 32 data = [ar1++gr1] with afifo + data;
	if <>0 delayed goto next_MulVN_rep32 with gr5--;
		rep 32 data = [ar2++gr2] with afifo + data;
		rep 32 [ar6++gr6] = afifo; 
	<MulVN_repN>
	ar3+=gr3;
	delayed goto ar3; 
		pop ar5,gr5;
		pop ar3,gr3;
	<MulVN_rep0>
	delayed return;
		nul;
		nul;
		nul;
	nul;nul;nul;nul;
	VEC_MUL_VN_REP(1);
	VEC_MUL_VN_REP(2);
	VEC_MUL_VN_REP(3);
	VEC_MUL_VN_REP(4);
	VEC_MUL_VN_REP(5);
	VEC_MUL_VN_REP(6);
	VEC_MUL_VN_REP(7);
	VEC_MUL_VN_REP(8);
	VEC_MUL_VN_REP(9);
	VEC_MUL_VN_REP(10);
	VEC_MUL_VN_REP(11);
	VEC_MUL_VN_REP(12);
	VEC_MUL_VN_REP(13);
	VEC_MUL_VN_REP(14);
	VEC_MUL_VN_REP(15);
	VEC_MUL_VN_REP(16);
	VEC_MUL_VN_REP(17);
	VEC_MUL_VN_REP(18);
	VEC_MUL_VN_REP(19);
	VEC_MUL_VN_REP(20);
	VEC_MUL_VN_REP(21);
	VEC_MUL_VN_REP(22);
	VEC_MUL_VN_REP(23);
	VEC_MUL_VN_REP(24);
	VEC_MUL_VN_REP(25);
	VEC_MUL_VN_REP(26);
	VEC_MUL_VN_REP(27);
	VEC_MUL_VN_REP(28);
	VEC_MUL_VN_REP(29);
	VEC_MUL_VN_REP(30);
	VEC_MUL_VN_REP(31);
return;
.wait;




end ".text_nmvcore";
