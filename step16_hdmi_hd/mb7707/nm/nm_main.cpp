#include "mb7707_load.h"
#include "sobel.h"
#include "malloc32.h"
#include "vdu.h"
#include "sleep.h"
#include <time.h>

#define ARM2NM(addr)((int*)(((unsigned)addr)>>2))
#define NM2ARM(addr)((int*)(((unsigned)addr)*4))

int *crt;
int rowsize;
char hex8buf[11];
char *hex8( int x)
{ int i,j,k;
for (i=0; i<8; i++)
{ j=x & 15;
k=(j>9)? j+=87 : j+=48;
hex8buf[7-i]=(char)k;
x>>=4;
}
hex8buf[8]=0;
return hex8buf;
}

int main(int argc, char *argv[])
{  
	
	
	//---------- start nm program ------------
	int fromHost=ncl_hostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = ncl_hostSync(0);
	int height= ncl_hostSync(1);
	int size  = width*height;
	//-------------------------------
	// Init VDU
	unsigned Y0=0xC0000000; 
	unsigned Y1=0xC0000000; 
	VEC_Fill((nm8u*) ARM2NM(0xC0000000), 128, width*height*2);
	VEC_Fill((nm8u*) ARM2NM(0xC0000000), 255, width*height/2);
	Start_VDU(width,height, Y0, Y1,0 ) ;


	// Allocate memory for 8-bit source and result images in shared memory
	
	nm8u* dst=(nm8u*)ARM2NM(0xC0000000);	// VDU DDR
	int frames=0;// number of loaded frames in DDR
	int maxFrames=128*1024*1024/size;
	nm8u* video=(nm8u*)ARM2NM(0x40000000);	// VUDEO-STREAM DDR
	

	CSobel sobel(width, height);
	
	// Check memory allocation
	if (sobel.isReady==false){
		ncl_hostSync(0xDEADB00F);	// send error to host
		return -1;
	}
	else 
		ncl_hostSync(0x600DB00F);	// send ok to host
		
	ncl_hostSync((int)&frames);		// Send frame addr to host
	ncl_hostSync((int)video);		// Send video buffer addr to host
		
	
	clock_t t0,t1;
	int counter=0;				// frame counter
	while(1){					// Start sobel in loop 
		for(int i=0; i<MIN(maxFrames-1,frames); i++){
			nm8u* src=VEC_Addr(video,i*size);
			t0=clock();
			sobel.filter(src,dst);
			sleep(1000);
			t1=clock();
		}
		counter++;
	}

	return 1; 
} 

