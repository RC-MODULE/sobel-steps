#include "sobel.h"
#include "EasyBMP.h"

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
int main(){
	BMP srcBMP;
	//srcBMP.ReadFromFile("../../../input/lena.bmp");
	if (!srcBMP.ReadFromFile("../../input/Bikesgray.bmp"))
		return false;
	
	BMP dstBMP(srcBMP);

	int width =srcBMP.TellWidth();
	int height=srcBMP.TellHeight();

	unsigned char* srcData= new unsigned char[width*height];
	unsigned char* dstData= new unsigned char[width*height];

	BMP2graydata(srcBMP, srcData);
	sobel( srcData, dstData, width, height);
	graydata2BMP(dstData, dstBMP);

	dstBMP.WriteToFile("dst.bmp");
	
	delete srcData;
	delete dstData;
	return 0;
}
