# sobel-in-steps

Руководство предназначено для ознакомления с программированием процессоров сеймейства NeuroMatrix, работой с инструментальными платами МВ77.07 и МС5103,
описывается процесс разработки DSP-приложения в виде последовательности шагов начиная от запуска простой поведенческой С++ модели 
до разработки высоко-оптимизированного кода под векторный сопроцессор.
В качестве примера используются широко применяемый в области ЦОС фильтр Собеля.


*Step by step DSP application development for NeuroMatrix . There are examples of filter Sobel  starting from simple C++ model to high-optimized application using NeuroMatrix vector co-processor*

В процессе изучения будут рассмотрены следующие вопросы:
- Изучение вопросов портирования готовых приложений с x86 плафтормы на NMC
- Обеспечение кроссплафторменности исходных текстов. 
- Запуск приложений в автономном режиме для плат МЦ5103 и MB7707 
- Запуск приложение под управлением хост-программы для плат МЦ5103 и MB7707
- Работа с графической оболочки VSHELL для упрощения разработки и отладки ЦОС-приложений 
- Запуск программного кода на RISC-ядре
- Подключение векторной библиотеки NMPP и перенос кода на векторный сопроцессор
- Оптимизация алгоритма, доработка кода - разработка спец. функций на ассемблере 
- Модификации алгоритма - перенос обработки из внешней памяти - в быструю внутреннюю
- Профилирование
- Распараллеливание потоков данных по внутренним банкам памяти.  
- Работа с видеопамятью MB7707 , вывод изображения на телевизор через HDMI

 





##Установка утилит и средств разработки под Windows
Для обеспечения работоспособности данной сборки требуется: 

