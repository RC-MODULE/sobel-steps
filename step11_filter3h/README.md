## Шаг 11. Оптимизация фильтра выделения горизонтальных границ 

Для выделения горизонтальных границ мы использовали фильтр nmppsFIRInitAlloc_8s16s(&pFIRState121,sobelH,3); с настраиваемым размером окна. 
Универсальность библиотечной функции удобна так как покрывает все возможные размеры фильтров,
однако цена за универсальность - снижение быстродействия. 
Реализуем на ассемблере специализированную функцию **filter3h** с фиксированным размером окна равным 3 и сравним два этих метода: 

Заменим на старые вызовы **nmppsFIR_8s16s** **filter3h**
```cpp
	...
	// here was: nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState121);
	filter3h ( signedImgUpLine, horizontTmpUpLine, frameSize, sobel_weights121);
	...
	// here was: nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState101);
    filter3h(signedImgUpLine, horizontTmpUpLine, frameSize, sobel_weights101);
	...
```

В результате данной оптимизации получили прирост производительности 7%: 
- 2176832 clocks per frame
- 5.25 clocks per pixel
- 147.00 fps








