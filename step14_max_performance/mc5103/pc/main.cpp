//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include <windows.h>
#include <process.h> 
#include "VShell.h"
#include "time.h"
#include "stdio.h"
#include "pc_connector_mc5103.h"
//#include "profiler_access.h"

#ifdef _DEBUG 
#define PROGRAM "../../nm/sobel_mc5103_nmd.abs"
#else
#define PROGRAM "../../nm/sobel_mc5103_nm.abs"
#endif

#pragma data_section ".data_shared_src.bss"
	long long src_pgm_file[1920*1080/8+64/8];
#pragma data_section ".data_shared_dst.bss"
	long long dst_pgm_file[1920*1080/8+64/8];
	
	
PL_Access* access;
int ReadMemBlock(void* host_dst, unsigned nmc_addr, unsigned size32){
	return PL_ReadMemBlock(access,(PL_Word*)host_dst, (PL_Addr)nmc_addr, size32);
}

int main()
{
	// Access and loading program to nm-board
	C_PC_Connector_mc5103 Connector(PROGRAM);
	if (!Connector.isConnected()){
		printf("Connection to mc5103 error!");
		return -1;
	}
	access=Connector.access;
	int handshake= Connector.Sync(0xC0DE0086);
	if (handshake!=0xC0DE6406){
		printf("Handshake with mc5103 error!");
		return -1;
	}
	
	if(!VS_Init())
		return 0;

	if(!VS_Bind("../../../../input/Lena224x240.bmp"))
		return 0;

	
	int width =VS_GetWidth (VS_SOURCE);
	int height=VS_GetHeight(VS_SOURCE);

	int size  =width*height;

    VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);	// Create window for 8-bit source grayscale image
	VS_CreateImage("Sobel  Image", 2, width, height, VS_RGB8, 0);	// Create window for 8-bit result grayscale image

	Connector.Sync(width);		// Send width to nmc
	Connector.Sync(height);		// Send height to nmc
	int ok=Connector.Sync(0);	// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
		printf("Memory allocation error!");
		return -1;
	}
	unsigned srcAddr=Connector.Sync(0);
	unsigned dstAddr=Connector.Sync(0);
	
	unsigned char*  srcImg8=  new unsigned char [size];
	unsigned char*  dstImg8=  new unsigned char [size];

	
	
	
	while(VS_Run())	{
        VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
		VS_SetData(1, srcImg8);				// Put source image in window ?1
		Connector.WriteMemBlock((unsigned*)srcImg8, srcAddr, size/4);
		Connector.Sync(0);
		//... wait while sobel runs on board
		unsigned t=Connector.Sync(0);
		Connector.ReadMemBlock ((unsigned*)dstImg8, dstAddr, size/4);
			
		//profiler_print2tbl("../../nm/sobel_mc5103_nmd.map", ReadMemBlock);
		printf("\n");
	
	
		VS_SetData(2, dstImg8);
		VS_Text("%d clocks per frame, %.2f clocks per pixel, %.2f fps\r\n", t, 1.0*t/size, 320000000.0/t );
		VS_Draw(VS_DRAW_ALL);
	}

	delete srcImg8;
	delete dstImg8;
    
    return 0;
}
