## Шаг 2. Портирование С++ кода на NMC RISC-ядро с 32-разрядным доступом

*В данном уроке осуществим A-варинат портирования алгоритма с байтовыми опреациями на RISC-ядро*  
Т.е. все операции доступа у нас будут целиком 32-разрядные. А каждый пиксель входного и выходноготизображения  должен храниться для этого в  отдельном 32-р. слове . 
Для этого выделем временные 32-разрядные массивы **source** и **result**
и расспакуем данные из байтовой картинки в 32-разрядный массив с помощью функции **VEC_Cnv**: 
Для NMC типы **char** можено было бы оставить неизменными так как на NMC-компилятор их интерпретирует как 32-разрядные. Но для кросплатформенноси будем вместо **char** использоывать **int**, а вместо **malloc** - **malloc32**, выделяющий память в 32-разрядных словах.

В результате модификаций получим следующий код : 

```cpp
#include "nmpp.h"		//[Added]
#include "malloc32.h"	//[Added]

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

void sobel( const unsigned char *_source,unsigned char *_result, int width, int height)
{
	unsigned int* source=(unsigned int*)malloc32(width*height);				//[Added] Allocate 32-bit buffer
	unsigned int* result=(unsigned int*)malloc32(width*height);				//[Added] Allocate 32-bit buffer
	VEC_Cnv((nm8u*)_source,(nm32u*)source,width*height);	//[Added] Convert 8-bit char elements to 32-bit int elements

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
	VEC_Cnv((nm32s*)result,(nm8s*)_result,width*height);	//[Added] Convert 32-bit int to 8-bit char elements
	free32(source);											//[Added]
	free32(result);											//[Added]
}
```

Аналогично предыдущему шагу мы получаеся программу для PC и для NM, в автономном и неавтономном режиме для разных плат и эмулятора 


В результате исполнения в этой же папке должен появиться dst.bmp

#### Производительность: 
-  clocks per frame 
- clocks per pixel
-  fps
