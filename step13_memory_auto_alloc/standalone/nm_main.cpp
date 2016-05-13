#include <time.h>
#include "sobel.h"
#include "nmplv.h"
#include "easypgm.h"
#include <stdio.h>

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
	//if (src_pgm_header_len==0) return -1;
	width=176;  height=60;

	nm8u* src=nmppsAddr_8u((nm8u*)src_pgm_file,src_pgm_header_len);
	int dst_pgm_header_len=save_pgm_header(dst_pgm_file,width,height," Created By RC-Module(2015)");
	nm8u* dst=nmppsAddr_8u((nm8u*)dst_pgm_file,dst_pgm_header_len);
	
	width =176;
	height=144;
	// Sobel filtration
	//NMPPS_BEGIN_MALLOC_SECTION();
	
	//seq64 currRoute[16];
	//seq64 bestRoute[16];
	//void*   allocHistory[32];
	//void*   freeHistory[32];
	
	//nmppsMallocSetRegularMode();
	//nmppsMallocTimerReset();
	//nmppsMallocReset(currRoute,allocHistory,freeHistory);
	//nmppsSet_64u(currRoute,0,16);
	
	//nmppsMallocSetPriorityMode(0x3210,4);
	
	nmppsMallocResetRoute();
	nmppsMallocSetRouteMode();
	Sobel sobel;
	sobel.initAlloc(width,60);
	int counter=0;
	int* route=(int*)nmppsMallocSpec.route;
	int* bestRoute=(int*)nmppsMallocSpec.bestRoute;
	while (1){
		//nmppsMallocSetRouteMode();
		//nmppsMallocRandomRoute();
		nmppsMallocResetPos();
		{
			nmppsMallocTimerStart();
			sobel.filter(src,dst);
			nmppsMallocTimerStop();
		}
		if (nmppsMallocSuccess()){
			if (nmppsMallocBetterRoute())
				printf("%08x %08x.%08x %d \n",counter,  bestRoute[1],bestRoute[0], nmppsMallocSpec.timeBest);
		}
		else 
			nmppsMallocWipe();
		
		
		if (nmppsMallocIncrementRoute()){
			printf("%08x %08x.%08x %d \n",counter,  route[1],route[0], nmppsMallocSpec.time);	
			break;
		}
		
		if (counter%0xFFF==0)
			printf("%08x       %08x.%08x %d \n",counter,  route[1],route[0], nmppsMallocSpec.time);
		counter++;
		
	}
	//-------------------------------
	nmppsMallocIncrementRoute();
	nmppsMallocIncrementRoute();
	//nmppsMallocSetBestRoute(ENABLE_HISTORY);
	//nmppsMallocSetHistoryMode();
	//CBaseSobel fastSobel(width, height);
	sobel.free();
	return nmppsMallocSpec.bestRoute[0];
	clock_t t0=clock();
	//sobelCuts(src,dst,width,height,60);
	clock_t t1=clock();
	//NMPPS_END_SECTION_SECTION();
	
	
	return t1-t0; 
} 

