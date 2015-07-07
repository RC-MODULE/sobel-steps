#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"
#include "sobel.h"


extern "C" {

	extern long long sobel_weights121[24];
	extern long long sobel_weights101[24];
	extern long long sobel_weights101v[30];
	extern long long sobel_weights121v[30];

	void filter3h( const char *source,  short *result, int size, void* weights);
	void filter3v( const short *source, short *result, int width, int height, void* weights);
};

void VEC_AddAbs1V (nm16s *pSrcVec1, nm16s *pSrcVec2, nm16s *pDstVec, int nSize);



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
	free32(pool1);
	free32(pool2);
	free32(pool3);
}




int CBaseSobel::init(int Width, int Height ){
	width	=Width;
	height	=Height;
	size	=width*height;
	wrapSize=size+2*width;
	isReady	=false;	

	pool1= malloc32(wrapSize/2,0x02);
	pool2= malloc32(wrapSize/2,0x04);
	pool3= malloc32(wrapSize/2,0x08);

	signedImgUpLine	 = (nm8s*)pool1;
	signedImg		 = VEC_Addr(signedImgUpLine,+width);
	
	horizontTmpUpLine= (nm16s*)pool2; 
	horizontTmp		 = VEC_Addr(horizontTmpUpLine, width); 
	
	verticalTmpUpLine= (nm16s*)pool3; 
	verticalTmp		 = VEC_Addr(verticalTmpUpLine, width); 
	
	horizontOut		 = (nm16s*)pool3;
	verticalOut		 = (nm16s*)pool1;
	horizontAbs      = (nm16s*)pool2;
	verticalAbs      = (nm16s*)pool3;
	summ			 = (nm16s*)pool1;

	if (pool1==0 || pool2==0 || pool3==0)
		return false;

	isReady=true;
	return true;
}





	
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
	nm8u* sourceUpLine=VEC_Addr(source,-width);
	VEC_SubC((nm8s*)sourceUpLine, 128, (nm8s*)signedImgUpLine, wrapSize);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	filter3h( signedImgUpLine, horizontTmpUpLine, wrapSize, sobel_weights121);
	filter3v(horizontTmpUpLine, horizontOut,  width, height, sobel_weights101v);
	VEC_Abs1(horizontOut, horizontAbs,size);	// Calculate absolute value 

	// vertical edge selection 
	filter3h(signedImgUpLine, verticalTmpUpLine, wrapSize, sobel_weights101);
	filter3v((nm16s*)verticalTmpUpLine, verticalOut, width, height, sobel_weights121v);
	VEC_Abs1(verticalOut, verticalAbs,size);	// Calculate absolute value 

	// summ
	//VEC_AddAbs1V(horizontAbs, verticalAbs ,(nm16s*)summ,size);		// Add 
	VEC_AddV(horizontAbs, verticalAbs,(nm16s*)summ,size);		// Add 
	VEC_ClipCnv_AddC((nm16s*)summ,8,0,(nm8s*)result, size, VEC_TBL_Diagonal_01h_G);
	
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
	int sliceHeight=30;
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
