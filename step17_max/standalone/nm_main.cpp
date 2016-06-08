#include <time.h>
#include "sobel.h"
#include "nmplv.h"
#include "easypgm.h"
#include "malloc32.h"

#include "stdio.h"
//#pragma data_section ".data_shared_src.bss"
//	long src_pgm_file[1920*1080/8+64/8];
//#pragma data_section ".data_shared_dst.bss"
//	long dst_pgm_file[1920*1080/8+64/8];
	

	

int main()
{  
	int width ;
	int height;
/*
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
	for (int i=0; i<1000;i++)
	sobel.filter(intSrc,intDst);
	clock_t t1=clock();

	// copy result from internal buffer back to shared one
	nmppsCopy_8u((nm8u*)intDst, (nm8u*)dst, width*height);
*/
	

	void* p[10];
	
	nmppsMallocResetRoute();
	
	nmppsMallocSetRoute16(0xF2010302010);
	clock_t t0=clock();
	for(int i=0; i<1000000; i++){
		
		p[0]=malloc(11);
		p[1]=malloc(21);


		p[2]=malloc(13);
		p[3]=malloc(31);

		free(p[0]);
		free(p[1]);

		p[4]=malloc(14);
		p[5]=malloc(15);
		free(p[2]);
		free(p[3]);

		p[6]=malloc(111);
		p[7]=malloc(31);

		free(p[4]);
		free(p[5]);
		free(p[6]);

		p[8]=malloc(31);
		p[9]=malloc(321);


		free(p[7]);
		free(p[8]);
		free(p[9]);

		//nmppsMallocSetHistoryMode();
	}
	
	clock_t t1=clock();

	//printf("t1-t0=%d",t1-t0);
	return t1-t0; 
} 
// NMC
// standard malloc 17323037/10/100 = 17323 at malloc/free
// RouteMode       18282722/10/100 = 18282 at nmppsMalloc/nmppsFree
// HistoryMode     1881696/10/100  = 1881  at nmppsMalloc/nmppsFree
// FixedMode
//       1788327490
// Speed 161143262

// PC 12874
// SPEED 400 
// 30 раз

// 39