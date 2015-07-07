#include "mc5103_load.h"
#include "sobel.h"
#include "malloc32.h"
#include <time.h>

int main(int argc, char *argv[])
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

	// Allocate memory for 8-bit source and result images in shared memory
	int* extDst=(int*)malloc32(size/4,EXT_BANK0);
	int* extSrc=(int*)malloc32(size/4,EXT_BANK0);		
	
	int* intSrc=(int*)malloc32(size/4,INT_BANK3);
	int* intDst=intSrc;		
	free32(intSrc);
	
	
	CSobel sobel(width, height);
	
	// Check memory allocation
	if (sobel.isReady==false || extSrc ==0 || extDst==0 ){
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
		VEC_Copy(extSrc,intSrc,size);
		t0=clock();
		sobel.filter((unsigned char*)intSrc,(unsigned char*)intDst);
		//sobel.filter((unsigned char*)extSrc,(unsigned char*)extDst);
		t1=clock();
		VEC_Copy(intDst,extDst,size);
		ncl_hostSync(t1-t0);	// Send elapsed time 
		counter++;
	}
	ncl_hostSync(0xDEADB00F);
	
	free32(extSrc);
	free32(extDst);
	
	return 1; 
} 

