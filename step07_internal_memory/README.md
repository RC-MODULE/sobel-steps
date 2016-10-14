## ��� 7. ����������� ��������� ��� ������ �� ���������� ������ nmc  

�� ���� ���������� ����� �� ������������ ���� �� ������� ������. � ��� ���� ������ ��� ��� ���� ����� ���� ���������� �� ���. 
������, ��������� ���������� ������ ���������� NMC ����� ����� ��������� ������������������. ��� ��� ���������� ������ ������������ ��� ��������� ���� SD �����, 
�������� ����� �����-�������, ������� ����� �������� �������� ���� �� ������ � ������� ��� ������� ����� ���������� �� ������������� ������.

```cpp
int CSobel::init (int Width, int Height){
	int sliceHeight=72;
	sliceCount =Height/sliceHeight;
	CBaseSobel::init(Width, sliceHeight);
	return isReady;
}

int CSobel::filter ( const unsigned char *source, unsigned char *result){
	
	for(int slice=0; slice<sliceCount; slice++){
		unsigned char* sliceSrcImg8= nmppsAddr_8u(source,slice*size);
		unsigned char* sliceDstImg8= nmppsAddr_8u(result,slice*size);
		CBaseSobel::filter(sliceSrcImg8, sliceDstImg8);
	}
	return true;

}
```
���������� ������ NMC ���������� 512KB � ������� �� 4 �����.
����� �������� ������������ ������ �� ���� ������ ��� �������� ���������, � �������� � �������������� ������ ����� ������� �� ������� ������.
��� ����� ��� ���������� ������� ��������� ���� 4 ��� (heap,heap1,heap2,heap3) � cfg-�����:
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


> ������� ��������,��� � 0-� ����� ��� ������� ��������� ������ ����. 
> ��� ��� ������� malloc32(malloc) ��������������� �������� �������� ������ � �������-�����: .heap .heap1 .heap2 .heap3 ,
> �� ����� ����� �������������� ������ ���� � ������ ���������� ��� ������ ���� � ������ �������� �� ������ ������, 
> �������� �������� ������������ ��������� ������ � ������� ����� � ������� �����:
```cpp
malloc32(HEAP_1|HEAP_2|HEAP_3);
```

������� ������ ������� ������� heap,heap1,heap2,heap3 � **Makefile**:
```mk
BUILDER_FLAGS    = -cmb7707brd.cfg -m  -heap=25000 -heap1=32500 -heap2=32500 -heap3=32500 -full_names -o$(TARGET) $(LIB_DIRS)
```

	
� ���������� ������ ����������� ����� ��� MC77.07 ������� �������� � 6 ���:
- 2822341 clocks per frame 
- 6.81 clocks per pixel
- 113.38 fps


������ �����, ��� � ��� ��������� �������������� ������:   
![���.1](http://savepic.su/5873135.jpg)
