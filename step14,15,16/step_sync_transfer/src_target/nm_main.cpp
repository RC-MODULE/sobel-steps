#include "hal_target.h"
#include "sobel.h"
#include "malloc32.h"
#include <time.h>

#ifdef __NM__
#pragma data_section ".data_shared_src.bss"
	long extSrc[1920*1080/8+64/8];
#pragma data_section ".data_shared_dst.bss"
	long extDst[1920*1080/8+64/8];
#endif	
int main()
{ 
#ifndef __NM__
	int* extSrc = halMalloc32((1920 * 1080 / 8 + 64 / 8) / 2);
	int* extDst = halMalloc32((1920 * 1080 / 8 + 64 / 8) / 2);
#endif
	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = halHostSync(0);
	int height= halHostSync(1);
	int size  = width*height;

	int* intSrc=(int*)malloc32(size/4,HEAP_3);
	int* intDst=intSrc;		
	//free32(intSrc);
	
	
	CSobel sobel(width, height);
	
	// Check memory allocation
	if (sobel.isReady==false){ // || intSrc ==0 ){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		
	halHostSync((int)extSrc);		// Send source buffer address to host
	halHostSync((int)extDst);		// Send result buffer address to host
		
	
	clock_t t0,t1;
	int counter=0;				// frame counter
	while(1){					// Start sobel in loop 
		halHostSync(counter);	// Wait source buffer till is ready 		
		//nmppsCopy_8u((nm8u*)extSrc,(nm8u*)intSrc,size);
		t0=clock();
		//sobel.filter((nm8u*)intSrc,(nm8u*)intDst);
		sobel.filter((nm8u*)extSrc, (nm8u*)extDst);
		//nmppsCopy_8u((nm8u*)extSrc,(nm8u*)extDst,size);
		t1=clock();
		//nmppsCopy_8u((nm8u*)intDst,(nm8u*)extDst,size);
		halHostSync(t1-t0);	// Send elapsed time 
		counter++;
	}
	halHostSync(0xDEADB00F);
	
	free32(extSrc);
	free32(extDst);
	
	return 1; 
} 

