#include "mc5103_load.h"
#include "sobel.h"
#include "malloc32.h"
#include <time.h>

#pragma data_section ".data_shared_src.bss"
	long extSrc[1920*1080/8+64/8];
#pragma data_section ".data_shared_dst.bss"
	long extDst[1920*1080/8+64/8];	

int main()
{  
	//---------- start nm program ------------
	int fromHost=ncl_hostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = ncl_hostSync(0);
	int height= ncl_hostSync(1);
	int size  = width*height;

int* intSrc=(int*)malloc32(size/4,HEAP_3);
	int* intDst=intSrc;		
	free32(intSrc);
	
	CSobel sobel(width, height);
	
	// Check memory allocation
	if (sobel.isReady==false || intSrc ==0 ){
		ncl_hostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		ncl_hostSync(0x600DB00F);	// send ok to host
		
	ncl_hostSync((int)extSrc);		// Send source buffer address to host
	ncl_hostSync((int)extDst);		// Send result buffer address to host
		
	
	clock_t t0,t1;
	int counter=0;				// frame counter
	while(1){					// Start sobel in loop 
		ncl_hostSync(counter);	// Wait source buffer till is ready 		
		VEC_Copy((nm8u*)extSrc,(nm8u*)intSrc,size);
		t0=clock();
		sobel.filter((unsigned char*)intSrc,(unsigned char*)intDst);
		t1=clock();
		VEC_Copy((nm8u*)intDst,(nm8u*)extDst,size);
		ncl_hostSync(t1-t0);	// Send elapsed time 
		counter++;
	}
	ncl_hostSync(0xDEADB00F);
	
	free32(extSrc);
	free32(extDst);
	
	return 1; 
} 

