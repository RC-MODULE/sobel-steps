#include <time.h>
#include "nmplv.h"
#include <stdio.h>
#include "nmpls.h"
#include "nmplm.h"

#define SIZE 65000/4
#pragma data_section ".heap"
	long buffer0[SIZE/2];
//	long state0[128];
#pragma data_section ".heap1"
	long buffer1[SIZE];
//	long state1[128];
#pragma data_section ".heap2"
	long buffer2[SIZE];
//	long state2[128];
#pragma data_section ".heap3"
	long buffer3[SIZE];
//	long state3[128];
#pragma data_section ".heap4"
	long buffer4[SIZE];
//	long state4[128];
#pragma data_section ".heap5"
	long buffer5[SIZE];
//	long state5[128];

long* buffer[6]	= {buffer0,buffer1,buffer2,buffer3,buffer4,buffer5};
//long* state[6]  = {state0,state1,state2,state3,state4,state5};

#define LEN 10/2
int main()
{  
		
	NmppsFIRState* pState=buffer3;
	int pTaps[]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	
	clock_t t0,t1;
	//pState=buffer3;
	
	nmppsSet_8s((nm8s*)buffer1,1,SIZE*4);
	
	for(int size=8; size<SIZE*4; size+=8)
	{
		nmppsFIRInit_8s16s(pState, pTaps,9);
		t0=clock();
		nmppsFIR_8s16s((nm8s*)buffer1, (nm16s*)buffer2, size, pState);
		t1=clock();
		float t_000=(t1-t0)*1.0/(size);
		
		
		nmppsFIRInit_8s16s(pState, pTaps,13);
		t0=clock();
		nmppsFIR_8s16s((nm8s*)buffer1, (nm16s*)buffer2, size, pState);
		t1=clock();
		float t_00=(t1-t0)*1.0/(size);
		
		nmppsFIRInit_8s16s(pState, pTaps, 19);
		t0=clock();
		nmppsFIR_8s16s((nm8s*)buffer1, (nm16s*)buffer2, size, pState);
		t1=clock();
		float t_0=(t1-t0)*1.0/(size);
		
		t0=clock();
		nmppsAdd_8s((nm8s*)buffer1, (nm8s*)buffer2,  (nm8s*)buffer3, size);
		t1=clock();
		float t_1=(t1-t0)*1.0/(size);
		
		t0=clock();
		nmppsMulC_8s((nm8s*)buffer1, 1,  (nm8s*)buffer2, size);
		t1=clock();
		float t_2=(t1-t0)*1.0/(size);
		
			
		printf("%d\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n",size,t_000,t_00,t_0,t_1,t_2);
	}
	
			
	
	
	
	
	return t1-t0; 
} 

