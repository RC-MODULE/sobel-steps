#include <time.h>
#include "sobel.h"
#include "malloc32.h"
#include "nmplv.h"
#include "easypgm.h"


int main(int argc, char *argv[])
{  
	
	s_pgm_header pgm_header;
	read_pgm_header((unsigned*)0x10004000,&pgm_header);
	
	// Get image parameters from host
	int width = pgm_header.width;
	int height= pgm_header.height;
	int size  = width*height;

	// Allocate memory for 8-bit source and result images in shared memory
	int* extDst=(int*)malloc32(size/4,EXT_BANK0);
	int* extSrc=(int*)malloc32(size/4,EXT_BANK0);		
	
	int* intSrc=(int*)malloc32(size/4,INT_BANK3);
	int* intDst=intSrc;		
	free32(intSrc);
	
	VEC_Copyua((nm8s*)pgm_header.data, pgm_header.disp, (nm8s*) intSrc, size);
	

	CSobel sobel(width, height);
	if (!sobel.isReady) return -1;
	clock_t t0=clock();
	sobel.filter((unsigned char*)intSrc,(unsigned char*)intDst);
	clock_t t1=clock();

	for(int i=0; i<size; i++){
		int pix=VEC_GetVal((nm8u*)intDst,i);
		VEC_SetVal((nm8u*)pgm_header.data, pgm_header.disp+i, pix);
	}

	free32(extSrc);
	free32(extDst);
	return t1-t0; 
} 

// return is 138000  138000/224/240 = 2,566964285714 ticks per pixel