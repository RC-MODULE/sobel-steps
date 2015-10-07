/******************************************************************************
*    RC Module
*    NeuroMatrix(r) NM6406 Software
*
*    Software design:    S.Mushkaev
*
*
*
******************************************************************************/

#include "pc_connector_mc5103.h"
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
#ifdef _DEBUG 
#define PROGRAM "../../nm/sobel_mc5103_nmd.abs"
#else
#define PROGRAM "../../nm/sobel_mc5103_nm.abs"
#endif

int main()
{
	BMP srcBMP;
	srcBMP.ReadFromFile("../../../../input/lena.bmp");
	BMP dstBMP(srcBMP);

	int width =srcBMP.TellWidth();
	int height=srcBMP.TellHeight();
	int size  =width*height;

	unsigned char* srcData= new unsigned char[width*height];
	unsigned char* dstData= new unsigned char[width*height];

	BMP2graydata(srcBMP, srcData);
	//sobel( srcData, dstData, width, height);
	//------- run sobel on nmc --------------
	// Access and loading program to nm-board
	C_PC_Connector_mc5103 Connector(PROGRAM);
	if (!Connector.isConnected()){
		printf("Connection to mc5103 error!");
		return -1;
	}

	int handshake= Connector.Sync(0xC0DE0086);
	if (handshake!=0xC0DE6406){
		printf("Handshake with mc5103 error!");
		return -1;
	}
	
	
	int ok;
	ok=Connector.Sync(width);		// Send width to nmc
	ok=Connector.Sync(height);		// Send height to nmc
	ok=Connector.Sync(0);			// Get	status of memory allocation from nm
	if (ok!=0x600DB00F){
		printf("Memory allocation error!");
		return -1;
	}
	unsigned srcAddr=Connector.Sync(0); // Recv source buffer address in NMC memory space
	unsigned dstAddr=Connector.Sync(0);	// Recv result buffer address in NMC memory space
	
	Connector.WriteMemBlock((unsigned*)srcData, srcAddr, size/4);	// Send data to NMC
	Connector.Sync(0);												// Barrier sync before call of Sobel filter on NMC

	//... wait while sobel is runing on board

	unsigned t=Connector.Sync(0);									// Barrier sync. Wait until Sobel filter is finished
	Connector.ReadMemBlock ((unsigned*)dstData, dstAddr, size/4);	// Recieve result data from NMC
	
	printf("%u clocks per frame , %d clocks per pixel, %f fps\r\n", t, t/size, 320000000.0/t );	
	
	
	//----------------------
	graydata2BMP(dstData, dstBMP);

	dstBMP.WriteToFile("dst.bmp");
	
	delete srcData;
	delete dstData;
    return 0;
	
	

	
	
}
