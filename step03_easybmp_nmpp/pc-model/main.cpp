//------------------------------------------------------------------------
//  Sobel filter 
//
//  Author: Sergey Mushkaev
//
//  Copyright (c) 2015 RC Module Inc.
//------------------------------------------------------------------------

#include "nmpli.h"
#include "sobel.h"
#include "EasyBMP.h"

void* malloc32(unsigned sizeInt32 );

void BMP2graydata(BMP& bmp, unsigned char* data){
	int k=0;
	int width =bmp.TellWidth();
	int height=bmp.TellHeight();

	for (int i=0; i<height; i++){
		for (int j=0; j<width; j++){
			RGBApixel pix=bmp.GetPixel(j,i);
			data[k++]=pix.Blue;
			//src[k++]= 0.2126 * pix.Red + 0.7152 * pix.Green + 0.0722 * pix.Blue;
		}
	}
}

void graydata2BMP(unsigned char* data, BMP& bmp ){
	int k=0;
	int width =bmp.TellWidth();
	int height=bmp.TellHeight();

	for (int i=0; i<height; i++){
		for (int j=0; j<width; j++){
			RGBApixel pix;
			pix.Blue =data[k];
			pix.Red  =data[k];
			pix.Green=data[k];
			bmp.SetPixel(j,i,pix);
			k++;
		}
	}

}
int main()
{

	BMP srcBMP;
	srcBMP.ReadFromFile("../../../input/lena.bmp");
	BMP dstBMP(srcBMP);

	int width =srcBMP.TellWidth();
	int height=srcBMP.TellHeight();

	unsigned char* srcPool= (unsigned char*) malloc32 (width*(height+4)/4);
	unsigned char* srcData= (unsigned char*) srcPool+width*2;
	unsigned char* dstData= (unsigned char*) malloc32 (width*height/4);
	
	if (srcPool==0 || dstData==0)
		return -1;

	BMP2graydata(srcBMP, srcData);
	sobel( srcData, dstData, width, height);
	graydata2BMP(dstData, dstBMP);

	dstBMP.WriteToFile("dst.bmp");
	
	free(srcPool);
	free(dstData);

    
    return 0;
}
