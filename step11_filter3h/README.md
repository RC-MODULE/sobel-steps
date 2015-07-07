## Шаг 11. Оптимизация филтра выделения горизонтальых границ 


###  Используем filter3h 

вместо универсальнй функции с проивзольным размером маски можно использовать специальизированную функцию. 
```cpp
	...
// here was: FIR121.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	filter3h ( signedImgUpLine, horizontTmpUpLine, wrapSize, sobel_weights121);
	...
```

и 
```cpp
	...
		// here was: FIR101.filter((nm8s*)signedImgUpLine, horizontTmpUpLine, wrapSize);
	filter3h(signedImgUpLine, horizontTmpUpLine, wrapSize, sobel_weights101);
	...
```


В результате данной оптимизцаии мы получили следующий прирост : 

- 13360045 clocks per frame
- 32.21 clocks per pixel
- 23.95 fps









