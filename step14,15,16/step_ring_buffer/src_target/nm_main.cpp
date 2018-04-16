#include "hal_target.h"
#include "sobel.h"
#include "malloc32.h"
#include <time.h>
#include "ringbuffer.h"

extern "C" {

#define WIDTH 720
#define HEIGHT 576
#define SIZE WIDTH*HEIGHT
#define MAX_COUNT 16
#ifdef __NM__
#pragma data_section ".data_shared_src.bss"
	long extSrc[SIZE*MAX_COUNT/8];
	//long extSrc[1920 * 1080 / 8 + 64 / 8];
	//long extSrc[720 * 576 / 8 * 8];
	//HalRingBuffer srcRingBuffer_;
	//HalRingBuffer dstRingBuffer_;

	//HalRingBuffer srcRingBuffer[1];
	//HalRingBuffer dstRingBuffer[1];
#pragma data_section ".data_shared_dst.bss"
	//long extDst[720*576 / 8 *8 ];
#endif	
};

int main()
{ 
//#ifndef __NM__
	
//#endif
	//---------- start nm program ------------
	int fromHost=halHostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = halHostSync(0);
	int height= halHostSync(1);
	int size  = width*height;
	int err;
	//int* intSrc=(int*)malloc32(size/4,HEAP_3);
	//int* intDst=intSrc;		
	//free32(intSrc);

//#ifndef __NM__
	//int* extSrc = (int*)halMalloc32(size/ 4 * 4);
	int* extDst = (int*)halMalloc32(size/ 4 * 4);
//#endif
	if (extSrc==0 || extDst ==0) {
		halHostSync(0xDEADB00F);	
		return -1;
	}

	CSobel sobel(width, height);
	
	// Check memory allocation
	if (sobel.isReady==false){ // || intSrc ==0 ){
		halHostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		halHostSync(0x600DB00F);	// send ok to host
		

	HalRingBuffer* srcRingBuffer = (HalRingBuffer*) halMalloc32(sizeof(HalRingBuffer));
	HalRingBuffer* dstRingBuffer = (HalRingBuffer*) halMalloc32(sizeof(HalRingBuffer));
	err= halRingBufferInit(srcRingBuffer, extSrc,  size / 4, 4, 0, 0, 0);
	err+=halRingBufferInit(dstRingBuffer, extDst,  size / 4, 4, 0, 0, 0);
	if (err) {
		halHostSync(0xDEADB00F);		// Send source buffer address to host
		return -1;
	}
	halHostSync((int)srcRingBuffer);		// Send source buffer address to host
	halHostSync((int)dstRingBuffer);		// Send result buffer address to host 
		
	
	clock_t t0,t1;
	int counter=0;				// frame counter
	while(1){					// Start sobel in loop 
		while (halRingBufferIsEmpty(srcRingBuffer))
			halSleep(15);
		while (halRingBufferIsFull(dstRingBuffer))
			halSleep(15);
		t0 = clock();
		sobel.filter((nm8u*)halRingBufferTail(srcRingBuffer), (nm8u*)halRingBufferHead(dstRingBuffer));
		t1 = clock();
		srcRingBuffer->tail++;
		dstRingBuffer->head++;
		counter++;
	}
	halHostSync(0xDEADB00F);
	
	free32(extSrc);
	free32(extDst);
	
	return 1; 
} 

