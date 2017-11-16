#include "mb7707_load.h"
#include "sobel.h"
#include "malloc32.h"
#include "vdu.h"
#include "sleep.h"
#include <time.h>
#include <nmpp.h>
#include <nmpli.h>
#include <stdio.h>

#define ARM2NM(addr)((int*)(((unsigned)addr)>>2))
#define NM2ARM(addr)((int*)(((unsigned)addr)*4))

int frames=10;// number of loaded frames in DDR

int main()
{  
	// Init VDU
	unsigned Y0=0xC0000000; 
	unsigned Y1=0xC0000000; 
	nmppsSet_8u((nm8u*) ARM2NM(0xC0000000), 128, 720*576*2);
	nmppsSet_8u((nm8u*) ARM2NM(0xC0000000), 255, 720*576/2);
	Start_VDU_SD( Y0, Y1) ;
	
	
	//---------- start nm program ------------
	int fromHost=ncl_hostSync(0xC0DE6406);		// send handshake to host
	if (fromHost!=0xC0DE0086){					// get  handshake from host
		return -1;
	}

	// Get image parameters from host
	int width = ncl_hostSync(0);
	int height= ncl_hostSync(1);
	int size  = width*height;

// Allocate memory for 8-bit source and result images in shared memory
	
	nm8u* dst=(nm8u*)ARM2NM(0xC0000000);	// VDU DDR
	
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
	char str[128];
	int counter=0;				// frame counter
	while(1){					// Start sobel in loop 
		for(int i=0; i<MIN(maxFrames-1,frames); i++){
			nm8u* src=nmppsAddr_8u(video,i*size);
			t0=clock();
			//sobel.filter(src,dst);
			nmppsCopy_8u(src,dst,size);
			t1=clock();
			unsigned t=t1-t0;
			sprintf(str,"%d clocks per frame, %.2f clocks per pixel, %.2f fps", t, 1.0*t/size, 320000000.0/t);
			IMG_Print8x15( str, dst, width, 10, 10 , 255, 0);
			sleep(1000);
		}
		counter++;
	}

	return 1; 
} 

