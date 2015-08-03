## Шаг 11. Оптимизация фильтра выделения горизонтальных границ 
Рабочий каталог *\step11_filter3h*

Для выделения горизонтальных границ мы использовали фильтр CSIG_FIR<nm8s,nm16s> с настраиваемым размером окна. 
Универсальность библиотечной функции удобна так как покрывает все возможные размеры фильтров,
однако цена за универсальность - снижение быстродействия. 
Реализуем на ассемблере специализированную функцию **filter3h** с фиксированным размером окна равным 3 и сравним два этих метода: 

Заменим на **filter3h**  старые вызовы **FIR121.filter** и **FIR101.filter**
```cpp
	...
	// here was: FIR121.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	filter3h ( signedImgUpLine, horizontTmpUpLine, wrapSize, sobel_weights121);
	...
	// here was: FIR101.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	filter3h(signedImgUpLine, horizontTmpUpLine, wrapSize, sobel_weights101);
	...
```

В результате данной оптимизации получили прирост производительности 7%: 
- 2176832 clocks per frame
- 5.25 clocks per pixel
- 147.00 fps








