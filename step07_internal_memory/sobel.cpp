#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"
#include "sobel.h"
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
	free32(horizontTmpUpLine);
	free32(horizontOut);
	free32(verticalOut);
}


int CBaseSobel::init(int Width, int Height ){
	width	=Width;
	height	=Height;
	size	=width*height;

	isReady	=false;	

	horizontTmpUpLine = (nm16s*)internal_malloc32((size+2*width)/2);
	horizontTmp= (nm16s*)VEC_Addr(horizontTmpUpLine,width);
	horizontOut= (nm16s*)internal_malloc32(size/2);	// Allocate temporary buffer 
	verticalOut= (nm16s*)internal_malloc32(size/2);	// Allocate temporary buffer

	FIR121.init(3,internal_malloc32,free32);
	FIR101.init(3,internal_malloc32,free32);

	if (horizontTmpUpLine==0 || horizontOut==0 || verticalOut==0)
		return false;

	if (FIR121.setWeights(sobelH)==0)
		return false;

	if (FIR101.setWeights(sobelV)==0)
		return false;

	isReady=true;
	return true;

}
	
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
	VEC_SubC((nm8s*)source,128,(nm8s*)result,size);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	FIR121.filter((nm8s*)result, horizontTmp, size);
	VEC_SubV(VEC_Addr(horizontTmp,-width), VEC_Addr(horizontTmp,width), horizontOut, size);
	
	// vertical edge selection 
	FIR101.filter((nm8s*)result, horizontTmp, size);
	nm16s* lines[4]={VEC_Addr(horizontTmp,-width),
							horizontTmp,
							horizontTmp,
					VEC_Addr(horizontTmp,width)};
	VEC_Add4V(lines, verticalOut, size); 

	VEC_Abs(horizontOut, horizontOut,size);	// Calculate absolute value 
	VEC_Abs(verticalOut, verticalOut,size);	// Calculate absolute value 

	VEC_AddV(horizontOut,verticalOut,(nm16s*)verticalOut,size);		// Add 

	VEC_ClipPowC((nm16s*)verticalOut,8,(nm16s*)verticalOut,size);	// Thresh function to leave pixels in 0..255 range

	VEC_Cnv((nm16s*)verticalOut, (nm8s*)result, size);				// Convert from 16-bit packed data to 8-bit packed data

	
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
	int sliceHeight=72;
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
