#include <time.h>
#include "sobel.h"
#include "nmplv.h"
#include "easypgm.h"

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
	//width = 176;	height= 144;
	
	nm8u* src=nmppsAddr_8u((nm8u*)src_pgm_file,src_pgm_header_len);
	int dst_pgm_header_len=save_pgm_header(dst_pgm_file,width,height," Created By RC-Module(2015)");
	nm8u* dst=nmppsAddr_8u((nm8u*)dst_pgm_file,dst_pgm_header_len);
	
	// Sobel filtration
	SobelCuts sobel;
	if (sobel.initAlloc(width, height,30))
		return -1;
	clock_t t0=clock();
	sobel.filter(src,dst);
	clock_t t1=clock();

	sobel.free();
	return t1-t0; 
} 

