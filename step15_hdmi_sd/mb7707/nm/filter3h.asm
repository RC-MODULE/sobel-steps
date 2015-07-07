//**********s********************************************************************
//    RC Module
//    NeuroMatrix(r) NM6406 Software
//
//    Image Processing Library 
//    (C-callable functions)
//
//    Software design:    S.Mushkaev
//    
//
//
//********************************************************************************


data ".data_sobel_weights121"
    global _sobel_weights121: long[24] = (	
							0000_0000_0000_0001hl, 
							0000_0000_0001_0002hl, 
							0000_0001_0002_0001hl,
							0001_0002_0001_0000hl,
							0002_0001_0000_0000hl, 
							0001_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							    
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0001hl, 
							0000_0000_0001_0002hl,
							0000_0001_0002_0001hl, 
							0001_0002_0001_0000hl,
							    
				   			0002_0001_0000_0000hl, 
							0001_0000_0000_0000hl, 
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl,
							0000_0000_0000_0000hl
							);
end ".data_sobel_weights121";	

data ".data_sobel_weights101"
	global _sobel_weights101: long[24] = (	
							00000_0000_0000_0001hl, 
							00000_0000_0001_0000hl, 
							00000_0001_0000_ffffhl,
							00001_0000_ffff_0000hl, 
							00000_ffff_0000_0000hl, 
							0ffff_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,

							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0001hl, 
							00000_0000_0001_0000hl,
							00000_0001_0000_ffffhl, 
							00001_0000_ffff_0000hl,

							00000_ffff_0000_0000hl, 
							0ffff_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl,
							00000_0000_0000_0000hl
							);
end ".data_sobel_weights101";

begin ".text_sobel"

macro FILTER_REP(N)
	rep 24 wfifo = [ar3++], ftw,wtw;
	rep N  ram   = [ar0++], ftw,wtw with vsum , data, 0;
	delayed goto ar2;	
		rep N [ar4++gr4]=afifo,ftw,wtw with vsum , ram,  0;
		rep N data = [ar1++] with vsum , data, afifo;
		rep N [ar5++gr5] = afifo;
	nul;
	nul;
end FILTER_REP;

global _filter3h: label;
<_filter3h>

.branch;
    ar5 = ar7 - 2;
	
	push ar0,gr0 with gr0 = false;  
	push ar1,gr1 with gr0++;  			
	push ar2,gr2 with gr0++;  			// gr0 = 2;
	push ar3,gr3;
	push ar4,gr4;
	push ar5,gr5;
	
    sb  = 02020202h;
	nb1 = 80008000h;
	
    ar0 = [--ar5];						// source buffer;
    ar4 = [--ar5] with gr4 = gr0; 		// result buffer
    gr7 = [--ar5] with gr5 = gr4<<1;	// gr7=size , gr5 = 4
	gr3 = [--ar5] with gr2 = gr7<<24;	// prepare for %(32*8)
     				
    ar1 = ar0 + gr0	with gr7 >>= 8;		// weights  , gr7 =(size/8)/32  
    ar5 = ar4 + gr4 with gr4 = gr5;		// gr4 = 3
    ar3 = gr3 with gr7--;
	<Next32>
		rep 24 wfifo = [ar3++], ftw,wtw;
		rep 32 ram   = [ar0++], ftw,wtw with vsum , data, 0;
		rep 32 [ar4++gr4]=afifo,ftw,wtw with vsum , ram,  0;
		ar3 = gr3;
    if > delayed goto Next32 with gr7--;
		rep 32 data = [ar1++] with vsum , data, afifo;
		rep 32 [ar5++gr5] = afifo;
    
	Filter_end :label;
	Filter_rep0:label;
	<Filter_repN>
	ar2 = Filter_rep0 with gr2>>=24;
	ar2+= gr2;
	delayed goto ar2; 
		ar2 = Filter_end;
	<Filter_rep0>
	delayed goto ar2;
		nul;
		nul;
		nul;
	nul;nul;nul;nul;
	FILTER_REP(1);
	FILTER_REP(2);
	FILTER_REP(3);
	FILTER_REP(4);
	FILTER_REP(5);
	FILTER_REP(6);
	FILTER_REP(7);
	FILTER_REP(8);
	FILTER_REP(9);
	FILTER_REP(10);
	FILTER_REP(11);
	FILTER_REP(12);
	FILTER_REP(13);
	FILTER_REP(14);
	FILTER_REP(15);
	FILTER_REP(16);
	FILTER_REP(17);
	FILTER_REP(18);
	FILTER_REP(19);
	FILTER_REP(20);
	FILTER_REP(21);
	FILTER_REP(22);
	FILTER_REP(23);
	FILTER_REP(24);
	FILTER_REP(25);
	FILTER_REP(26);
	FILTER_REP(27);
	FILTER_REP(28);
	FILTER_REP(29);
	FILTER_REP(30);
	FILTER_REP(31);
	<Filter_end>
    pop ar5,gr5;
	pop ar4,gr4;
	pop ar3,gr3;
	pop ar2,gr2;
	pop ar1,gr1;
	pop ar0,gr0;
	
    return;
end ".text_sobel";
