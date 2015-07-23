/******************************************************************************
*    RC Module
*    NeuroMatrix(r) NM6406 Software
*
*    Software design:    S.Mushkaev
*
*
*    Copyright (c) 2015 RC Module Inc.
******************************************************************************/

#include "VShell.h"
#include "sobel.h"
#include "malloc32.h"
int main()
{
	if(!VS_Init())	// Init vshell
		return 0;

	if(!VS_Bind("../../../input/bugs720x576x20.avi"))	// Input video stream
		return 0;

	int width =VS_GetWidth (VS_SOURCE);	// Get width  of video frame
	int height=VS_GetHeight(VS_SOURCE);	// Get height of video frame
	int size  =width*height;

    VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);	// Create window for grayscale drawing of 8-bit source image
	VS_CreateImage("Sobel  Image", 2, width, height, VS_RGB8, 0);	// Create window for grayscale drawing of 8-bit result image

	unsigned char* srcImg8=(unsigned char*) wrap_malloc32(size/4);	// Allocate source image buffer with guard fields of two rows
	unsigned char* dstImg8=(unsigned char*)      malloc32(size/4);	// Allocate result image buffer 
	
	
	CSobel sobel(width, height);

	while(VS_Run())
	{
        VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
		VS_SetData(1, srcImg8);				// Put source image in window 1

		sobel.filter(srcImg8, dstImg8);
		
		
		VS_SetData(2, dstImg8);
		VS_Draw(VS_DRAW_ALL);
	}
    
	wrap_free32(srcImg8);	// Free source image buffer 
	free32(dstImg8);	  	// Free result image buffer 
    return 0;
}
