## ��� 11. ����������� ������� ��������� �������������� ������ 

��� ��������� �������������� ������ �� ������������ ������ nmppsFIRInitAlloc_8s16s(&pFIRState121,sobelH,3); � ������������� �������� ����. 
��������������� ������������ ������� ������ ��� ��� ��������� ��� ��������� ������� ��������,
������ ���� �� ��������������� - �������� ��������������. 
��������� �� ���������� ������������������ ������� **filter3h** � ������������� �������� ���� ������ 3 � ������� ��� ���� ������: 

������� �� ������ ������ **nmppsFIR_8s16s** **filter3h**
```cpp
	...
	// here was: nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState121);
	filter3h ( signedImgUpLine, horizontTmpUpLine, frameSize, sobel_weights121);
	...
	// here was: nmppsFIR_8s16s(signedImgUpLine, horizontTmpUpLine, frameSize, pFIRState101);
    filter3h(signedImgUpLine, horizontTmpUpLine, frameSize, sobel_weights101);
	...
```

� ���������� ������ ����������� �������� ������� ������������������ 7%: 
- 2176832 clocks per frame
- 5.25 clocks per pixel
- 147.00 fps








