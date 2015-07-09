#include <time.h>
#include "mc5103_load.h"
#include "sobel.h"
#include "malloc32.h"
#include "nmplv.h"


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

int main(int argc, char *argv[])
{  
	
	s_pgm_header pgm_header;
	read_pgm_header((unsigned*)0x10004000,&pgm_header);
	// Get image parameters from host
	int width = pgm_header.width;
	int height= pgm_header.height;
	int size  = width*height;

	// Allocate memory for 8-bit source and result images in shared memory
	int* src=(int*)malloc32(size/4);		
	int* dst=(int*)malloc32(size/4); 
	// Check memory allocation
	if (src ==0 || dst==0) return -1;
		
	VEC_Copyua((nm8s*)pgm_header.data, pgm_header.disp, (nm8s*) src, size);
	
	clock_t t0=clock();
	sobel((unsigned char*)src,(unsigned char*)dst,width,height);
	clock_t t1=clock();

	for(int i=0; i<size; i++){
		int pix=VEC_GetVal((nm8u*)dst,i);
		VEC_SetVal((nm8u*)pgm_header.data, pgm_header.disp+i, pix);
	}

	free32(src);
	free32(dst);
	return 1; 
} 

