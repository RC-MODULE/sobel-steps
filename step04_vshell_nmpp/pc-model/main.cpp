//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "VShell.h"
#include "nmpli.h"
#include "sobel.h"
#include "malloc32.h"

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

	nmppsMallocSetBoundary32(width/4);
	nm8u* srcImg8=nmppsMalloc_8u(width*height);
	nm8u* dstImg8=nmppsMalloc_8u(width*height);
	
	while(VS_Run())	{
        VS_GetGrayData(VS_SOURCE, srcImg8);
		VS_SetData(1, srcImg8);

		sobel(srcImg8, dstImg8, width, height);
		
		VS_SetData(2, dstImg8);
		VS_Draw(VS_DRAW_ALL);
	}
    
	nmppsFree(srcImg8);
	nmppsFree(dstImg8);
    return 0;
}
