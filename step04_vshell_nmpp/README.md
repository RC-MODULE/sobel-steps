## Шаг 3. Портирование алгоритма на векторный процессор 

*В этом уроке модифицируем алгоритм таким образом, чтобы переложить логико-арифметические операции с RISC ядра на векторный сопроцессор*

Реализация функция **sobel** на предыдущем шаге использует только С++ конструкции и поэтому исполняется целиком на скалярном RISC-процессоре.
Производительность можно значительно увеличить если переложить вычисления со скалярного RISC-ядра на векторный сопроцессор с помощью оптимизированных функций на ассемблере.
Воспользуемся имеющимися векторными функциями из состава NMPP и заменим цикл в **sobel.cpp** на вызов этих функций :
```cpp
#include "nmpli.h"
#include "malloc32.h"

int sobelH[9]={
		1,2,1,
		0, 0,0,
		-1,-2,-1
};

int sobelV[9]={
		1,0,-1,
		2, 0,-2,
		1,0,-1
};

bool sobel( const unsigned char *source, unsigned char *result, int width,int height)
{
	NmppiFilterState *pHorizontState;
	NmppiFilterState *pVerticalState;
	nmppiFilterInitAlloc_8s16s(&pHorizontState,sobelH,3,3,width);
	nmppiFilterInitAlloc_8s16s(&pVerticalState,sobelV,3,3,width);
	
	int size=width*height;
	nm16s* horizontOut= nmppsMalloc_16s(size);	// Allocate temporary buffer 
	nm16s* verticalOut= nmppsMalloc_16s(size);	// Allocate temporary buffer

	if (nmppsMallocFail())			// Check all allocation are successful
		return false;
	
	nmppsSubC_8s((nm8s*)source, 128, (nm8s*)source, size);	// Transform dynamic range 0..255 to -128..+127

	nmppiFilter_8s16s((nm8s*)source, horizontOut, width, height, pHorizontState); 	// horizontal edge detection
	nmppiFilter_8s16s((nm8s*)source, verticalOut, width, height, pVerticalState);  	// vertical   edge detection

	nmppsAbs_16s(horizontOut, horizontOut, size);	// Calculate absolute value 
	nmppsAbs_16s(verticalOut, verticalOut, size);	// Calculate absolute value 

	nmppsAdd_16s(horizontOut, verticalOut, verticalOut,size);		// Add 
	nmppsClipPowC_16s(verticalOut, 8, verticalOut, size);// Thresh function to leave pixels in 0..255 range
	nmppsConvert_16s8s(verticalOut, (nm8s*)result, size);// Convert from 16-bit packed data to 8-bit packed data
	
	nmppsFree(horizontOut);
	nmppsFree(verticalOut);
	nmppiFilterFree(pHorizontState);
	nmppiFilterFree(pVerticalState);
	return true;
}
```

### Комментарии к коду:

- nmppsSubC_8s  
Векторный сопроцессор работает только с знаковыми целыми числами.
Так как изображение приходит в беззнаковом формате то для перевода чисел из диапазона [0..255] в [-128..127] используем функцию вычитания константы 
**nmppsSubC_8s**


#### Запуск
Запуск программы осуществляется через **make run** из папки *mb7707/pc/make_vs08* или *mb7707/pc/make_vs13* в зависимости от версии Visual Studio.
Запустив полученную программу получим производительность:
- 4868121 clocks per frame 
- 57 clocks per pixel
- 65.733781 fps   

Как видно из полученной производительности векторизация вычислений ускорило программу в 250 раз 

 



