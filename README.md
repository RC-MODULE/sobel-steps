# sobel-in-steps
Пошаговое руководство процесса разработки DSP-приложения на процессоре NeuroMatrix . 
Руководство состоит из последовательности шагов начиная от запуска простой поведенческой модели до разработки высоко-оптимизированного кода под векторный сопроцессор.
В качестве примера используются широкоприменяемый в области ЦОС фильтр Собеля.  

*Step by step DSP application development for NeuroMatrix . There are examples of filter Sobel  starting from simple C++ model to high-optimized application using NeuroMatrix vector co-processor*


##Установка под Windows
Для обеспечения работоспособности данной сборки требуется: 

1. SDK для хост-машины: 
 * GCC http://sourceforge.net/projects/mingw/
 * Visual Studio 2005
 * Visual Studio 2013 Express
1. Установить NMSDK 
 * Рекомендуется взять последнюю (бета)версию http://www.module.ru/mb7707/toolchains-win32/nmsdk306en_20150611.zip
2. Для сборки Makefile-ов необходимо иметь установленный 'make'
 * Вариант-a: 'make' можно вызывать из пакета MinGW for Windows http://sourceforge.net/projects/mingw/ , прописав соответствующий путь в %PATH%. 
 * Вариант-b: 'make' Можно установить отдельным пакетом http://gnuwin32.sourceforge.net/packages/make.htm
    Также потребуется:
	libint3.dll http://gnuwin32.sourceforge.net/packages/libintl.htm
	libiconv2.dll http://gnuwin32.sourceforge.net/packages/libiconv.htm
3. Makefile поддерживает кроссплатформенную сборку под Windows 7/Windows XP/Linux,  поэтому для обеспечения совместимости таже могут потребоваться unix-утилиты:  
 * 'which' - http://gnuwin32.sourceforge.net/packages/which.htm
 * 'rm','mkdir' из пакета CoreUtils for Windows http://gnuwin32.sourceforge.net/packages/coreutils.htm
4. Для работы проекта используются библиотеки:
 * NMPP http://www.module.ru/mb7707/NeuroMatrix/
 * VSHELL http://www.module.ru/mb7707/NeuroMatrix/VSHELL_1.0.0.24.zip
 * БЗИО (Библиотека загрузки и обмена) для платы MB77.07 либо MC5103
 * Если библиотеки NMPP и VSHELL БЗИО уже установлены (определены переменные NMPP и VSHELL, MB7707, MC5103), то будут подключены именно эти библиотеки , если же они отсутствуют, то будут подключены локальные из папки /deps, входящие в состав данной сборки.    
  В этом случае библиотеку NMPP необходимо собрать командой 'make' из  папки  /deps/nmpp/make.
    Для библиотеки VSHELL.dll также может потребоваться путь 'YOUR_PATH/sobel-in-steps/deps/VSHELL/bin' в переменной %PATH% 
	
### Сборка и запуск
1. Запуск приложения (с автоматической сборкой) выбранного шага осуществляется командой 'make run' из соответствующий папки хостовой части приложения, например 'mb7707\pc\make_vs08\' 
2. При работе с платой MB77.07 необходимо переопределить MAC-адрес сетевого адаптера подключенного к плате в  main.cpp. По умолчанию используется 
```cpp
  unsigned char MAC_ADDRESS[] = {0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f};
```	