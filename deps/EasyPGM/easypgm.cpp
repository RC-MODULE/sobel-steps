#include "nmplv.h"
#include "stdio.h"


struct s_pgm_header{
	int width;
	int height;
	int max_gray;
	unsigned* data;
	unsigned  disp;
	int header_length;
};

int read_pgm_header(void* addr32, s_pgm_header* header){
	char str[16];
	char symbol;
	int  pos=0;
	nm8u* addr=(nm8u*)addr32;
	symbol=VEC_GetVal(addr,pos++); if (symbol!='P') return 0;
	symbol=VEC_GetVal(addr,pos++); if (symbol!='5') return 10;
	symbol=VEC_GetVal(addr,pos++); if (symbol!=0x0A) return 20;
	
	// skip comment
	do {
		symbol=VEC_GetVal(addr,pos++); 
		if (pos>32)	return 30;
	}while (symbol!=0x0A);
	
	int len=0;
	// read width
	do {
		symbol=VEC_GetVal(addr,pos++); 
		str[len++]=symbol;
		if (len>32)	return 40;
	} while (symbol!=' ');
	str[len-1]=0;
	header->width=atoi(str);
	
	// read height
	len=0;
	do {
		symbol=VEC_GetVal(addr,pos++); 
		str[len++]=symbol;
		if (len>64)	return 51;
	} while (symbol!=0x0A);
	str[len-1]=0;
	header->height=atoi(str);
	
	
	// read max gray
	len=0;
	do {
		symbol=VEC_GetVal(addr,pos++); 
		str[len++]=symbol;
		if (len>32)	return 60;
	}while (symbol!=0x0A);
	str[len-1]=0;
	header->max_gray=atoi(str);
	//return header->max_gray;
	
	header->data=(unsigned*)addr+pos/4;
	header->disp=pos%4;
	header->header_length=pos;
	return pos;
	
}