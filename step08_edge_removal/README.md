## Шаг 8. Устранение граничных дефектов  

Проблема предыдущего шага заключается в том, что разрезая кадр на независимые слайсы мы тереям градиентную информацию на границах между ними. 
Для устранения этих дефектов , достаточно взять слайсы чуть шире по высоте на одну строку , чтобы они перекрывали друг друга. 

меняем код 6-го шага :
```cpp
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
		nmppsSubC_8s((nm8s*)source,128,(nm8s*)result,size);	// Transform dynamic range 0..255 to -128..+127
		
		// horizontal edge selection 
		nmppsFIR_8s16s((nm8s*)result, horizontTmp, size, pFIRState121);
		nmppsSub_16s(nmppsAddr_16s(horizontTmp,-width), nmppsAddr_16s(horizontTmp,width), horizontOut, size);
		
		// vertical edge selection 
		nmppsFIR_8s16s((nm8s*)result, horizontTmp, size, pFIRState101);
	[cut]
}
```

на 


```cpp
int CBaseSobel::filter( const unsigned char *source, unsigned char *result)
{
	nm8s* sourceUpLine=nmppsAddr_8s((nm8s*)source,-width);
	nmppsSubC_8s(sourceUpLine, 128, signedImgUpLine, frameSize);	// Transform dynamic range 0..255 to -128..+127

	// horizontal edge selection 
	nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState121);
	nmppsSub_16s(horizontTmpUpLine, horizontTmpDnLine, horizontOut, size);

	// vertical edge selection 
	nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState101);
	[cut]
}

```

	
В результате полосы исчезли :
![Рис.1](http://savepic.su/5938789.jpg)

но за счет обработки краевых эффектов производительность чуть снизилась на 1%:
- 2848800 clocks per frame 
- 6.87 clocks per pixel
- 112.33 fps






