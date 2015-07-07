## Шаг 14. Определение пиковой производительности  

Данный шаг , большой практической ценностине является 
функция написана для общего случая когда входное и выходное изображения находятся во внешней медленной (ddr) памяти, а обработка производится частями во внутренней.
Однако для небольших изображений <64kB возможна обработка целиком во внутренней памяти. Полученная при этом скорость будет соответствовать пиковой производительности 

 на ходится во внешней 
Так как входное и выходное изображения в большинстве случаев превосходят 64кб не вмещаются в банк памяти 128Кб. 
На предыдущих шаг мы использовали внутреннюю память процессора, но никак не учитывали потоки данных между банками внутренней памяти.
Внутренняя память nmc ядра состоит из 4 банков памяти по 128кБ. Архитектура процессора позволяет осуществлять одновременный доступ к этим банкам и организовать 4 параллельных потока данных, например 
для векторных команд взвешенного суммирования vsum:
-из банка 0 - происходит чтение команд
-из банка 1 - читаются входные данные 
-из банка 2 - подгружаются весовые коэффициенты
-в  банк 3 - сохраняется результат 

Если код, входные , выходные массивы и коэффициенты матрицы умножения удастся разложить по разным банкам, то это даст максимальную производительность SIMD команд ~1 такт на операцию. 

С помощью функции malloc32 cоздадим динамически три пула для данных : pool1, pool2 , pool3  из куч heap1, heap2, heap3 разместив их с помощью cfg-файла в сегментах nmc_data1, nmc_data2, nmc_data3 соответственно:

```cfg
MEMORY
{
	//------------- NMC ----------------------------------------
	INTERNAL_MEMORY10:	at  0x00050200,		len = 0x00007E00;	// 128K-IM1 NMC		(ARM:0x00140000	0x0017ffff	0x4000(256kB))
	INTERNAL_MEMORY11:	at  0x00058000,		len = 0x00008000;	// 128K-IM1 NMC			 
	INTERNAL_MEMORY30:	at  0x00060000,		len = 0x00008000;	// 128K-IM3 NMC		(ARM:0x00180000	0x001bffff	0x4000(256kB))
	INTERNAL_MEMORY31:	at  0x00068000,		len = 0x00008000;	// 128K-IM3 NMC			 
...
	EXTERNAL_MEMORY0: 	at 	0x10000000, 	len = 0x02000000;	// 128MB-EM0-DDR 	(ARM:0x40000000	0x7fffffff) 
	EXTERNAL_MEMORY1: 	at 	0x30000000, 	len = 0x02000000;	// 128MB-EM1-DDR 	(ARM:0xc0000000	0xffffffff) 
}

SEGMENTS
{
	code		    : in INTERNAL_MEMORY10;
	nmc_data0		: in INTERNAL_MEMORY10; 
	nmc_data1		: in INTERNAL_MEMORY11; 
	nmc_data2		: in INTERNAL_MEMORY30;
	nmc_data3		: in INTERNAL_MEMORY31;
...
	ddr_data0		: in EXTERNAL_MEMORY0;
	ddr_data1		: in EXTERNAL_MEMORY1;
}

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


Для указания выбора кучи используем функцию malloc32 с указанием маски доступных куч для выделения:

sobel.cpp:
```cpp
	...
	pool1= malloc32(wrapSize/2, INT_BANK1);
	pool2= malloc32(wrapSize/2, INT_BANK2);
	pool3= malloc32(wrapSize/2, INT_BANK3);
	...
```



И попробуем разместить в них входные и выходные массивы для каждой функции так , чтобы они располагались в разных пулах :

|[code]           |pool1[nmc_data1]   |pool2[nmc_data2] 		|pool3[nmc_data3]  	|pool4[ddr_data0]|Shared[ddr_data1] |
|:--              |:--                |:--						|:---				|---			|---				|
|VEC_SubC         |signedImgUpLine    |							|   				|   			|sourceUpLine   	|
|filter3h         |**signedImgUpLine**|horizontTmpUpLine   		|sobel_weights121   |   			|   				|
|filter3v         |sobel_weights101v  |horizontTmpUpLine   		|horizontOut   		|   			|   				|
|VEC_Abs1         |                   |**horizontAbs**     		|horizontOut   		|   			|   				|
|filter3h         |signedImgUpLine    |sobel_weights101    		|verticalTmpUpLine  |   			|   				|
|filter3v         |**verticalOut**    |sobel_weights121v   		|verticalTmp   		|   			|   				|
|VEC_Abs1         |verticalOut        |                       	|verticalAbs   		|   			|   				|
|VEC_AddV         |summ               |horizontAbs            	|verticalAbs    	|   			|   				|
|VEC_ClipCnv_AddC |summ               |vec_tbl_Diagonal_01h_G   |   				|   			|result   			|





В результате данной оптимизации мы имеем следующую скорость в пересчете на пиксель : 

2.58 clocks per pixel







