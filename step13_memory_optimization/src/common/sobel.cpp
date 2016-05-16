#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"
#include "sobel.h"
#pragma code_section ".text_sobel"

extern "C" {

	extern long long sobel_weights121[24];
	extern long long sobel_weights101[24];
	extern long long sobel_weights101v[30];
	extern long long sobel_weights121v[30];

	void filter3h( const nm8s *source,  nm16s *result, int size, void* weights);
	void filter3v( const nm16s *source, nm16s *result, int width, int height, void* weights);
};

//CBaseSobel::CBaseSobel(){
//	isReady=false;
//}

//CBaseSobel::CBaseSobel(int Width, int Height){
//	init(Width, Height);
//}

void Sobel::free(){
//	nmppsFree(pool1);
//	nmppsFree(pool2);
//	nmppsFree(pool3);
//	nmppsFree(pClipConvertState);
}

int Sobel::initAlloc(int Width, int Height){
	width	=Width;
	height	=Height;
	size	=width*height;
	frameSize=size+2*width;
	isReady	=false;	

	pool1= nmppsMalloc_16s(frameSize);
	pool2= nmppsMalloc_16s(frameSize);
	pool3= nmppsMalloc_16s(frameSize);

	signedImgUpLine	 = (nm8s*)pool1;
	signedImg		 = nmppsAddr_8s(signedImgUpLine,+width);
	
	horizontTmpUpLine= (nm16s*)pool2; 
	horizontTmp		 = nmppsAddr_16s(horizontTmpUpLine, width); 
	
	verticalTmpUpLine= (nm16s*)pool3; 
	verticalTmp		 = nmppsAddr_16s(verticalTmpUpLine, width); 
	nmppsClipConvertAddCInitAlloc_16s8s(&pClipConvertState);

	
	horizontOut		 = (nm16s*)pool3;
	verticalOut		 = (nm16s*)pool1;
	horizontAbs      = (nm16s*)pool2;
	verticalAbs      = (nm16s*)pool3;
	summ			 = (nm16s*)pool1;

	if (nmppsMallocSuccess())
		return 0;
	else {
		free();
		return -1;
	}
	return 0;
}
int Sobel::filterFinal( const unsigned char *source, unsigned char *result, int finalHeight)
{
	int originFrameSize= frameSize;
	int originSize     = size;
	int originHeight   = height;

	frameSize= finalHeight*width;
	size     = frameSize;
	height   = finalHeight;

	int ret=filter( source, result);

	frameSize= originFrameSize;
	size     = originSize;
	height   = originHeight;
	
	return ret;
}
	
int Sobel::filter( const unsigned char *source, unsigned char *result)
{
	nm8s* sourceUpLine=nmppsAddr_8s((nm8s*)source,-width);
	nmppsSubC_8s(sourceUpLine, 128, signedImgUpLine, frameSize);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	filter3h( signedImgUpLine, horizontTmpUpLine, frameSize, sobel_weights121);
	filter3v(horizontTmpUpLine, horizontOut,  width, height, sobel_weights101v);
	nmppsAbs_16s(horizontOut, horizontAbs,size);	// Calculate absolute value 

	// vertical edge selection 
	filter3h(signedImgUpLine, verticalTmpUpLine, frameSize, sobel_weights101);
	filter3v((nm16s*)verticalTmpUpLine, verticalOut, width, height, sobel_weights121v);
	nmppsAbs1_16s(verticalOut, verticalAbs,size);	// Calculate absolute value 

	// summ
	nmppsAdd_16s(horizontAbs, verticalAbs,(nm16s*)summ,size);		// Add 
	nmppsClipConvertAddC_16s8s((nm16s*)summ,8,0,(nm8s*)result, size, pClipConvertState);
	
	
	return true;
}
/*
CSobel::CSobel(){
	
}

CSobel::~CSobel(){

}

Sobel::Sobel (int Width, int Height){
	init(Width, Height);
}
*/

int SobelCuts::initAlloc (int Width, int Height, int sliceHeight){
	fullHeight=Height;
	// try to find maximum slice height to fit in internal memory
	if (sliceHeight==0){
		for(int sliceHeight=(Height+29)/30*30; sliceHeight>=30; sliceHeight-=30){
			if (Sobel::initAlloc(Width, sliceHeight)==0)
				return 0;
		}
	}
	else 
		return Sobel::initAlloc(Width, sliceHeight);
	return -1;
}

int SobelCuts::filter ( const unsigned char *source, unsigned char *result)
{
	int residualHeight=fullHeight-2;
	source=nmppsAddr_8u(source,width);
	result=nmppsAddr_8u(result,width);
	while (residualHeight>height){
		Sobel::filter(source, result);
		source = nmppsAddr_8u(source, size);
		result = nmppsAddr_8u(result, size);
		residualHeight-=height;
	}
	if (residualHeight>0){
		Sobel::filterFinal(source, result, residualHeight);
	}
	
	return true;

}
