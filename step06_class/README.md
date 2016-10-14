## Шаг 6. Оптимизация динамического выделения памяти 

В предыдущем шаге каждый раз при входе в функцию **sobel** мы использовали динамическое выделение и освобождение памяти, что неэффективно. 
Сделаем выделение памяти одноразовым, например с помощью конструктора класса CBaseSobel

```cpp
CBaseSobel::CBaseSobel(int Width, int Height){
	init(Width, Height);
}

CBaseSobel::~CBaseSobel(){
	nmppsFreeFrame(&frame);
	nmppsFree(horizontOut);
	nmppsFree(verticalOut);
	nmppsFIRFree(pFIRState121);
	nmppsFIRFree(pFIRState101);
}

int CBaseSobel::init(int Width, int Height){
	width	=Width;
	height	=Height;
	size	=width*height;
	horizontTmp= nmppsMallocFrame_16s(size,width,&frame);
	horizontOut= nmppsMalloc_16s(size);	// Allocate temporary buffer 
	verticalOut= nmppsMalloc_16s(size);	// Allocate temporary buffer
	
	nmppsFIRInitAlloc_8s16s(&pFIRState121,sobelH,3);
	nmppsFIRInitAlloc_8s16s(&pFIRState101,sobelV,3);
	isReady=nmppsMallocSuccess();
	return isReady;
}
```
> Так как при вычитании кадров после фильтрации мы используем смещение на одну строку вверх и вниз, то выходим за рамки выделенного временного массива, поэтому реально требуется выделить массив чуть большего 
размера :
```cpp
int wrapSize=size+2*width;
horizontTmpUpLine= (nm16s*)malloc32(wrapSize/2);
```	
	
В результате данной оптимизации имеем для MC77.07
- 17237692 clocks per frame 
- 41.56 clocks per pixel,
- 18.56 fps

Здесь видим небольшой прирост скорости, это связно с тем что кадр обрабатывается большого размера и в медленной DDR памяти, на фоне чего оптимизация слабо заметна, 
однако в дальнейшем при переходе во внутреннюю память  и работы с кадром по частям эффект от этой оптимизации будет более существенным.

