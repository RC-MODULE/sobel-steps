## Шаг 13. Распараллеливание входных и выходных потоков данных 

На предыдущих шаг мы использовали внутреннюю память процессора, но никак не учитывали потоки данных между банками внутренней памяти.
Внутренняя память nmc ядра состоит из 4 банков памяти по 128кБ. Архитектура процессора позволяет осуществлять одновременный доступ к этим банкам и организовать 4 параллельных потока данных, например 
для векторных команд взвешенного суммирования vsum:
-из банка 0 - происходит чтение команд
-из банка 1 - читаются входные данные 
-из банка 2 - подгружаются весовые коэффициенты
-в  банк 3 - сохраняется результат 

Если код, входные , выходные массивы и коэффициенты матрицы умножения удастся разложить по разным банкам, то это даст максимальную производительность SIMD команд ~1 такт на операцию. 

Создадим динамически три пуля для данных : pool1, pool2 , pool3 
и попробуем разместить в них входные и выходные массивы для каждой функции так , чтобы они располагались в разных пулах :





|pool0            |pool1              |pool2   					|pool3  			|pool4  |Shared    		|
|:--              |:--                |:--						|:---				|---	|---			|
|pool0            |INTERNAL_MEMORY10  |INTERNAL_MEMORY10		|pool3  			|pool4  |Shared    		|
|:--              |:--                |:--						|:---				|---	|---			|
|VEC_SubC         |signedImgUpLine    |horizontTmpUpLine   		|   				|   	|sourceUpLine   |
|filter3h         |**signedImgUpLine**|horizontTmpUpLine   		|sobel_weights121   |   	|   			|
|filter3v         |sobel_weights101v  |**horizontAbs**     		|horizontOut   		|   	|   			|
|VEC_Abs1         |                   |sobel_weights101    		|horizontOut   		|   	|   			|
|filter3h         |signedImgUpLine    |sobel_weights121v   		|verticalTmpUpLine  |   	|   			|
|filter3v         |**verticalOut**    |                       	|verticalTmp   		|   	|   			|
|VEC_Abs1         |verticalOut        |horizontAbs            	|verticalAbs   		|   	|   			|
|VEC_AddV         |summ               |vec_tbl_Diagonal_01h_G 	|verticalAbs    	|   	|   			|
|VEC_ClipCnv_AddC |summ               |                       	|   				|   	|result   		|











В результате данной оптимизации мы получили следующий прирост скорости: 

- 13109964 clocks per frame
- 31.61 clocks per pixel
- 24.41 fps








