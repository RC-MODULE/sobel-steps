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
0-й банк мы будем использовать для размещения кода , а остальные три для данных. 
Чтобы динамическая память для обработки выделялась из этих трех банков , а исходный и результирующий располагались во внешней пямяти, 
нам необходимо указать положение всех 4 куч (heap,heap1,heap2,heap3) в cfg-файле:

```cpp
SECTIONS
{
	.text				: in code;
	[cut]
	.heap				: in ddr_data0;
	.heap1				: in nmc_data1;
	.heap2				: in nmc_data2;
	.heap3				: in nmc_data3;
	[cut]
}	
```

Размеры секций зададим ключами heap,heap1,heap2,heap3 в **Makefile**:
```mk
BUILDER_FLAGS    = -cmb7707brd.cfg -m  -heap=1000000 -heap1=32000 -heap2=30000 -heap3=32000 -full_names -o$(TARGET) $(LIB_DIRS)
```

	
В результате данной оптимизации имеем для MC77.07
- 17230136 clocks per frame , 
- 41.55 clocks per pixel, 
- 18.57 fps

Однако видим что у нас появились разделительные полосы: 


![Рис.1](http://savepic.su/5873135.jpg"Внешний вид оболочки VSELL и результат обработки")
