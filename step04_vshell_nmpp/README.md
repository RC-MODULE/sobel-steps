## Шаг 4. Подключение графической оболочки VSHELL 
В этом шаге переходим от единичной обработки к покадровой используя графическую оболочку VSHELL 


### модифицируем nmc-приложение
Модифицируем nmc-приложение на бесконечный цикл приема и обработки кадров в nm_main.cpp
```cpp
...
while(1){					// Start sobel in loop 
	ncl_hostSync(counter);	// Wait source buffer till is ready 		
	t0=clock();
	isOk=sobel((unsigned char*)src,(unsigned char*)dst, width, height);
	t1=clock();
	if (isOk==false ) 
		break;
	ncl_hostSync(t1-t0);	// Send elapsed time 
	counter++;
}
...
```

### модифицируем  host-приложение
Модифицируем пути в Makefile для хост приложения , добавляя пути к $(VSHELL ) и подключая библиотеку vshell.
```
INC_DIRS         = -I"$(VSHELL)/include" -I"$(MB7707)/pc/include" -I$(ROOT)/deps/connector
LIB_DIRS         = -L"$(VSHELL)/lib"     -L"$(MB7707)/pc/lib"
LIBS             = vshell.lib mb7707load.lib
```

Инициализация VSHELL проста и требует всего нескольких строчек в функции main:
```cpp
...
	if(!VS_Init())	// Init VSHELL library
		return 0;

	if(!VS_Bind("../../../../input/bugs720x576x20.avi"))	// Set video sequence for playback
		return 0;

	int width =VS_GetWidth (VS_SOURCE);	
	int height=VS_GetHeight(VS_SOURCE);
	int size  =width*height;

    VS_CreateImage("Source Image", 1, width, height, VS_RGB8, 0);	// Create window for 8-bit source grayscale image
	VS_CreateImage("Sobel  Image", 2, width, height, VS_RGB8, 0);	// Create window for 8-bit result grayscale image
...
```	
Более подробную документацию на VSHELL можно найти в /deps/VSHELL/doc

Модифицируем ответную часть хост-приложения на бесконечный цикл передачи кадров в функции main

```cpp
...
while(VS_Run())	{
	VS_GetGrayData(VS_SOURCE, srcImg8);	// Get image from video stream
	VS_SetData(1, srcImg8);				// Put source image in window N1

	Connector.WriteMemBlock((unsigned*)srcImg8, srcAddr, size/4);	// Send image to shared memory of nmc 
	Connector.Sync(0);												// Barrier sync - force nmc to wait while new image is coming 
	//... wait while sobel runs on board

	unsigned t=Connector.Sync(0);									// Barrier sync - signal from nmc that sobel-filter is finished
	Connector.ReadMemBlock ((unsigned*)dstImg8, dstAddr, size/4);	// Read result image
		
	if (t==0xDEADB00F)
		VS_Text("Memory allocation error in sobel!\n");
	VS_SetData(2, dstImg8);
	VS_Text("%u clocks per frame , %d clocks per pixel, %f fps\r\n", t, t/size, 320000000.0/t );
	VS_Draw(VS_DRAW_ALL);
}
...
```	

Прим. Для работы VSHELL использует vshell.dll , необходимо убедиться, что путь к этой dll прописан в %PATH%

После запуска нажимаем кнопку "play" должен появиться следующий результат:
![Рис.1](http://i11.pixs.ru/storage/8/9/2/ScreenShot_2019353_17733892.jpg "Внешний вид оболочки VSELL и результат обработки")




