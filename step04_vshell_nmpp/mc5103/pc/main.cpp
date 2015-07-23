//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "VShell.h"
#include "pc_connector_mc5103.h"

#ifdef _DEBUG 
#define PROGRAM "../../nm/sobel_mc5103_nmd.abs"
#else
#define PROGRAM "../../nm/sobel_mc5103_nm.abs"
#endif

int main()
{
	// Access and loading program to nm-board
	C_PC_Connector_mc5103 Connector(PROGRAM);
	if (!Connector.isConnected()){
		printf("Connection to mc5103 error!");
		return -1;
	}

	int handshake= Connector.Sync(0xC0DE0086);
	if (handshake!=0xC0DE6406){
		printf("Handshake with mc5103 error!");
		return -1;
	}
	
	if(!VS_Init())
		return 0;

	//if(!VS_Bind("//dragon/distrib/streams/video/720x576/bugs.avi"))
	if(!VS_Bind("../../../../input/bugs720x576x20.avi"))
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
			
		if (t==0xDEADB00F)
			VS_Text("Memory allocation error in sobel!\n");
		VS_SetData(2, dstImg8);
		VS_Text("%u clocks per frame , %.2f clocks per pixel, %.2f fps", t, 1.0*t/size, 320000000.0/t );
		VS_Draw(VS_DRAW_ALL);
	}

	delete srcImg8;
	delete dstImg8;
    return 0;
}
