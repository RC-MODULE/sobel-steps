//------------------------------------------------------------------------
//
//  $Workfile:: Math_Add.as $
//
//  ��������-��������� ����������
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:05 $
//
//! \if file_doc
//!
//! \file   Math_Add.asm
//! \author ������ �������
//! \brief  ������� ���������� ����.
//!
//! \endif
//!
//------------------------------------------------------------------------


begin ".text_nmvcore"


macro VEC_ADD_REP(N)
	delayed return;
		rep N data = [ar1++gr1] with activate data xor data;
		rep N data = [ar0++gr0] with data + afifo;
		rep N [ar6++gr6] = afifo;
end   VEC_ADD_REP;

Add_rep0:label;

    //------------------------------------------------------------------------
    //! \fn void vec_Add(nmreg nb1, nmreg ar0, nmreg gr0, nmreg ar1, nmreg gr1, nmreg gr5, nmreg ar6, nmreg gr6)
    //!
    //------------------------------------------------------------------------

global vec_AddAbs1V :label;
<vec_AddAbs1V>
.branch;
	push ar2,gr2 with gr2=gr5<<27 ;
	push ar5,gr5 with gr5>>=5;	
	if =0 delayed goto Add_repN with gr2>>=25;
		ar2 = Add_rep0 with gr5--;
	push ar3,gr3;
	next_Add_rep32: label;
	ar3= next_Add_rep32;
	<next_Add_rep32>
	if <>0 delayed goto ar3 with gr5--;	
		rep 32 data = [ar1++gr1] with activate data xor data;
		rep 32 data = [ar0++gr0] with data + afifo;
		rep 32 [ar6++gr6] = afifo;
	<Add_repN>
	ar2+=gr2;
	pop ar3,gr3;
	delayed goto ar2; 
		pop ar5,gr5;
		pop ar2,gr2;
	<Add_rep0>
	delayed return;
		nul;
		nul;
		nul;
	VEC_ADD_REP(1);
	VEC_ADD_REP(2);
	VEC_ADD_REP(3);
	VEC_ADD_REP(4);
	VEC_ADD_REP(5);
	VEC_ADD_REP(6);
	VEC_ADD_REP(7);
	VEC_ADD_REP(8);
	VEC_ADD_REP(9);
	VEC_ADD_REP(10);
	VEC_ADD_REP(11);
	VEC_ADD_REP(12);
	VEC_ADD_REP(13);
	VEC_ADD_REP(14);
	VEC_ADD_REP(15);
	VEC_ADD_REP(16);
	VEC_ADD_REP(17);
	VEC_ADD_REP(18);
	VEC_ADD_REP(19);
	VEC_ADD_REP(20);
	VEC_ADD_REP(21);
	VEC_ADD_REP(22);
	VEC_ADD_REP(23);
	VEC_ADD_REP(24);
	VEC_ADD_REP(25);
	VEC_ADD_REP(26);
	VEC_ADD_REP(27);
	VEC_ADD_REP(28);
	VEC_ADD_REP(29);
	VEC_ADD_REP(30);
	VEC_ADD_REP(31);
return;
.wait;




end ".text_nmvcore";
