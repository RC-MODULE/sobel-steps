#include "mb7707_load.h"
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
	int fromHost=ncl_hostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = ncl_hostSync(0);
	int height= ncl_hostSync(1);
	int size  = width*height;
	
	// Check memory allocation
	if (src ==0 || dst==0){
		ncl_hostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		ncl_hostSync(0x600DB00F);	// send ok to host
		
	ncl_hostSync((int)src);		// Send source buffer address to host
	ncl_hostSync((int)dst);		// Send result buffer address to host
		
	
	clock_t t0,t1;
	int counter=0;				// frame counter
	bool isOk;
	while(1){					// Start sobel in loop 
		ncl_hostSync(counter);	// Wait source buffer till is ready 		
		t0=clock();
		isOk=sobel((unsigned char*)src,(unsigned char*)dst, width, height);
		t1=clock();
		if (isOk==false ) 
			break;
		ncl_hostSync(t1-t0);	// Send elapsed time 
		counter++;
	}
	ncl_hostSync(0xDEADB00F);
	free(src);
	free(dst);
	return 1; 
} 

