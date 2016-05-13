#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"
#include "sobel.h"
#pragma code_section ".text_sobel"

int sobelH[3]={
		1,2,1
//		0, 0,0,
//		-1,-2,-1
};

int sobelV[3]={
		1,0,-1
//		2, 0,-2,
//		1,0,-1
};

CBaseSobel::CBaseSobel(){
	isReady=false;
}

CBaseSobel::CBaseSobel(int Width, int Height){
	init(Width, Height);
}

CBaseSobel::~CBaseSobel(){
	nmppsFreeFrame(&frame);
	nmppsFree(horizontOut);
	nmppsFree(verticalOut);
	nmppsFIRFree(pFIRState121);
	nmppsFIRFree(pFIRState101);
}

int CBaseSobel::init(int Width, int Height){
	width	=Width;
	height	=Height;
	size	=width*height;
	horizontTmp= nmppsMallocFrame_16s(size,width,&frame);
	horizontOut= nmppsMalloc_16s(size);	// Allocate temporary buffer 
	verticalOut= nmppsMalloc_16s(size);	// Allocate temporary buffer
	
	nmppsFIRInitAlloc_8s16s(&pFIRState121,sobelH,3);
	nmppsFIRInitAlloc_8s16s(&pFIRState101,sobelV,3);
	//isReady=true;
	return true;

}
	

	
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
	if (nmppsMallocSuccess()){
		
		nmppsSubC_8s((nm8s*)source,128,(nm8s*)result,size);	// Transform dynamic range 0..255 to -128..+127
		
		// horizontal edge selection 
		nmppsFIR_8s16s((nm8s*)result, horizontTmp, size, pFIRState121);
		nmppsSub_16s(nmppsAddr_16s(horizontTmp,-width), nmppsAddr_16s(horizontTmp,width), horizontOut, size);
		
		// vertical edge selection 
		nmppsFIR_8s16s((nm8s*)result, horizontTmp, size, pFIRState101);
		nm16s* lines[4]={nmppsAddr_16s(	horizontTmp,-width),
										horizontTmp,
										horizontTmp,
						nmppsAddr_16s(	horizontTmp,width)};
		nmppsAdd4V_16s(lines, verticalOut, size); 

		nmppsAbs_16s(horizontOut, horizontOut,size);	// Calculate absolute value 
		nmppsAbs_16s(verticalOut, verticalOut,size);	// Calculate absolute value 

		nmppsAdd_16s(horizontOut,verticalOut,verticalOut,size);		// Add 

		nmppsClipPowC_16s(verticalOut,8,verticalOut,size);	// Thresh function to leave pixels in 0..255 range

		nmppsConvert_16s8s(verticalOut, (nm8s*)result, size);				// Convert from 16-bit packed data to 8-bit packed data
		
	}

	return nmppsMallocSuccess();
	
}
