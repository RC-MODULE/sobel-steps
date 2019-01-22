//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "vshell.h"
#include "sobel.h"
#include "nmpp.h"


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

	nm8u* srcImg8=nmppsMalloc_8u (size);	// Allocate source image buffer with guard fields of two rows
	nm8u* dstImg8=nmppsMalloc_8u (size);	// Allocate result image buffer 
	
	
	CSobel sobel(width, height);

	while(VS_Run())	{
        VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
		VS_SetData(1, srcImg8);				// Put source image in window 1

		sobel.filter(srcImg8, dstImg8);
		
		VS_SetData(2, dstImg8);				// Put result image in window 2
		VS_Draw(VS_DRAW_ALL);				// Draw all windows
	}
    
	nmppsFree(srcImg8);	// Free source image buffer 
	nmppsFree(dstImg8);	// Free result image buffer 
    return 0;
}
