#include "nmplv.h"
#include "stdio.h"
#include "easypgm.h"
#include <string.h>
#include <stdlib.h>

int save_pgm_header(void* header, int width, int height, char* copyright)
{
	char width_str[8];
	char height_str[8];
	nm8u* addr=(nm8u*)header;
	int pos=0;
	// put PGM-magic number  into header
	VEC_SetVal(addr,pos++,'P'); 
	VEC_SetVal(addr,pos++,'5'); 
	VEC_SetVal(addr,pos++,0x0A);
	VEC_SetVal(addr,pos++,'#');
	
	// convert with and height to text
	sprintf(width_str,"%d",width);
	sprintf(height_str,"%d",height);
	int width_len =strlen(width_str);
	int height_len=strlen(height_str);

	// put  copyright cutted text to fit header in 32 bytes 
	int copyright_len=strlen(copyright);
	int copyright_max_len=64-4-1-width_len-1-height_len-1-4;
	if (copyright_len>copyright_max_len)
		copyright_len=copyright_max_len;
	for(int i=0; i<copyright_len;i++ )
		VEC_SetVal(addr,pos++,copyright[i]); 
	for(int i=0; i<copyright_max_len-copyright_len;i++ )
		VEC_SetVal(addr,pos++,' '); 
	VEC_SetVal(addr,pos++,0x0A);
	
	// put  width into header
	for (int i=0; i<width_len; i++) 
		VEC_SetVal(addr,pos++,width_str[i]); 
	VEC_SetVal(addr,pos++,' ');

	// put  height into header
	for (int i=0; i<height_len; i++) 
		VEC_SetVal(addr,pos++,height_str[i]); 
	VEC_SetVal(addr,pos++,0x0A);
	
	// put max gray into header
	VEC_SetVal(addr,pos++,'2');
	VEC_SetVal(addr,pos++,'5');
	VEC_SetVal(addr,pos++,'5');
	VEC_SetVal(addr,pos++,0x0A);

	return pos;
}

int read_pgm_header(void* header, int& width, int& height){
	char str[16];
	char symbol;
	int  pos=0;
	nm8u* addr=(nm8u*)header;
	
	
	symbol=VEC_GetVal(addr,pos++); if (symbol!='P')  return 0;
	symbol=VEC_GetVal(addr,pos++); if (symbol!='5')  return 0;
	symbol=VEC_GetVal(addr,pos++); if (symbol!=0x0A) return 0;
	
	
	// skip comment
	do {
		symbol=VEC_GetVal(addr,pos++); 
		if (pos>32)	return 0;
	}while (symbol!=0x0A);
	
	int len=0;
	// read width
	do {
		symbol=VEC_GetVal(addr,pos++); 
		str[len++]=symbol;
		if (len>32)	return 0;
	} while (symbol!=' ');
	str[len-1]=0;
	width=atoi(str);
	
	// read height
	len=0;
	do {
		symbol=VEC_GetVal(addr,pos++); 
		str[len++]=symbol;
		if (len>64)	return 0;
	} while (symbol!=0x0A);
	str[len-1]=0;
	height=atoi(str);
	
	
	// read max gray
	len=0;
	do {
		symbol=VEC_GetVal(addr,pos++); 
		str[len++]=symbol;
		if (len>32)	return 0;
	}while (symbol!=0x0A);
	str[len-1]=0;
	int max_gray=atoi(str);
	//return header->max_gray;
	
	//*data=(long*)VEC_Addr(addr,pos/4);
	//data_byte_disp=pos%4;
	return pos;
	
}