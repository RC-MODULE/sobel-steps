## Шаг 13. Распараллеливание входных и выходных потоков данных 
Рабочий каталог \step13_memory_optimization\

На предыдущих шаг мы использовали внутреннюю память процессора, но никак не учитывали потоки данных между банками внутренней памяти.  
Внутренняя память nmc ядра состоит из 4 банков памяти по 128кБ. Архитектура процессора позволяет осуществлять одновременный доступ к этим банкам и организовать 4 параллельных потока данных.  
Например, для векторных команд взвешенного суммирования vsum возможно 4 потока:
-из банка 0 - происходит чтение команд
-из банка 1 - читаются входные данные 
-из банка 2 - подгружаются весовые коэффициенты
-в  банк 3 - сохраняется результат 

Если код, входные , выходные массивы и коэффициенты матрицы умножения удается разложить по разным банкам, то это дает максимальную производительность SIMD команд в ~1 такт на операцию. 


Раннее мы использовали 4 динамических массива:  **signedImgUpLine, horizontTmpUpLine, horizontOut и verticalOut**.
И в принципе мы могли бы разместить каждый в отдельном банке, но в этом случае код пришлось бы перенести во внешнюю память, что замедлило бы быстродействие. 

Попробуем сохранить код в 0-ом банки и ограничиться 3 банками для данных, размещая в каждом массивы максимально возможного размера. 
Для этого создадим три пуля данных : pool1, pool2 , pool3 , в кучах heap1,heap2 и heap3  соответственно:
**sobel.cpp**:
```cpp
	...
	pool1= malloc32(wrapSize/2, INT_BANK1);
	pool2= malloc32(wrapSize/2, INT_BANK2);
	pool3= malloc32(wrapSize/2, INT_BANK3);
	...
```
И далее в этих пулах будем отводить области памяти **signedImgUpLine, horizontTmpUpLine, horizontOut и verticalOut** для функций , работая как с указателями. 
Также у нас есть 4 статических массива весовых коэффициентов: **sobel_weights121, sobel_weights101,sobel_weights121v,sobel_weights101v**, которые также непрерывно читаются в цикле образя поток данных.

Попробуем так разместить  весовые коэффициенты , входные и выходные массивы массивы так, чтобы при каждом вызове функций они с одной стороны располагались в разных пулах, 
а с другой новые данные не затирали результаты от предыдущих вызовов.
Это можно сделать как показано в таблице ниже:

|[code]           |pool1[nmc_data1]   |pool2[nmc_data2] 		|pool3[nmc_data3]  	|pool4[ddr_data0]|Shared[ddr_data1] |
|:--              |:--                |:--						|:---				|---			|---				|
|VEC_SubC         |**signedImgUpLine**|							|   				|   			|sourceUpLine    	|
|filter3h         |signedImgUpLine    |**horizontTmpUpLine**	|sobel_weights121   |   			|   				|
|filter3v         |sobel_weights101v  |horizontTmpUpLine   		|**horizontOut**	|   			|   				|
|VEC_Abs1         |                   |**horizontAbs**     		|horizontOut   		|   			|   				|
|filter3h         |signedImgUpLine    |sobel_weights101    		|**verticalTmpUpLine**|   			|   				|
|filter3v         |**verticalOut**    |sobel_weights121v   		|verticalTmpUpLine	|   			|   				|
|VEC_Abs1         |verticalOut        |                       	|**verticalAbs**	|   			|   				|
|VEC_AddV         |**summ**           |horizontAbs            	|verticalAbs    	|   			|   				|
|VEC_ClipCnv_AddC |summ               |vec_tbl_Diagonal_01h_G   |   				|   			|**result**			|
> Жирным шрифтом выделен результирующий параметр


Расположением весовых коэффициентов мы управляем через соответствующие секции в cfg-файле:
```cfg
SECTIONS
{
	.text				: in code;
	.data				: in code;
	.stack				: in code;
	.heap				: in ddr_data0;
	.heap1				: in nmc_data1;
	.heap2				: in nmc_data2;
	.heap3				: in nmc_data3;
	.text_sobel			: in nmc_data0;
	.data_sobel			: in nmc_data2;
	.data_sobel_weights101:  in nmc_data2;
	.data_sobel_weights121:	 in nmc_data3;
	.data_sobel_weights101v: in nmc_data1;
	.data_sobel_weights121v: in nmc_data2;
}
```

Для наиболее оптимального использования внутренней памяти массивы нужно выделять максимального большого размера. 
В зависимости от ширины изображения высота слайса подбирается опытным путем в init-функции .
```cpp
int CSobel::init (int Width, int Height){
	fullHeight=Height;
	// try to find maximum slice height to fit in internal memory
	for(int sliceHeight=(Height+29)/30*30; sliceHeight>=30; sliceHeight-=30){
		if (CBaseSobel::init(Width, sliceHeight))
			break;
	}
	return isReady;
}
```


### Запуск
В результате данной оптимизации мы получили следующий прирост скорости еще в 30%: 
- 1516584 clocks per frame
- 3.66 clocks per pixel
- 211.00 fps




