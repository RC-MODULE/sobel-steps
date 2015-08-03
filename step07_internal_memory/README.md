## Шаг 7. Модификация программы для работы во внутренней памяти nmc  

Во всех предыдущих шагах мы обрабатывали кадр во внешней памяти. И это было удобно так как кадр можно было обработать за раз. 
Однако, используя внутреннюю память процессора NMC можно резко увеличить производительность. Так как внутренней памяти недостаточно для обработки даже SD кадра, 
создадим новый класс-потомок, который будет нарезать исходный кадр на слайсы и вызвать для каждого метод фильтрации из родительского класса.

```cpp
int CSobel::init (int Width, int Height){
	int sliceHeight=72;
	sliceCount =Height/sliceHeight;
	CBaseSobel::init(Width, sliceHeight);
	return isReady;
}

int CSobel::filter ( const unsigned char *source, unsigned char *result){
	
	for(int slice=0; slice<sliceCount; slice++){
		unsigned char* sliceSrcImg8= VEC_Addr(source,slice*size);
		unsigned char* sliceDstImg8= VEC_Addr(result,slice*size);
		CBaseSobel::filter(sliceSrcImg8, sliceDstImg8);
	}
	return true;

}
```
Внутренняя память NMC составляет 512KB и разбита на 4 банка.
Будем выделять динамическую память из этих банков для кусочной обработки, а исходный и результирующий полные кадры держать во внешней пямяти.
Для этого нам необходимо указать положение всех 4 куч (heap,heap1,heap2,heap3) в cfg-файле:
```cpp
SECTIONS
{
	.text				: in code;
	[cut]
    .heap                : in nmc_data0;
    .heap1               : in nmc_data1;
    .heap2               : in nmc_data2;
    .heap3               : in nmc_data3;
	[cut]
}	
```


> Следует отметить,что в 0-й банке как правило находятся секции кода. 
> Так как функция malloc32(malloc) последовательно пытается выделять память в секциях-кучах: .heap .heap1 .heap2 .heap3 ,
> то чтобы лучше распараллелить потоки кода и данных желательно эти секции кода и данных развести по разным банкам, 
> например запретив динамическое выделение памяти в нулевом банке с помощью маски:
```cpp
malloc32(HEAP_1|HEAP_2|HEAP_3);
```

Размеры секций зададим ключами heap,heap1,heap2,heap3 в **Makefile**:
```mk
BUILDER_FLAGS    = -cmb7707brd.cfg -m  -heap=25000 -heap1=32500 -heap2=32500 -heap3=32500 -full_names -o$(TARGET) $(LIB_DIRS)
```

	
В результате данной оптимизации имеем для MC77.07 прирост скорости в 6 раз:
- 2822341 clocks per frame 
- 6.81 clocks per pixel
- 113.38 fps


Однако видим, что у нас появились разделительные полосы:   
![Рис.1](http://savepic.su/5873135.jpg)
