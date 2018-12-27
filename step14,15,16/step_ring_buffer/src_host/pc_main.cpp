//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "vshell.h"
#include "hal_host.h"
#include "ringbuffer_host.h"
#include "hal.h"
#include <stdio.h>
#include <process.h> 

HalHostRingBuffer* srcRingBuffer;
HalHostRingBuffer* dstRingBuffer;
HalRingBuffer* outBuffer;

char srcImg8[720*576];
void threadPop(void*) {
	/*
	int counter = 0;
	char * dst = new char[dstRingBuffer->size*4];
	while (1) {
		halHostRingBufferPop(dstRingBuffer, dst, 1);
		VS_SetData(2, dst);
		VS_Draw(VS_DRAW_ALL);
	}
	*/
	while (1) {
		halSleep(60);
		char* dst = (char*)halRingBufferTail(outBuffer);

		outBuffer->tail++;
		if (outBuffer->tail>= outBuffer->head) {
			outBuffer->tail = 0;
		}
		
		VS_SetData(2, dst);
		VS_Draw(VS_DRAW_ALL);
	}
}

int main()
{
	
	
	// Access and loading program to nm-board
	halSleep(5000);
	if (halOpen("sobel.abs",NULL)){
		printf("Connection error!");
		while (1);
		return -1;
	}
	halSleep(1000);
	int handshake= halSync(0xC0DE0086);
	if (handshake!=0xC0DE6406){
		printf("Handshake with mc5103 error!");
		while (1);
		return -1;
	}
	
	if(!VS_Init())
		return 0;

	//if (!VS_Bind("../../../input/bugs720x576x20.avi"))
	if (!VS_Bind("d:/Video/Films/640x480/Disney640x480.avi"))
	//if(!VS_Bind("../../../input/Pigeon_D176x144_ds.avi"))
		return 0;

	int width =VS_GetWidth (VS_SOURCE);
	int height=VS_GetHeight(VS_SOURCE);
	int size  =width*height;

    VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);	// Create window for 8-bit source grayscale image
	VS_CreateImage("Sobel  Image", 2, width, height, VS_RGB8, 0);	// Create window for 8-bit result grayscale image
	VS_CreateImage("Sobel  nmc",   3, width, height, VS_RGB8, 0);	// Create window for 8-bit result grayscale image

	halSync(width);		// Send width to nmc
	halSync(height);		// Send height to nmc|
	int ok=halSync(0);	// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
		printf("Memory allocation error!");
		while (1);
		return -1;
	}
	unsigned srcRingBufferAddr=halSync(0);
	unsigned dstRingBufferAddr=halSync(0);
	
	unsigned char*  srcImg8=  new unsigned char [size];
	unsigned char*  dstImg8=  new unsigned char [size];
	
	
	srcRingBuffer = new HalHostRingBuffer;
	dstRingBuffer = new HalHostRingBuffer;
	srcRingBuffer->sleep = 20;
	dstRingBuffer->sleep = 20;
	halHostRingBufferInit(srcRingBuffer, srcRingBufferAddr);
	halHostRingBufferInit(dstRingBuffer, dstRingBufferAddr);
	
	_beginthread(threadPop , 0, NULL);

	outBuffer = new HalRingBuffer;
	int * buffer = new int[srcRingBuffer->size * 256];
	halRingBufferInit(outBuffer, buffer, srcRingBuffer->size , 256, 0, 0, 0);

	char * dst;
	VS_OpRunForward();
	VS_Run();
	while (VS_Run()) {

		if (!halHostRingBufferIsFull(srcRingBuffer)) {
			VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
			VS_SetData(1, srcImg8);				// Put source image in window ?1
			halHostRingBufferPush(srcRingBuffer, srcImg8, 1);
		}

		if (!halHostRingBufferIsEmpty(dstRingBuffer)) {
			char* dst = (char*)halRingBufferHead(outBuffer);

			//halHostRingBufferPop(dstRingBuffer, dstImg8, 1);
			halHostRingBufferPop(dstRingBuffer, dst, 1);
			VS_SetData(3, dst);
			if (outBuffer->head < 156)
				outBuffer->head++;


		}
		VS_Draw(VS_DRAW_ALL);
	}
		
	
	
	
	


	delete srcImg8;
	delete dstImg8;

	halClose();
    return 0;
}
