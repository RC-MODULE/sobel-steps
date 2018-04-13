#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"
#include "sobel.h"
#pragma code_section ".text_sobel"

extern "C" {
	void add2VW (nm16s *pSrcVec0,nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize) ;
	extern long long sobel_weights121[];
	extern long long sobel_weights101[];

	void filter3h ( const nm8s *source, nm16s *result, int size, void* weights);
}
// here was: int sobelH[3]={
//		1,2,1
//		0, 0,0,
//		-1,-2,-1
//};

// here was: int sobelV[3]={
//		1,0,-1
//		2, 0,-2,
//		1,0,-1
//};

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
	nmppsFree(pClipConvertState);
}


int CBaseSobel::init(int Width, int Height ){
	width	=Width;
	height	=Height;
	size	=width*height;
	frameSize=size+2*width;
	isReady	=false;	

	signedImg			= nmppsMallocFrame_8s(size,width,&signedFrame);
	signedImgUpLine	 	= nmppsAddr_8s(signedImg,-width);
		
	horizontTmp		 	= nmppsMallocFrame_16s(size, width, &horizontTmpFrame); 
	horizontTmpUpLine	= nmppsAddr_16s(horizontTmp,-width); 
	horizontTmpDnLine	= nmppsAddr_16s(horizontTmp,+width);

	horizontOut			= nmppsMalloc_16s(size);	// Allocate temporary buffer 
	verticalOut			= nmppsMalloc_16s(size);	// Allocate temporary buffer
	
	nmppsClipConvertAddCInitAlloc_16s8s(&pClipConvertState);


	// here was: FIR121.init(3,malloc32,free32);
	// here was: FIR101.init(3,malloc32,free32);



	// here was: if (FIR121.setWeights(sobelH)==0)
	// here was: 	return false;

	// here was: if (FIR101.setWeights(sobelV)==0)
	// here was: 	return false;

	isReady=nmppsMallocSuccess();
	return isReady;

}
	
	
int CBaseSobel::filter( const nm8u *source, nm8u *result)
{
	nm8s* sourceUpLine=nmppsAddr_8s((nm8s*)source,-width);
	nmppsSubC_8s(sourceUpLine, 128, signedImgUpLine, frameSize);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	// here was: nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState121);
	filter3h ( signedImgUpLine, horizontTmpUpLine, frameSize, sobel_weights121);

	nmppsSub_16s(horizontTmpUpLine, horizontTmpDnLine, horizontOut, size);

	// vertical edge selection 
	// here was: nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState101);
	filter3h(signedImgUpLine, horizontTmpUpLine, frameSize, sobel_weights101);

	add2VW (horizontTmp, horizontTmpUpLine,horizontTmpDnLine,verticalOut, size);
	
	nmppsAbs1_16s(horizontOut, horizontOut,size);	// Calculate absolute value 
	nmppsAbs1_16s(verticalOut, verticalOut,size);	// Calculate absolute value 

	nmppsAdd_16s(horizontOut,verticalOut,verticalOut,size);		// Add 

	nmppsClipConvertAddC_16s8s((nm16s*)verticalOut,8,0,(nm8s*)result, size, pClipConvertState);
	
	return true;
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
