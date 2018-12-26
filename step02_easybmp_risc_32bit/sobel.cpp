#include "nmpp.h"		



short sobelH[9]={
		1,2,1,
		0, 0,0,
		-1,-2,-1};

short sobelV[9]={
		1,0,-1,
		2, 0,-2,
		1,0,-1};

#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define MIN(a,b) ((a) > (b) ? (b) : (a))

int sobel( const nm8u *_source, nm8u *_result, int width, int height)
{
	
	unsigned int* source=(unsigned int*)nmppsMalloc32(width*height);				//[Added] Allocate 32-bit buffer
	unsigned int* result=(unsigned int*)nmppsMalloc32(width*height);				//[Added] Allocate 32-bit buffer
	if (source==0 || result==0)
		return -1;
	nmppsConvert_8u32u((nm8u*)_source,(nm32u*)source,width*height);	//[Added] Convert 8-bit char elements to 32-bit int elements

	int j,sum1,sum2;
	const unsigned int *line1, *line2, *line3;				//[Modified]
	line1 = source- width -1;
	line2 = line1 + width;
	line3 = line2 + width;
	const unsigned int* end=source+width*height;			//[Modified]
	unsigned int* res=result;								//[Added]
	
	for(j=0; j<height*width; j++){
		if (line1>source && (line3+2)<end){
		
			sum1  = line1[0]*sobelH[0] + line1[1]*sobelH[1] + line1[2]*sobelH[2] +
					line2[0]*sobelH[3] + line2[1]*sobelH[4] + line2[2]*sobelH[5] + 
					line3[0]*sobelH[6] + line3[1]*sobelH[7] + line3[2]*sobelH[8] ;
			
			sum2  = line1[0]*sobelV[0] + line1[1]*sobelV[1] + line1[2]*sobelV[2] +
					line2[0]*sobelV[3] + line2[1]*sobelV[4] + line2[2]*sobelV[5] + 
					line3[0]*sobelV[6] + line3[1]*sobelV[7] + line3[2]*sobelV[8] ;
			
			sum1=(sum1>0)?sum1:-sum1;
			sum2=(sum2>0)?sum2:-sum2;
			*res=MIN(255,sum1+sum2);						//[Modified]
		}
		res++;
		line1++;
        line2++;
        line3++;
	}
	nmppsConvert_32s8s((nm32s*)result,(nm8s*)_result,width*height);	//[Added] Convert 32-bit int to 8-bit char elements
	nmppsFree(source);											//[Added]
	nmppsFree(result);											//[Added]
	return 0;
}