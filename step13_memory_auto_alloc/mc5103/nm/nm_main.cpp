#include "mc5103_load.h"
#include "sobel.h"
#include "malloc32.h"
#include <time.h>


#pragma data_section ".data_shared_src.bss"
	long src[1920*1080/8+64/8];
#pragma data_section ".data_shared_dst.bss"
	long dst[1920*1080/8+64/8];
	
int main()
{  
	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = halHostSync(0);
	int height= halHostSync(1);
	int size  = width*height;

	
	
	
		
	halHostSync((int)src);		// Send source buffer address to host
	halHostSync((int)dst);		// Send result buffer address to host
		
	
	clock_t t0,t1;
	int counter=0;				// frame counter
	nmppsMallocResetRoute();
	nmppsMallocSetRouteMode();
	//nmppsMallocSetRingMode();
	//fseq64 route=0x033132310;
	//nmppsMallocSpec.route[0]=0x033132310;
	//nmppsMallocSpec.route[0]  =0x000022310;
	//nmppsMallocSetRoute16(&route);
	Sobel sobel;
	if (sobel.initAlloc(width,60))	halHostSync(0xDEADB00F);	// send ok to host
	else									halHostSync(0x600DB00F);	// send ok to host

	while(1){					// Start sobel in loop 
		halHostSync(counter);	// Wait source buffer till is ready 		
		if (nmppsMallocResetPos()) return -1;
		
		int* route=(int*)nmppsMallocSpec.route;		
		for(int i=0; i<2; i++)
			halHostSync(route[i]);


		t0=clock();
		nmppsMallocTimerStart();
		//sobelCuts((unsigned char*)src,(unsigned char*)dst, width, height, 60);
		if (sobel.filter((unsigned char*)src,(unsigned char*)dst))
			nmppsSet_8u((nm8u*)dst,64,size);
		nmppsMallocTimerStop();
		t1=clock();
		


		for(int i=0; i<2; i++)
			halHostSync(route[i]);


		if (nmppsMallocFail()){
			nmppsMallocWipe();
			halHostSync(0);	// Send elapsed time 
		}
		else{
			nmppsMallocBetterRoute();
			halHostSync(nmppsMallocSpec.timeBest);	// Send elapsed time 
		}
		
		//halHostSync(nmppsMallocSpec.route[0]);
		//halHostSync(nmppsMallocSpec.route[0]>>32);
		
		//nmppsMallocIncrementRoute();
		if (nmppsMallocIncrementRoute()) 
			break;
		//nmppsMallocRandomRoute();
		//nmppsMallocRandomRoute();
		counter++;
		//if (counter>80)
		//	nmppsMallocSetBestRoute(0);
	}
	halHostSync(0xDEADB00F);

	return 1; 
} 

