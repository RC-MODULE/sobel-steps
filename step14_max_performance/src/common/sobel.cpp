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

CBaseSobel::CBaseSobel(){
	isReady=false;
}

CBaseSobel::CBaseSobel(int Width, int Height){
	init(Width, Height);
}

CBaseSobel::~CBaseSobel(){
	if (pool1) 	free32(pool1);
	if (pool2)  free32(pool2);
	if (pool3) 	free32(pool3);
}

int CBaseSobel::init(int Width, int Height ){
	width	=Width;
	height	=Height;
	size	=width*height;
	frameSize=size+2*width;
	isReady	=false;	

	pool1= malloc32(frameSize/2, HEAP_1);
	pool2= malloc32(frameSize/2, HEAP_2);
	pool3= malloc32(frameSize/2, HEAP_3);

	signedImgUpLine	 = (nm8s*)pool1;
	signedImg		 = nmppsAddr_8s(signedImgUpLine,+width);
	
	horizontTmpUpLine= (nm16s*)pool2; 
	horizontTmp		 = nmppsAddr_16s(horizontTmpUpLine, width); 
	
	verticalTmpUpLine= (nm16s*)pool3; 
	verticalTmp		 = nmppsAddr_16s(verticalTmpUpLine, width); 
	
	horizontOut		 = (nm16s*)pool3;
	verticalOut		 = (nm16s*)pool1;
	horizontAbs      = (nm16s*)pool2;
	verticalAbs      = (nm16s*)pool3;
	summ			 = (nm16s*)pool1;

	isReady= (pool1!=0) && (pool2!=0) && (pool3!=0);
		
	if (!isReady){
		if (pool1)	free32(pool1); pool1=0;
		if (pool2)	free32(pool2); pool2=0;
		if (pool3)	free32(pool3); pool3=0;
	}

	return isReady;
}

	
int CBaseSobel::filter( const unsigned char *source, unsigned char *result, int customHeight)
{
	int height  ;
	int frameSize;
	int size;
	if (customHeight){
		frameSize= customHeight*width;
		size    = frameSize;
		height  = customHeight;
	} 
	else {
		frameSize= CBaseSobel::frameSize;
		size    = CBaseSobel::size;
		height  = CBaseSobel::height;
	}
	
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

CSobel::CSobel(){
	
}

CSobel::~CSobel(){

}

CSobel::CSobel (int Width, int Height){
	init(Width, Height);
}

int CSobel::init (int Width, int Height){
	fullHeight=Height;
	// try to find maximum slice height to fit in internal memory
	for(int sliceHeight=(Height+29)/30*30; sliceHeight>=30; sliceHeight-=30){
		if (CBaseSobel::init(Width, sliceHeight))
			break;
	}
	return isReady;
}

int CSobel::filter ( const unsigned char *source, unsigned char *result){
	int residualHeight=fullHeight;
	while (residualHeight>height){
		CBaseSobel::filter(source, result);
		source = nmppsAddr_8u(source, size);
		result = nmppsAddr_8u(result, size);
		residualHeight-=height;
	}
	if (residualHeight>0){
		CBaseSobel::filter(source, result, residualHeight);
	}
	
	return true;

}
