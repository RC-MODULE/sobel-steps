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

	nm8u* srcFrame = nmppsMalloc_8u(size+2*width);	// Allocate source image buffer with border fields of two rows
	nm8u* srcImage = nmppsAddr_8u(srcFrame,width);	// Source image 
	nm8u* dstImage = nmppsMalloc_8u(size);			// Allocate result image 
	
	CBaseSobel sobel(width, height);
	while(VS_Run()){
        VS_GetGrayData(VS_SOURCE, srcImage);	// Get image from video stream
		VS_SetData(1, srcImage);				// Put source image in window 1
		
		sobel.filter(srcImage, dstImage);
		
		VS_SetData(2, dstImage);				// Put result image in window 2
		VS_Draw(VS_DRAW_ALL);				// Draw all windows
	}
    
	nmppsFree(srcFrame);	// Free source image buffer 
	nmppsFree(dstImage);	// Free result image buffer 
    return 0;
}
