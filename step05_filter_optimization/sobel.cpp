#include "nmpli.h"
#include "nmpp.h"		


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

int sobel( const nm8u *source, nm8u *result, int width,int height)
{
	int size=width*height;
	NmppsFrame_16s frame;
	nmppsMallocFrame_16s(size,width,&frame);
	
	nm16s* horizontTmp= frame.data;
	nm16s* horizontOut= (nm16s*)nmppsMalloc_16s(size);	// Allocate temporary buffer 
	nm16s* verticalOut= (nm16s*)nmppsMalloc_16s(size);	// Allocate temporary buffer
	
	NmppsFIRState* pFIRState121;
	NmppsFIRState* pFIRState101;
	nmppsFIRInitAlloc_8s16s(&pFIRState121,sobelH,3);
	nmppsFIRInitAlloc_8s16s(&pFIRState101,sobelV,3);
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
	nmppsFreeFrame(&frame);
	nmppsFree(horizontOut);
	nmppsFree(verticalOut);
	nmppsFIRFree(pFIRState121);
	nmppsFIRFree(pFIRState101);
	
	return !nmppsMallocSuccess();
}