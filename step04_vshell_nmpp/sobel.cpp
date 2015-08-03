#include "nmpli.h"
#include "malloc32.h"

int sobelH[9]={
		1,2,1,
		0, 0,0,
		-1,-2,-1
};

int sobelV[9]={
		1,0,-1,
		2, 0,-2,
		1,0,-1
};

bool sobel( const unsigned char *source, unsigned char *result, int width,int height)
{
	CIMG_FIR<nm8s,nm16s> horizontFIR(3, 3, malloc32, (t_free_func)free);	// Init filter for horizontal edge detection
	CIMG_FIR<nm8s,nm16s> verticalFIR(3, 3, malloc32, (t_free_func)free);	// Init filter for vertical   edge detection
	if (horizontFIR.SetWeights(sobelH, width)==0 || verticalFIR.SetWeights(sobelV, width)==0) 
		return false;	
	
	int size=width*height;
	nm16s* horizontOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer 
	nm16s* verticalOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer
	if (horizontOut==0 || verticalOut==0){
		free32(horizontOut);
		free32(verticalOut);
		return false;
	}

	VEC_SubC((nm8s*)source, 128, (nm8s*)source, size);	// Transform dynamic range 0..255 to -128..+127

	horizontFIR.Filter((nm8s*)source, horizontOut, width, height);	// horizontal edge detection
	verticalFIR.Filter((nm8s*)source, verticalOut, width, height);	// vertical   edge detection

	VEC_Abs(horizontOut, horizontOut, size);	// Calculate absolute value 
	VEC_Abs(verticalOut, verticalOut, size);	// Calculate absolute value 

	VEC_AddV(horizontOut, verticalOut, verticalOut,size);		// Add 
	VEC_ClipPowC(verticalOut, 8, verticalOut, size);// Thresh function to leave pixels in 0..255 range
	VEC_Cnv(verticalOut, (nm8s*)result, size);		// Convert from 16-bit packed data to 8-bit packed data
	
	free32(horizontOut);
	free32(verticalOut);
	return true;
}