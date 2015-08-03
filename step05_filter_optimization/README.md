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
horizontFIR.Filter((nm8s*)source, horizontOut, width, height);	// horizontal edge detection
```
эффективней заменить на более быструю одномерную с последующим вычитанием результата из самого себя смещенным на две строки:
```cpp
int sobelH[3]={
		1,2,1
};
... 
// horizontal edge selection 
FIR121.filter((nm8s*)result, horizontTmp, size);
VEC_SubV(VEC_Addr(horizontTmp,-width), VEC_Addr(horizontTmp,width), horizontOut, size);
```

В случае выделения вертикальных границ с маской:
```cpp
int sobelV[9]={
		1,0,-1,
		2, 0,-2,
		1,0,-1
};
verticalFIR.Filter((nm8s*)source, verticalOut, width, height);	// vertical   edge detection
```
можем поступить похожим образом, но результаты уже сложить между собой как 4 вектора-массива:
```cpp	
int sobelV[3]={
		1,0,-1
};
...
// vertical edge selection 
FIR101.filter((nm8s*)result, horizontTmp, size);
nm16s* lines[4]={VEC_Addr(horizontTmp,-width),
						horizontTmp,
						horizontTmp,
				VEC_Addr(horizontTmp,width)};
VEC_Add4V(lines, verticalOut, size); 
```

#### Запуск
В результате данной оптимизации имеем для MC77.07
- 17269696 clocks per frame ,
- 41.64 clocks per pixel, 
- 18.53 fps
Прирост производительности - 20%

