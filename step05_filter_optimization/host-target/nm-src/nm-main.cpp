#include <time.h>
#include "hal_target.h"
#include "sobel.h"

//#pragma data_section ".data_shared_src.bss"
//	long src[1920*1080/8+64/8];
//#pragma data_section ".data_shared_dst.bss"
//	long dst[1920*1080/8+64/8];
	
int main()
{  
	
	//cache_enable();
	//---------- start nm programm ------------
	int fromHost=halHostSync(0xC0DE6406);		// barrier sync/ send handshake to host
	if (fromHost!=0xC0DE0086){					// barrier sync/ get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = halHostSync(0);	// barrier sync / get image width  from host
	int height= halHostSync(1);	// barrier sync / get image height from host
	int size  = width*height;
	int* src = halMalloc32(size/4);
	int* dst = halMalloc32(size/4);

	// Check memory allocation
	if (src ==0 || dst==0){
		halHostSync(0xDEADB00F);	// barrier sync/ send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// barrier sync/ send ok to host
		
	halHostSync((int)src);		// barrier sync/ Send source buffer address to host
	halHostSync((int)dst);		// barrier sync/ Send result buffer address to host
		
	
	clock_t t0,t1;
	int counter=0;					// frame counter
	bool isOk;
	bool isPlay=1;
	while(1){						// Start sobel in loop 
		isPlay=halHostSync(counter);// Wait source buffer till is ready 		
		if (!isPlay) break;
		t0=clock();
		isOk=sobel((unsigned char*)src,(unsigned char*)dst, width, height);
		t1=clock();
		if (isOk == -1) {
			halHostSync(0xBEDA);	// Send elapsed time 
			break;
		}
		isPlay=halHostSync(t1-t0);	// Send elapsed time 
		if (!isPlay) break;
		counter++;
	}
	halHostSync(0x777);
	free(src);
	free(dst);
	return 0; 

} 

