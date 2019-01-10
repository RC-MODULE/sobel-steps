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
	nmppsFreeFrame(&signedFrame);
	nmppsFreeFrame(&horizontTmpFrame);
	nmppsFree(horizontOut);
	nmppsFree(verticalOut);
	nmppsFIRFree(pFIRState121);
	nmppsFIRFree(pFIRState101);
}


int CBaseSobel::init(int Width, int Height ){
	width	=Width;
	height	=Height;
	size	=width*height;
	isReady	=false;	

	signedImg			= nmppsMallocFrame_8s(size,width,&signedFrame);
	horizontTmp		 	= nmppsMallocFrame_16s(size, width, &horizontTmpFrame); 
	horizontTmpUpLine	= nmppsAddr_16s(horizontTmp,-width); 
	horizontTmpDnLine	= nmppsAddr_16s(horizontTmp,+width);

	horizontOut			= nmppsMalloc_16s(size);	// Allocate temporary buffer 
	verticalOut			= nmppsMalloc_16s(size);	// Allocate temporary buffer
	
	nmppsFIRInitAlloc_8s16s(&pFIRState121,sobelH,3);
	nmppsFIRInitAlloc_8s16s(&pFIRState101,sobelV,3);

	isReady=nmppsMallocSuccess();
	return isReady;

}
	

	
int CBaseSobel::filter( const nm8u *source, nm8u *result)
{
	nmppsSubC_8s((nm8s*)source,128,signedImg,size);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	nmppsFIR_8s16s(signedImg, horizontTmp, size, pFIRState121);
	nmppsSub_16s(horizontTmpUpLine, horizontTmpDnLine, horizontOut, size);
	
	// vertical edge selection 
	nmppsFIR_8s16s(signedImg, horizontTmp, size, pFIRState101);
	nm16s* lines[4]={	horizontTmpUpLine,
						horizontTmp,
						horizontTmp,
						horizontTmpDnLine};
	nmppsAdd4V_16s(lines, verticalOut, size); 

	nmppsAbs_16s(horizontOut, horizontOut,size);	// Calculate absolute value 
	nmppsAbs_16s(verticalOut, verticalOut,size);	// Calculate absolute value 

	nmppsAdd_16s(horizontOut,verticalOut,verticalOut,size);		// Add 

	nmppsClipPowC_16s(verticalOut,8,verticalOut,size);	// Thresh function to leave pixels in 0..255 range

	nmppsConvert_16s8s(verticalOut, (nm8s*)result, size);				// Convert from 16-bit packed data to 8-bit packed data

	
	return 0;
}

CSobel::CSobel(){
	
}
CSobel::~CSobel(){

}

CSobel::CSobel (int Width, int Height){
	init(Width, Height);
}

int CSobel::init (int Width, int Height){
	int sliceHeight=72;
	sliceCount =Height/sliceHeight;
	CBaseSobel::init(Width, sliceHeight);
	return isReady;
}

int CSobel::filter ( const nm8u *source, nm8u *result){
	
	for(int slice=0; slice<sliceCount; slice++){
		nm8u* sliceSrcImg8= nmppsAddr_8u(source,slice*size);
		nm8u* sliceDstImg8= nmppsAddr_8u(result,slice*size);
		CBaseSobel::filter(sliceSrcImg8, sliceDstImg8);
	}
	return true;

}
