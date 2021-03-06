﻿## Шаг 9. Профилирование 

Для оценки производительности функции мы использовали функции **clock**. Приступая к более глубокой оптимизации нам желательно знать время затраченное каждой функцией.
Для этих целей можно воспользоваться библиотекой профилирования. Подключение профилировщика осуществляется добавлением к проекту единственного файла *proflist_generated.asm*, 
в котором указываются полные имена функций, подлежащих профилированию.

Автоматически сгенерировать список имен всех доступных для профилирования функций вместе с самим файлом можно по уже имеющемуся map-файлу с помощью команды **make profile** .
После сборки и линковки *proflist_generated.asm* библиотека автоматически инициализируется и стартует на целовом устройстве, сохраняя результаты профилирования в разделямой памяти . 

Чтобы вывести результат профилирования со стороны хост программы необходимо вызывать функцию 
```cpp
	#include "profiler_access.h"
	...
	profiler_print2tbl("../../nm/sobel_mb7707_nmd.map", ReadMemBlock);
```
На вход **profiler_print2tbl** необходимо передать:
- имя map-файла, по которому функция сможет найти местоположение результатов профилирования в памяти и затем вывести их на экран.
- указатель на функцию копирования с помощью которой будет осуществляться доступ к результатом профилирования :

Определить данную функцию можно, например, следующим образом:
```cpp		

PL_Access* access;
int ReadMemBlock(void* host_dst, unsigned nmc_addr, unsigned size32){
	return PL_ReadMemBlock(access,(PL_Word*)host_dst, (PL_Addr)nmc_addr, size32);
}
```	
	
 


### Сборка 
Для автоматической генерации нового *proflist_generated.asm* необходимо:
- удалить имеющийся *proflist_generated.asm*
- собрать abs-файл (без proflist_generated.asm) командой *make* 
- сгенерировать *proflist_generated.asm* командой *make profile*
- отредактировать, удалить ненужные для профилирования функции 
- собрать abs-файл (с *proflist_generated.asm*) командой *make* 

### Запуск
Запуск осуществляется из папки *\sobel-steps\step09_profiling\mb7707\pc\make_vs08* командой *make run*  

За счет накладных расходов на профилирование общая производительность программы несоклько уменьшится:
- 3022707 clocks per frame
- 7.29 clocks per pixel
- 105.87 fps


Результат профилирования можно наблюдать в консольном окне в следующем виде :
![Рис.1](http://savepic.ru/7354995.png)
- Столбец 1 - общее время работы функции (в тактах)
- Столбец 2 - количество вызовов 
- Столбец 3 - усредненное время одного вызова 
- Столбец 4 - физический адрес функции 
- Столбец 5 - название функции









