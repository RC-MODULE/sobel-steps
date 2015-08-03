## Шаг 6. Оптимизация динамического выделения памяти 

В предыдущем шаге каждый раз при входе в функцию **sobel** мы использовали динамическое выделение и освобождение памяти, что неэффективно. 
Сделаем выделение памяти одноразовым, например с помощью конструктора класса CBaseSobel

```cpp
CBaseSobel::CBaseSobel(int Width, int Height){
	init(Width, Height);
}

CBaseSobel::~CBaseSobel(){
	free32(horizontTmpUpLine);
	free32(horizontOut);
	free32(verticalOut);
}

int CBaseSobel::init(int Width, int Height){
	width	=Width;
	height	=Height;
	size	=width*height;
	int wrapSize=size+2*width;
	isReady	=false;	
	
	horizontTmpUpLine= (nm16s*)malloc32(wrapSize/2);
	horizontTmp= VEC_Addr((nm16s*)horizontTmpUpLine, width);
	horizontOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer 
	verticalOut= (nm16s*)malloc32(size/2);	// Allocate temporary buffer

	FIR121.init(3,malloc32,free32);
	FIR101.init(3,malloc32,free32);

	if (horizontTmpUpLine==0 || horizontOut==0 || verticalOut==0)
		return false;

	if (FIR121.setWeights(sobelH)==0)
		return false;

	if (FIR101.setWeights(sobelV)==0)
		return false;

	isReady=true;
	return true;

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

