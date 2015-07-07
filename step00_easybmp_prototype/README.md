## Шаг 0. Прототипирование 

У нас есть математическая форма фильтра Собеля, реализуем ее прототип для хоста 
Согласно определению оператора Собеля имеем следущий код sobel.cpp: 
```cpp
short sobelH[9]={
		1, 2, 1,
		0, 0, 0,
		-1,-2,-1};

short sobelV[9]={
		1, 0, -1,
		2, 0, -2,
		1, 0, -1};

void sobel( const unsigned char *source, unsigned char *result, int width, int height)
{
	int j,sum1,sum2;
	const unsigned char *line1, *line2, *line3;
	line1 = source- width -1;
	line2 = line1 + width;
	line3 = line2 + width;
	const unsigned char* end=source+width*height;
	
	for(j=0; j<height*width; j++){
		if (line1>source && (line3+2)<end){
			sum1  = line1[0]*sobelH[0] + line1[1]*sobelH[1] + line1[2]*sobelH[2] +
					line2[0]*sobelH[3] + line2[1]*sobelH[4] + line2[2]*sobelH[5] + 
					line3[0]*sobelH[6] + line3[1]*sobelH[7] + line3[2]*sobelH[8] ;
			
			sum2  = line1[0]*sobelV[0] + line1[1]*sobelV[1] + line1[2]*sobelV[2] +
					line2[0]*sobelV[3] + line2[1]*sobelV[4] + line2[2]*sobelV[5] + 
					line3[0]*sobelV[6] + line3[1]*sobelV[7] + line3[2]*sobelV[8] ;
			
			sum1=(sum1>0)?sum1:-sum1;
			sum2=(sum2>0)?sum2:-sum2;
			*result=MIN(255,sum1+sum2);
		}
		result++;
		line1++;
        line2++;
        line3++;
	}
}
```

Для работы с bmp-изображениями используем библиотеку EasyBMP.
Запуск программы осуществляется командой 
```sh 
make run 
```
Результатом программы должно сфоримроваться изображение dst.bmp
