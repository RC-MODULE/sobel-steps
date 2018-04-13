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
	int counter=0;				// frame counter
	clock_t t0,t1;
	
		
	halHostSync((int)src);		// Send source buffer address to host
	halHostSync((int)dst);		// Send result buffer address to host
		
	nmppsMallocSpec.route[0]=0x0321;
	nmppsMallocSetRouteMode();
	SobelCuts sobel;
	if (sobel.initAlloc(width,height,30)==0)
		halHostSync(0x600DB00F);	// send ok to host
	else 
		halHostSync(0xDEADB00F);	// send error to host
	
	
	while(1){					// Start sobel in loop 
		halHostSync(counter);	// Wait source buffer till is ready 		
		t0=clock();
		sobel.filter((nm8u*)src,(nm8u*)dst);
		t1=clock();
		halHostSync(t1-t0);	// Send elapsed time 
		counter++;
	}
	sobel.free();
	halHostSync(0xDEADB00F);


	return 1; 
} 

