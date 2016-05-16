#include <time.h>
#include "sobel.h"
#include "nmplv.h"
#include "easybmp.h"
#include "malloc32.h"


void BMP2graydata(BMP& bmp, unsigned char* data){
	int k=0;
	int width =bmp.TellWidth();
	int height=bmp.TellHeight();

	for (int i=0; i<height; i++){
		for (int j=0; j<width; j++){
			RGBApixel pix=bmp.GetPixel(j,i );
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

	unsigned char* srcPull= new unsigned char[width*height+2*width];
	unsigned char* srcData=srcPull+width;
	unsigned char* dstPull= new unsigned char[width*height+2*width];
	unsigned char* dstData=dstPull+width;

	
	BMP2graydata(srcBMP, srcData);
	//sobel( srcData, dstData, width, height);
	CBaseSobel sobel(width, height);
	if (!sobel.isReady) return -1;
	
	clock_t t0=clock();
	for(int i=0; i<100000000; i++)
		sobel.filter(srcData,dstData);
	
	clock_t t1=clock();
	printf ("%d", t1-t0);

 	graydata2BMP(dstData, dstBMP);

	dstBMP.WriteToFile("dst.bmp");
	
	delete srcPull;
	delete dstPull;
    
	return t1-t0; 
} 
//		t1-t0	7097,7088,7105,7092,7052	long
// 7132 7089
// 56798 56802