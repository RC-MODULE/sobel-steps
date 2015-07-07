## Шаг 12. Оптимизация фильтра выделения вертикальных границ 


###  Используем filter3v вместо VEC_SubV

Заменяем операцию вычитания двух массивов фильтрацию с коэффиценами (-1,0,1). 
```cpp
	...
	//VEC_SubV(horizontTmpUpLine, horizontTmpDnLine, horizontOut, size);
	filter3v(horizontTmpUpLine, horizontOut,  width, height, sobel_weights101v);
	...
```


###  Используем filter3v вместо VEC_Add2VW

Заменяем операцию суммирования двух массивов и одного удвоенного , на фильтрацию с коэффиценами (1,2,1). 
```cpp
	...
	//VEC_Add2VW (horizontTmp, horizontTmpUpLine,horizontTmpDnLine,verticalOut, size);
	filter3v((nm16s*)horizontTmpUpLine, verticalOut, width, height, sobel_weights121v);
	...
```


В результате данной оптимизцаии мы получили следующий прирост : 

- 13109964 clocks per frame
- 31.61 clocks per pixel
- 24.41 fps








