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
	
	
	VEC_Copyua((nm8s*)pgm_header.data, pgm_header.disp, (nm8s*) extSrc, size);
	

	CSobel sobel(width, height);
	if (!sobel.isReady) return -1;
	clock_t t0=clock();
	sobel.filter((unsigned char*)extSrc,(unsigned char*)extDst);
	clock_t t1=clock();

	for(int i=0; i<size; i++){
		int pix=VEC_GetVal((nm8u*)extDst,i);
		VEC_SetVal((nm8u*)pgm_header.data, pgm_header.disp+i, pix);
	}

	free32(extSrc);
	free32(extDst);
	return t1-t0; 
} 

// return is 1308967  1308967/720/576 = 3,156266878858 ticks per pixel