//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "VShell.h"
#include "hal_host.h"

#ifdef _DEBUG 
#define PROGRAM "../../nm/sobel_mb7707_nmd.abs"
#else
#define PROGRAM "../../nm/sobel_mb7707_nm.abs"
#endif

unsigned char MAC_ADDRESS[] = {0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f};
int main(int arcg)
{
	

	// Access and loading program to nm-board
	C_PC_Connector_mb7707 Connector(MAC_ADDRESS,PROGRAM);
	if (!Connector.isConnected()){
		printf("Connection to mc5103 error!");
		return -1;
	}

	int handshake= halSync(0xC0DE0086);
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

	halSync(width);		// Send width to nmc
	halSync(height);		// Send height to nmc
	int ok=halSync(0);	// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
		printf("Memory allocation error!");
		return -1;
	}
	unsigned srcAddr=halSync(0);
	unsigned dstAddr=halSync(0);
	
	unsigned char*  srcImg8=  new unsigned char [size];
	unsigned char*  dstImg8=  new unsigned char [size];
	
	
	
	while(VS_Run())	{
        VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
		VS_SetData(1, srcImg8);				// Put source image in window N1

		halWriteMemBlock((unsigned*)srcImg8, srcAddr, size/4);	// Send image to shared memory of nmc 
		halSync(0);												// Barrier sync - force nmc to wait while new image is coming 
		//... wait while sobel runs on board

		unsigned t=halSync(0);									// Barrier sync - signal from nmc that sobel-filter is finished
		halReadMemBlock ((unsigned*)dstImg8, dstAddr, size/4);	// Read result image
			
		if (t==0xDEADB00F)
			VS_Text("Memory allocation error in sobel!\n");
		VS_SetData(2, dstImg8);
		VS_Text("%u clocks per frame , %.2f clocks per pixel, %.2f fps\r\n", t, 1.0*t/size, 320000000.0/t );
		VS_Draw(VS_DRAW_ALL);
	}

	delete srcImg8;
	delete dstImg8;
    return 0;
}
