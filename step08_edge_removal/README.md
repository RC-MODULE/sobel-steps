## Шаг 8. Устранение граничных дефектов  

Проблема предыдущего шага заключается в том, что разрезая кадр на независимые слайсы мы тереям градиентную информацию на границах между ними. 
Для устранения этих дефектов , достаточно взять слайсы чуть шире по высоте на одну строку , чтобы они перекрывали друг друга. 

меняем код 6-го шага :
```cpp
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
	VEC_SubC((nm8s*)source,128,(nm8s*)result,size);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	FIR121.filter((nm8s*)result, horizontTmp, size);
	VEC_SubV(VEC_Addr(horizontTmp,-width), VEC_Addr(horizontTmp,width), horizontOut, size);
	
	// vertical edge selection 
	FIR101.filter((nm8s*)result, horizontTmp, size);
	[cut]
}
```

на 


```cpp
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
	nm8u* sourceUpLine=VEC_Addr(source,-width);
	VEC_SubC((nm8s*)sourceUpLine, 128, (nm8s*)signedImgUpLine, wrapSize);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	FIR121.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	VEC_SubV(horizontTmpUpLine, horizontTmpDnLine, horizontOut, size);

	// vertical edge selection 
	FIR101.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	[cut]
}

```

	
В результате полосы исчезли :
![Рис.1](http://i11.pixs.ru/storage/5/6/2/noedgejpg_8617812_17737562.jpg "Внешний вид оболочки VSELL и результат обработки")

но за счет обработки краевых эффектов производительность чуть снизилась:
- 18564196 clocks per frame ,
- 44.76 clocks per pixel, 
- 17.24 fps





