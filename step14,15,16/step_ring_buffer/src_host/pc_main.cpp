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


void threadPop(void*) {
	int counter = 0;
	char * dst = new char[dstRingBuffer->size*4];
	while (1) {
		halHostRingBufferPop(dstRingBuffer, dst, 1);
		VS_SetData(2, dst);
		VS_Draw(VS_DRAW_ALL);
	}
}

int main()
{
	
	
	// Access and loading program to nm-board
	halSleep(4000);
	if (halOpen("sobel.abs",NULL)){
		printf("Connection error!");
		return -1;
	}
	int handshake= halSync(0xC0DE0086);
	if (handshake!=0xC0DE6406){
		printf("Handshake with mc5103 error!");
		return -1;
	}
	
	if(!VS_Init())
		return 0;

	if (!VS_Bind("../../../input/bugs720x576x20.avi"))
	//if(!VS_Bind("../../../input/Pigeon_D176x144_ds.avi"))
		return 0;

	int width =VS_GetWidth (VS_SOURCE);
	int height=VS_GetHeight(VS_SOURCE);
	int size  =width*height;

    VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);	// Create window for 8-bit source grayscale image
	VS_CreateImage("Sobel  Image", 2, width, height, VS_RGB8, 0);	// Create window for 8-bit result grayscale image

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

	VS_OpRunForward();
	while (VS_Run()) {
		VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
		VS_SetData(1, srcImg8);				// Put source image in window ?1


		halHostRingBufferPush(srcRingBuffer, srcImg8, 1);
	}
	
	
	


	delete srcImg8;
	delete dstImg8;

	halClose();
    return 0;
}
