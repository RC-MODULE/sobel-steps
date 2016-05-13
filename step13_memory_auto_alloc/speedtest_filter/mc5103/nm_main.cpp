#include <time.h>
#include "nmplv.h"
#include <stdio.h>
#include "nmpls.h"
#include "nmplm.h"

#define SIZE 10240
#pragma data_section ".heap"
	long buffer0[SIZE];
	long state0[128];
#pragma data_section ".heap1"
	long buffer1[SIZE];
	long state1[128];
#pragma data_section ".heap2"
	long buffer2[SIZE];
	long state2[128];
#pragma data_section ".heap3"
	long buffer3[SIZE];
	long state3[128];
#pragma data_section ".heap4"
	long buffer4[SIZE];
	long state4[128];
#pragma data_section ".heap5"
	long buffer5[SIZE];
	long state5[128];

long* buffer[6]	= {buffer0,buffer1,buffer2,buffer3,buffer4,buffer5};
long* state[6]  = {state0,state1,state2,state3,state4,state5};

#define LEN 10/2
int main()
{  
		
	NmppsFIRState* pState;
	int pTaps[]={1,2,3,4,5,6,7,8,9,10};
	
	clock_t t0,t1;
	for(int src=0; src<6; src++){
		for(int src2=0; src2<6; src2++){		
			for(int dst=0; dst<6; dst++){
			
				//pState=state[src2];
				//nmppsFIRInit_8s16s(pState, pTaps, 3);
			
				t0=clock();
				//nmppsFIR_8s16s((nm8s*)buffer[src], (nm16s*)buffer[dst], SIZE*4, pState);
				//nmppsAdd_64s((nm64s*)buffer[src], (nm64s*)buffer[src2],  (nm64s*)buffer[dst], SIZE*8);
				nmppsAdd_8s((nm8s*)buffer[src], (nm8s*)buffer[src2],  (nm8s*)buffer[dst], SIZE*8);
				//nmppsSub_32s((nm32s*)buffer[src], (nm32s*)buffer[src2],  (nm32s*)buffer[dst], SIZE);
				//nmppsSubC_32s((nm32s*)buffer[src], 1,  (nm32s*)buffer[dst], SIZE);
				//nmppmMul_mm_8s16s((nm8s*)buffer[src],128,128,(nm16s*)buffer[src2], (nm16s*)buffer[dst], 128);
				t1=clock();
			
				float t=(t1-t0)*1.0/(SIZE*8);
			
				//printf("[%d-%d]\t%.3f\n",src,dst,t);
				printf("[%d-%d-%d]\t%.3f\n",src,src2,dst,t);
			}
		}
	}
	
			
	
	
	
	
	return t1-t0; 
} 

