#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"
#include "sobel.h"

void VEC_Add2VW (nm16s *pSrcVec0,nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize) ;

extern "C" {

	extern long long sobel_weights121[];
	extern long long sobel_weights101[];

	void filter3h ( const char *source, short *result, int size, void* weights);
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
	free32(signedImgUpLine);
	free32(horizontTmpUpLine);
	free32(horizontOut);
	free32(verticalOut);
}




int CBaseSobel::init(int Width, int Height ){
	width	=Width;
	height	=Height;
	size	=width*height;
	wrapSize=size+2*width;
	isReady	=false;	

	signedImgUpLine	= (nm8s*)malloc32(wrapSize/4);
	signedImg		= VEC_Addr(signedImgUpLine,+width);
	
	horizontTmpUpLine= (nm16s*)malloc32(wrapSize/2); 
	horizontTmp		 = VEC_Addr(horizontTmpUpLine, width); 
	horizontTmpDnLine= VEC_Addr(horizontTmpUpLine, width*2);

	horizontOut		= (nm16s*)malloc32(size/2);	// Allocate temporary buffer 
	verticalOut		= (nm16s*)malloc32(size/2);	// Allocate temporary buffer

	// here was: FIR121.init(3,malloc32,free32);
	// here was: FIR101.init(3,malloc32,free32);

	if (signedImgUpLine==0 || horizontTmpUpLine==0 || horizontOut==0 || verticalOut==0)
		return false;

	// here was: if (FIR121.setWeights(sobelH)==0)
	// here was: 	return false;

	// here was: if (FIR101.setWeights(sobelV)==0)
	// here was: 	return false;

	isReady=true;
	return true;

}
	
	
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
	nm8u* sourceUpLine=VEC_Addr(source,-width);
	VEC_SubC((nm8s*)sourceUpLine, 128, (nm8s*)signedImgUpLine, wrapSize);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	// here was: FIR121.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	filter3h ( signedImgUpLine, horizontTmpUpLine, wrapSize, sobel_weights121);

	VEC_SubV(horizontTmpUpLine, horizontTmpDnLine, horizontOut, size);

	// vertical edge selection 
	// here was: FIR101.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	filter3h(signedImgUpLine, horizontTmpUpLine, wrapSize, sobel_weights101);

	VEC_Add2VW (horizontTmp, horizontTmpUpLine,horizontTmpDnLine,verticalOut, size);
	
	VEC_Abs1(horizontOut, horizontOut,size);	// Calculate absolute value 
	VEC_Abs1(verticalOut, verticalOut,size);	// Calculate absolute value 

	VEC_AddV(horizontOut,verticalOut,(nm16s*)verticalOut,size);		// Add 

	VEC_ClipCnv_AddC((nm16s*)verticalOut,8,0,(nm8s*)result, size, VEC_TBL_Diagonal_01h_G);
	
	return true;
}

CSobel::CSobel(){
	
}

CSobel::~CSobel(){
	CBaseSobel::~CBaseSobel();
}

CSobel::CSobel (int Width, int Height){
	init(Width, Height);
}

int CSobel::init (int Width, int Height){
	int sliceHeight=32;
	sliceCount =Height/sliceHeight;
	CBaseSobel::init(Width, sliceHeight);
	return isReady;
}

int CSobel::filter ( const unsigned char *source, unsigned char *result){
	
	for(int slice=0; slice<sliceCount; slice++){
		unsigned char* sliceSrcImg8= VEC_Addr(source,slice*size);
		unsigned char* sliceDstImg8= VEC_Addr(result,slice*size);
		CBaseSobel::filter(sliceSrcImg8, sliceDstImg8);
	}
	return true;

}
