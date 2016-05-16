#include <time.h>
#include "sobel.h"
#include "nmplv.h"
#include "easypgm.h"
#include "malloc32.h"

#pragma data_section ".data_shared_src.bss"
	long src_pgm_file[1920*1080/8+64/8];
#pragma data_section ".data_shared_dst.bss"
	long dst_pgm_file[1920*1080/8+64/8];
	

	

int main()
{  
	int width ;
	int height;

	// parse pgm header	
	int src_pgm_header_len=read_pgm_header(src_pgm_file,width,height);
	if (src_pgm_header_len==0) return -1;
	
	nm8u* src=nmppsAddr_8u((nm8u*)src_pgm_file,src_pgm_header_len);
	int dst_pgm_header_len=save_pgm_header(dst_pgm_file,width,height," Created By RC-Module(2015)");
	nm8u* dst=nmppsAddr_8u((nm8u*)dst_pgm_file,dst_pgm_header_len);

	// allocate in/out buffer in internal memory
	nm8u* intSrc=(nm8u*)malloc32(width*height/4,HEAP_3);
	nm8u* intDst=intSrc;		
	free32(intSrc);
	if (intSrc==0) return -1;
	// copy image from shared memory to internal inplace buffer [intSrc]
	nmppsCopy_8u((nm8u*)src, (nm8u*)intSrc, width*height);
	
	// Sobel filtration
	CBaseSobel sobel(width, height);
	if (!sobel.isReady) return -1;
	clock_t t0=clock();
	sobel.filter(intSrc,intDst);
	clock_t t1=clock();

	// copy result from internal buffer back to shared one
	nmppsCopy_8u((nm8u*)intDst, (nm8u*)dst, width*height);
	return t1-t0; 
} 