1. SDK для хост-машины: (на выбор)
 * [Visual Studio 2005 Express](http://apdubey.blogspot.ru/2009/04/microsoft-visual-studio-2005-express.html)
 * [Visual Studio 2013 Express](https://www.microsoft.com/en-US/download/details.aspx?id=44914)
2. Установить NMSDK 
 * Рекомендуется взять последнюю (бета)версию http://www.module.ru/mb7707/toolchains-win32/nmsdk306en_20150611.zip
3. Для сборки Makefile-ов необходимо иметь установленный *make*
 * Вариант установки-а:  
 -скачать все необходимые утилиты, в том числе инсталлятор *make*, с помощью скрипта *./sobel-steps/gnuwin32/get-utils.bat*   
  в результате должны появиться следующие файлы:  
  *make-3.81.exe unzip-5.51-1.exe coreutils-5.3.0-bin.zip unzip-5.51-1-bin.zip which-2.20-bin.zip*  
 -Запустить инсталлятор *make-3.81.exe*  
 -Прописать путь к установленному *make.exe* в %PATH%  
 * Вариант установки-b:  
   Самостоятельно *make* можно установить через Setup, скачав с http://gnuwin32.sourceforge.net/packages/make.htm
 * Вариант установки-с:   
   *make* можно вызывать из GCC пакета MinGW for Windows http://sourceforge.net/projects/mingw/  
4. Для установки дополнительных библиотек и пакетов ПО разработки НТЦ Модуль необходим распаковщик 'unzip':  
  -Скачать *unzip* можно с помощью скрипта */sobel-steps/gnuwin32/get-utils.bat*  
  -Установить *unzip-5.51-1.exe* либо в текущую директорию */sobel-steps/gnuwin32/*, либо в любую другую с добавлением соответствующего пути к *unzip* в %PATH%
5. Makefile поддерживает кроссплатформенную сборку под Windows 7/Windows XP/Linux,  поэтому для обеспечения совместимости также могут потребоваться unix-утилиты (*which,rm,mkdir*):  
 * Вариант установки -a:  
  -скачать с помощью скрипта */sobel-steps/gnuwin32/get-utils.bat*  
  -распаковать с помощью */sobel-steps/gnuwin32/unzip-utils.bat* в текущую директорию */sobel-steps/gnuwin32/*
 * Вариант установки -b:  
  -скачать и установить дистрибутивы со страниц http://gnuwin32.sourceforge.net/packages/which.htm и http://gnuwin32.sourceforge.net/packages/coreutils.htm

##Загрузка библиотек и видеороликов 
 
1. Для работы проекта используются следующие библиотеки НТЦ Модуль:
 * NMPP  - Библиотека поддержки базовых векторно-матричных функций на процессорах семейства NeuroMatrix
 * VSHELL - Программный модуль , представляющий графическую оболочку и API для вывода графики и изображений. 
 * БЗИО (Библиотека загрузки и обмена) для платы MB77.07 либо MC5103
 * NMPROFILER - библиотека для профилирования функций на NMC

  Скачать все необходимые компоненты, включая NMSDK, можно командой *make get* из папки '/deps/'.  
  Библиотеки NMPP и NMPROFILER рекомендуется установить локально в папку '/deps/'  командой 'make install'  
  Остальные компоненты обновить/установить по мере необходимости  (для библиотек БЗИО требуется чтобы были прописаны в PATH пути к /bin папкам)
    
  В файле /sobel-steps/env.mk  в соответствующих переменных указать пути к установленным библиотекам 
  
2. Загрузка видео-данных  
   Закачать тестовые видеоролики можно командой *make* из папки /sobel-steps/input
   
### Сборка и запуск
1. Запуск pc-nm приложения (с автоматической сборкой) выбранного шага осуществляется командой 'make run' из соответствующий папки хостовой части приложения, например 'mb7707/pc/make_vs08/'  либо непосредственно из среды VisualStudio.
2. Запуск автономного приложения (без хост-части) осуществляется командой 'make run' из соответствующий папки /standalone/
3. При работе с платой MB77.07 в pc/main.cpp необходимо переопределить MAC-адрес сетевого адаптера подключенного к плате в  main.cpp. По умолчанию используется 
```cpp
  unsigned char MAC_ADDRESS[] = {0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f};
```	
4. Убедиться, что перемычка на плате MB77.07 установлена (Загрузка OS Linux - не производится). 



### Содержание 
#### Шаг 0. [Реализация прототипа фильтра Собеля для хоста ](/step00_easybmp_prototype/)
 Рассматривается поведенческая модель. Запуск на хосте.
#### Шаг 1. [Подготовка к портированию на NMC](/step01_easybmp_port2nmc/)
 Адаптация кода для обеспечения кроссплатформенности 
#### Шаг 2. [Портирование. Запуск программы на NMC](/step02_easybmp_risc/)
 Осуществляется запуск модели на хосте, на RISC ядре процессора NMC на платах MB77.07 и МС5103
#### Шаг 3. [Портирование алгоритма на векторный процессор](/step03_easybmp_nmpp/)
  Используем векторные функции из состава NMPP 
#### Шаг 4. [Подключение графической оболочки VSHELL ](/step04_vshell_nmpp/)
 Переход от единичной обработки к покадровой используя графическую оболочку VSHELL
#### Шаг 5. [Оптимизация градиентных фильтров  ](/step05_filter_optimization/)
 Переход от двумерной фильтрации к одномерной 
#### Шаг 6. [Оптимизация динамического выделения памяти ](/step06_class/)
 Использование классов.
#### Шаг 7. [Модификация программы для работы во внутренней памяти nmc](/step07_internal_memory/)
 Переход к кусочной обработке изображения во внутренней памяти.
#### Шаг 8. [Устранение граничных дефектов кусочной обработки](/step08_edge_removal/)
#### Шаг 9. [Профилирование](/step09_profiling/)
#### Шаг 10. [Оптимизация векторных функций ](/step10_nmpp_optimization/)
#### Шаг 11. [Оптимизация фильтра выделения горизонтальных границ ](/step11_filter3h/)
#### Шаг 12. [Оптимизация фильтра выделения вертикальных границ ](/step12_filter3v/)
#### Шаг 13. [Распараллеливание входных и выходных потоков данных ](/step13_memory_optimization/)
#### Шаг 14. [Определение пиковой производительности](/step14_max_performance/)
#### Шаг 15. [HDMI вывод на экран в SD разрешении](/step15_hdmi_sd/)
#### Шаг 16. [HDMI вывод на экран в HD разрешении](/step16_hdmi_hd/)


 