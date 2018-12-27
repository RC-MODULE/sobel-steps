//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "VShell.h"
#include "sobel.h"
#include "malloc32.h"
#include "nmpp.h"


int main()
{
	if(!VS_Init())
		return 0;

	if(!VS_Bind("../../../input/bugs720x576x20.avi"))
		return 0;

	int width =VS_GetWidth (VS_SOURCE);
	int height=VS_GetHeight(VS_SOURCE);
	int size  =width*height;

    VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);
	VS_CreateImage("Sobel  Image", 2, width, height, VS_RGB8, 0);

	nm8u* srcFrame = nmppsMalloc_8u(width*height+2*width);
	nm8u* srcImage = nmppsAddr_8u(srcFrame,width);
	nm8u* dstImage = nmppsMalloc_8u(width*height);
	
	while(VS_Run())	{
        VS_GetGrayData(VS_SOURCE, srcImage);
		VS_SetData(1, srcImage);

		sobel(srcImage, dstImage, width, height);
		
		VS_SetData(2, dstImage);
		VS_Draw(VS_DRAW_ALL);
	}
    
	nmppsFree(srcFrame);
	nmppsFree(dstImage);
    return 0;
}
