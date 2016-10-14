## Шаг 5. Оптимизация градиентных фильтров 
*На этом шаге выполним фильтрации более оптимальным способом*

В предыдущем шаге мы использовали двумерный фильтр с маской 3х3 для изображений. 
Однако , как видно, коэффициенты фильтра выделения горизонтальных границ отличаются только знаком в верхней и нижней строке.
```cpp
int sobelH[9]={
		1,2,1,
		0, 0,0,
		-1,-2,-1
};
```
поэтому функцию двумерной фильтрации
```cpp
nmppiFilterInitAlloc_8s16s(&pHorizontState,sobelH,3,3,width);
nmppiFilter_8s16s((nm8s*)source, horizontOut, width, height, pHorizontState); 	// horizontal edge detection
```
эффективней заменить на более быструю одномерную с последующим вычитанием результата из самого себя смещенным на две строки:
```cpp
int sobelH[3]={
		1,2,1
};
... 
// horizontal edge selection 
nmppsFIR_8s16s((nm8s*)result, horizontTmp, size, pFIRState121);
nmppsSub_16s(nmppsAddr_16s(horizontTmp,-width), nmppsAddr_16s(horizontTmp,width), horizontOut, size);
```

В случае выделения вертикальных границ с маской:
```cpp
int sobelV[9]={
		1,0,-1,
		2, 0,-2,
		1,0,-1
};
nmppiFilterInitAlloc_8s16s(&pVerticalState,sobelV,3,3,width);
nmppiFilter_8s16s((nm8s*)source, verticalOut, width, height, pVerticalState);  	// vertical   edge detection
```
можем поступить похожим образом, но результаты уже сложить между собой как 4 вектора-массива:
```cpp	
int sobelV[3]={
		1,0,-1
};
...
// vertical edge selection 
nmppsFIR_8s16s((nm8s*)result, horizontTmp, size, pFIRState101);
nm16s* lines[4]={nmppsAddr_16s(	horizontTmp,-width),
				horizontTmp,
				horizontTmp,
				nmppsAddr_16s(	horizontTmp,width)};
nmppsAdd4V_16s(lines, verticalOut, size); 

```

#### Запуск
В результате данной оптимизации имеем для MC77.07
- 17269696 clocks per frame ,
- 41.64 clocks per pixel, 
- 18.53 fps
Прирост производительности - 20%

