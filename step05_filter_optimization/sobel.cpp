#include "nmplv.h"
#include "nmpls.h"
#include "malloc32.h"

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

#define WRAP_SIZE (1920/2+2)

void* wrap_malloc32 (unsigned size_int32)
{
	int* wrap=(int*)malloc32(size_int32+WRAP_SIZE*2);
	if  (wrap==0) return 0;
	int* goods=wrap+WRAP_SIZE;
	return goods;	
}

void wrap_free32(void* p)
{
	if (p)	free((int*)p-WRAP_SIZE);
}
	
bool sobel( const unsigned char *source, unsigned char *result, int width, int height)
{
	int size=width*height;

	nm16s* horizontTmp= (nm16s*)wrap_malloc32(size/2);
	nm16s* horizontOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer 
	nm16s* verticalOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer
	if (horizontTmp==0 || horizontOut==0 || verticalOut==0){
		free32(horizontOut);
		free32(verticalOut);
		wrap_free32(horizontTmp);
		return false;
	}

	CSIG_FIR<nm8s,nm16s> FIR121(3,malloc32,free32);
	CSIG_FIR<nm8s,nm16s> FIR101(3,malloc32,free32);
	if (FIR121.setWeights(sobelH)==0 || FIR101.setWeights(sobelV)==0)
		return false;	
	
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

	VEC_AddV(horizontOut,verticalOut,verticalOut,size);		// Add 

	VEC_ClipPowC(verticalOut,8,verticalOut,size);	// Thresh function to leave pixels in 0..255 range

	VEC_Cnv(verticalOut, (nm8s*)result, size);				// Convert from 16-bit packed data to 8-bit packed data


	wrap_free32(horizontTmp);
	free32(horizontOut);
	free32(verticalOut);
	return true;
}
