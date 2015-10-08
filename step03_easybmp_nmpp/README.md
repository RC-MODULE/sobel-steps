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
	CIMG_FIR<nm8s,nm16s> horizontFIR(3, 3, malloc32, (t_free_func)free);	// Init filter for horizontal edge detection
	CIMG_FIR<nm8s,nm16s> verticalFIR(3, 3, malloc32, (t_free_func)free);	// Init filter for vertical   edge detection
	if (horizontFIR.SetWeights(sobelH, width)==0 || verticalFIR.SetWeights(sobelV, width)==0) 
		return false;	
	
	int size=width*height;
	nm16s* horizontOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer 
	nm16s* verticalOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer
	if (horizontOut==0 || verticalOut==0){
		free32(horizontOut);
		free32(verticalOut);
		return false;
	}

	VEC_SubC((nm8s*)source, 128, (nm8s*)source, size);	// Transform dynamic range 0..255 to -128..+127

	horizontFIR.Filter((nm8s*)source, horizontOut, width, height);	// horizontal edge detection
	verticalFIR.Filter((nm8s*)source, verticalOut, width, height);	// vertical   edge detection

	VEC_Abs(horizontOut, horizontOut, size);	// Calculate absolute value 
	VEC_Abs(verticalOut, verticalOut, size);	// Calculate absolute value 

	VEC_AddV(horizontOut, verticalOut, verticalOut,size);		// Add 
	VEC_ClipPowC(verticalOut, 8, verticalOut, size);// Thresh function to leave pixels in 0..255 range
	VEC_Cnv(verticalOut, (nm8s*)result, size);		// Convert from 16-bit packed data to 8-bit packed data
	
	free32(horizontOut);
	free32(verticalOut);
	return true;
}
```

### Комментарии к коду:
- malloc32  
Так как функция **malloc** на хосте принимает размер в байтах, а на стороне NMC- в 32р.-словах, 
то для переносимости кода мы вынуждены стандартный вызов **malloc** на NMC обернуть в функцию **malloc32**, в которой размер передается в 32-разрядных словах и дальше использовать только его. 

```cpp
void* malloc32(unsigned size_int32 )
{
#ifdef __NM__
	return malloc(size_int32); 
#else
	return malloc(size_int32*4);
#endif
}
```
>Выделение памяти будет происходить из секции *heap* во внешний памяти согласно конфигурационному файлу.


- VEC_SubC  
Векторный сопроцессор работает только с знаковыми целыми числами.
Так как изображение приходит в беззнаковом формате то для перевода чисел из диапазона [0..255] в [-128..127] используем функцию вычитания константы 
**VEC_SubC**


#### Запуск
Запуск программы осуществляется через **make run** из папки *mb7707/pc/make_vs08* или *mb7707/pc/make_vs13* в зависимости от версии Visual Studio.
Запустив полученную программу получим производительность:
- 4868121 clocks per frame 
- 57 clocks per pixel
- 65.733781 fps   

Как видно из полученной производительности векторизация вычислений ускорило программу в 250 раз 

 



