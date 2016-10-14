## ��� 13. ����������������� ������� � �������� ������� ������ 

�� ���������� ��� �� ������������ ���������� ������ ����������, �� ����� �� ��������� ������ ������ ����� ������� ���������� ������.  
���������� ������ nmc ���� ������� �� 4 ������ ������ �� 128��. ����������� ���������� ��������� ������������ ������������� ������ � ���� ������ � ������������ 4 ������������ ������ ������.  
��������, ��� ��������� ������ ����������� ������������ vsum �������� 4 ������:
-�� ����� 0 - ���������� ������ ������
-�� ����� 1 - �������� ������� ������ 
-�� ����� 2 - ������������ ������� ������������
-�  ���� 3 - ����������� ��������� 

���� ���, ������� , �������� ������� � ������������ ������� ��������� ������� ��������� �� ������ ������, �� ��� ���� ������������ ������������������ SIMD ������ � ~1 ���� �� ��������. 


������ �� ������������ 4 ������������ �������:  **signedImgUpLine, horizontTmpUpLine, horizontOut � verticalOut**.
� � �������� �� ����� �� ���������� ������ � ��������� �����, �� � ���� ������ ��� �������� �� ��������� �� ������� ������, ��� ��������� �� ��������������. 

��������� ��������� ��� � 0-�� ����� � ������������ 3 ������� ��� ������, �������� � ������ ������� ����������� ���������� �������. 
��� ����� �������� ��� ���� ������ : pool1, pool2 , pool3 , � ����� heap1,heap2 � heap3  ��������������:
**sobel.cpp**:
```cpp
	...
	pool1= malloc32(wrapSize/2, INT_BANK1);
	pool2= malloc32(wrapSize/2, INT_BANK2);
	pool3= malloc32(wrapSize/2, INT_BANK3);
	...
```
� ����� � ���� ����� ����� �������� ������� ������ **signedImgUpLine, horizontTmpUpLine, horizontOut � verticalOut** ��� ������� , ������� ��� � �����������. 
����� � ��� ���� 4 ����������� ������� ������� �������������: **sobel_weights121, sobel_weights101,sobel_weights121v,sobel_weights101v**, ������� ����� ���������� �������� � ����� ������ ����� ������.

��������� ��� ����������  ������� ������������ , ������� � �������� ������� ������� ���, ����� ��� ������ ������ ������� ��� � ����� ������� ������������� � ������ �����, 
� � ������ ����� ������ �� �������� ���������� �� ���������� �������.
��� ����� ������� ��� �������� � ������� ����:

|[code]           |pool1[nmc_data1]   |pool2[nmc_data2] 		|pool3[nmc_data3]  	|pool4[ddr_data0]|Shared[ddr_data1] |
|:--              |:--                |:--						|:---				|---			|---				|
|nmppsSubC_8s         |**signedImgUpLine**|							|   				|   			|sourceUpLine    	|
|filter3h         |signedImgUpLine    |**horizontTmpUpLine**	|sobel_weights121   |   			|   				|
|filter3v         |sobel_weights101v  |horizontTmpUpLine   		|**horizontOut**	|   			|   				|
|nmppsAbs1_16s         |                   |**horizontAbs**     		|horizontOut   		|   			|   				|
|filter3h         |signedImgUpLine    |sobel_weights101    		|**verticalTmpUpLine**|   			|   				|
|filter3v         |**verticalOut**    |sobel_weights121v   		|verticalTmpUpLine	|   			|   				|
|nmppsAbs1_16s         |verticalOut        |                       	|**verticalAbs**	|   			|   				|
|nmppsAdd_16s         |**summ**           |horizontAbs            	|verticalAbs    	|   			|   				|
|nmppsClipConvertAddC_16s8s |summ               |vec_tbl_Diagonal_01h_G   |   				|   			|**result**			|
> ������ ������� ������� �������������� ��������


������������� ������� ������������� �� ��������� ����� ��������������� ������ � cfg-�����:
```cfg
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

��� �������� ������������ ������������� ���������� ������ ������� ����� �������� ������������� �������� �������. 
� ����������� �� ������ ����������� ������ ������ ����������� ������� ����� � init-������� .
```cpp
int CSobel::init (int Width, int Height){
	fullHeight=Height;
	// try to find maximum slice height to fit in internal memory
	for(int sliceHeight=(Height+29)/30*30; sliceHeight>=30; sliceHeight-=30){
		if (CBaseSobel::init(Width, sliceHeight))
			break;
	}
	return isReady;
}
```


### ������
� ���������� ������ ����������� �� �������� ��������� ������� �������� ��� � 30%: 
- 1516584 clocks per frame
- 3.66 clocks per pixel
- 211.00 fps




