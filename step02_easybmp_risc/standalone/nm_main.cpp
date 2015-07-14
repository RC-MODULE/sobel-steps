#include <time.h>
#include "sobel.h"
#include "malloc32.h"
#include "nmplv.h"
#include "easypgm.h"
#include "memcfg.h"

int main(int argc, char *argv[])
{  
	// Read PGM-header if exists
	s_pgm_header pgm_header;
	if (read_pgm_header((unsigned*)EXCH_ZONE,&pgm_header)!=PGM_OK){
		pgm_header.data=(unsigned*)EXCH_ZONE;
		pgm_header.disp=0;
		pgm_header.width =128;	// set default value
		pgm_header.height=128;	// set default value
	}
	int width = pgm_header.width;
	int height= pgm_header.height;
	int size  = width*height;

	// Allocate memory for 8-bit source and result images in shared memory
	int* src=(int*)malloc32(size/4); if (src ==0 ) return -1;		
	int* dst=(int*)malloc32(size/4); if (dst ==0 ) return -1;
	
	// Copy form unaligned byte-position to aligned one
	VEC_Copyua((nm8s*)pgm_header.data, pgm_header.disp, (nm8s*) src, size);
	
	// Sobel filtration
	clock_t t0=clock();
	sobel((unsigned char*)src, (unsigned char*)dst, width, height);
	clock_t t1=clock();

	// Copy resulting picture back to unaligned byte-position
	for(int i=0; i<size; i++){
		int pix=VEC_GetVal((nm8u*)dst,i);
		VEC_SetVal((nm8u*)pgm_header.data, pgm_header.disp+i, pix);
	}

	free32(src);
	free32(dst);
	return t1-t0; 
} 

