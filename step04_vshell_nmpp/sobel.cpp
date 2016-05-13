#include "nmpli.h"
#include "malloc32.h"

int sobelH[9]={
		1, 2, 1,
		0, 0, 0,
	   -1,-2,-1
};

int sobelV[9]={
		1, 0,-1,
		2, 0,-2,
		1, 0,-1
};

bool sobel( const unsigned char *source, unsigned char *result, int width,int height)
{
	NmppiFilterState *pHorizontState;
	NmppiFilterState *pVerticalState;
	nmppiFilterInitAlloc_8s16s(&pHorizontState,sobelH,3,3,width);
	nmppiFilterInitAlloc_8s16s(&pVerticalState,sobelV,3,3,width);
	
	int size=width*height;
	nm16s* horizontOut= nmppsMalloc_16s(size);	// Allocate temporary buffer 
	nm16s* verticalOut= nmppsMalloc_16s(size);	// Allocate temporary buffer

	if (nmppsMallocFail())			// Check all allocation are successful
		return false;
	
	nmppsSubC_8s((nm8s*)source, 128, (nm8s*)source, size);	// Transform dynamic range 0..255 to -128..+127

	nmppiFilter_8s16s((nm8s*)source, horizontOut, width, height, pHorizontState); 	// horizontal edge detection
	nmppiFilter_8s16s((nm8s*)source, verticalOut, width, height, pVerticalState);  	// vertical   edge detection

	nmppsAbs_16s(horizontOut, horizontOut, size);	// Calculate absolute value 
	nmppsAbs_16s(verticalOut, verticalOut, size);	// Calculate absolute value 

	nmppsAdd_16s(horizontOut, verticalOut, verticalOut,size);		// Add 
	nmppsClipPowC_16s(verticalOut, 8, verticalOut, size);// Thresh function to leave pixels in 0..255 range
	nmppsConvert_16s8s(verticalOut, (nm8s*)result, size);// Convert from 16-bit packed data to 8-bit packed data
	
	nmppsFree(horizontOut);
	nmppsFree(verticalOut);
	nmppiFilterFree(pHorizontState);
	nmppiFilterFree(pVerticalState);
	return true;
}