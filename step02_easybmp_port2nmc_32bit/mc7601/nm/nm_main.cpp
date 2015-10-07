#include <time.h>
#include "mc7601_ll_nm.h"
#include "sobel.h"

#pragma data_section ".data_shared_src.bss"
	long src[1920*1080/8+64/8];
#pragma data_section ".data_shared_dst.bss"
	long dst[1920*1080/8+64/8];
	
int main()
{  
	//cache_enable();
	
	//---------- start nm programm ------------
	int fromHost=ncl_hostSync(0xC0DE6406);		// barrier sync/ send handshake to host
	if (fromHost!=0xC0DE0086){					// barrier sync/ get  handshake from host
		return -1;
	}
	//return 1;

	// Get image parameters from host
	int width = ncl_hostSync(0);	// barrier sync / get image width  from host
	int height= ncl_hostSync(1);	// barrier sync / get image height from host
	int size  = width*height;
	
	// Check memory allocation
	if (src ==0 || dst==0){
		ncl_hostSync(0xDEADB00F);	// barrier sync/ send error to host
		return -1;
	}
	else 
		ncl_hostSync(0x600DB00F);	// barrier sync/ send ok to host
		
	ncl_hostSync((int)src);		// barrier sync/ Send source buffer address to host
	ncl_hostSync((int)dst);		// barrier sync/ Send result buffer address to host
		
	ncl_hostSync(0);	// Wait source buffer is ready 		
	clock_t t0=clock();
	sobel((unsigned char*)src,(unsigned char*)dst,width,height);
	clock_t t1=clock();
	ncl_hostSync(t1-t0);	// Send elapsed time 
	
	return 1; 
} 

