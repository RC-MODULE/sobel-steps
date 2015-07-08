#include "time.h"
inline void sleep(clock_t msec ){
		#ifdef __NM__ 
		clock_t dt=msec*(CLOCKS_PER_SEC/1000);	
		clock_t t0=clock();
		while(clock()-t0<dt){
			__asm{
				rep 32 with vfalse;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 with afifo and afifo;
				rep 32 [ar7] = afifo;
			}
		}
			
		#else
			::Sleep(msec);
		#endif
	}