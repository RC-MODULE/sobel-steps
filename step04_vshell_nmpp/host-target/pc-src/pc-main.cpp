/******************************************************************************
*    RC Module
*    NeuroMatrix(r) NM6406 Software
*
*    Software design:    S.Mushkaev
*
*
*
******************************************************************************/

#include "hal_host.h"
#include "EasyBMP.h"
#include <windows.h>
#include "vshell.h"



int main()
{
	if (halOpen("target.abs", NULL)) {			// Load executable file to board, connect to shared memory
		::Sleep(10000);
		return -1;
	}

	int handshake= halSync(0xC0DE0086);
	if (handshake!=0xC0DE6406){
		printf("Handshake with board error!");
		return -1;
	}
	
	if(!VS_Init())
		return 0;

	//if(!VS_Bind("//dragon/distrib/streams/video/720x576/bugs.avi"))
	if(!VS_Bind("../../../input/bugs720x576x20.avi"))
		return 0;

	int width =VS_GetWidth (VS_SOURCE);
	int height=VS_GetHeight(VS_SOURCE);
	int size  =width*height;
	int ok,dt;

    VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);	// Create window for 8-bit source grayscale image
	VS_CreateImage("Sobel  Image", 2, width, height, VS_RGB8, 0);	// Create window for 8-bit result grayscale image
	ok=halSync(width);		// Send width to nmc
	ok=halSync(height);		// Send height to nmc
	ok=halSync(0);			// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
		printf("Memory allocation error!\n");
		return -1;
	}
	unsigned srcAddr=halSync(0); // Recv source buffer address in NMC memory space
	unsigned dstAddr=halSync(0);	// Recv result buffer address in NMC memory space
	
	unsigned char*  srcImg8=  new unsigned char [size];
	unsigned char*  dstImg8=  new unsigned char [size];
	while(VS_Run())	{
        VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
		VS_SetData(1, srcImg8);				// Put source image in window N1

		halWriteMemBlock((unsigned*)srcImg8, srcAddr, size/4);	// Send image to shared memory of nmc 
		ok=halSync(1);											// Barrier sync - force nmc to wait while new image is coming 
		//... wait while sobel runs on board

		dt=halSync(2);											// Barrier sync - signal from nmc that sobel-filter is finished
		halReadMemBlock ((unsigned*)dstImg8, dstAddr, size/4);	// Read result image
			
		if (dt==0xBEDA)
			VS_Text("Memory allocation error in sobel!\n");
		else 
			VS_Text("%u clocks per frame , %.2f clocks per pixel, %.2f fps\r\n", dt, 1.0*dt / size, 320000000.0 / dt);
		VS_SetData(2, dstImg8);
		
		VS_Draw(VS_DRAW_ALL);
	}
	ok = halSync(0);		// signal to terminate nmc
	ok = halSync(0x777);	// Final barrier sync - 777<-->777
	halClose();
	delete srcImg8;
	delete dstImg8;
    return 0;
	
	

	
	
}
