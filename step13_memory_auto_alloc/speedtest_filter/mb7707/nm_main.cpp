#include <time.h>
#include "nmplv.h"
#include <stdio.h>
#include <string.h>

#define SIZE 10240
#pragma data_section ".heap"
	long buffer0[SIZE];
#pragma data_section ".heap1"
	long buffer1[SIZE];
#pragma data_section ".heap2"
	long buffer2[SIZE];
#pragma data_section ".heap3"
	long buffer3[SIZE];
#pragma data_section ".heap4"
	long buffer4[SIZE];
#pragma data_section ".heap5"
	long buffer5[SIZE];
#pragma data_section ".heap6"
	long buffer6[SIZE];
#pragma data_section ".heap7"
	long buffer7[SIZE];

long* buffer[8]	={buffer0,buffer1,buffer2,buffer3,buffer4,buffer5,buffer6,buffer7};

#pragma data_section ".data_shared_dst.bss"
	char strSize[8];
	char strText[1024];
	
int main()
{  
	
	sprintf(strText,"Hello, it is simple text from nmc!!!");
	
	char* pText=strText;
	
	clock_t t0,t1;
	for(int src=0; src<8; src++){
		for(int dst=0; dst<8; dst++){
			t0=clock();
			nmppsMulC_8s((nm8s*)buffer[src],1,(nm8s*)buffer[dst],SIZE*8);
			//nmppsMulC_8s16s((nm8s*)buffer[src],1,(nm16s*)buffer[dst],SIZE*4);
			//nmppsMulC_16s((nm16s*)buffer[src],1,(nm16s*)buffer[dst],SIZE*4);
			//nmppsMulC_32s((nm32s*)buffer[src],1,(nm32s*)buffer[dst],SIZE*2);
			t1=clock();
			
			float t=(t1-t0)*1.0/SIZE/8;
			//t/=(SIZE*4);
			sprintf(pText,"[%d-%d]\t%.3f\n",src,dst,t);
			pText+=strlen(pText);
		}
	}
	
	int textSize=strlen(strText);
	sprintf(strSize,"%x   ",(textSize+3)/4);
	nmppsConvert_32s8s((nm32s*)strSize,(nm8s*)strSize,textSize+7+8);
	
		
	return t1-t0; 
} 

