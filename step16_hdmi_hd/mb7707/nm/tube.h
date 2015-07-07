#ifndef __TUBE_H__
#define __TUBE_H__

/*
void tube_msg(const char* msg);
void tube_hex(unsigned x);
void tube_str(const char* msg);
void tube_die();
*/


#define  tube_msg(msg) 
#define  tube_hex(x) 
#define  tube_str(msg) 
#define  tube_die() 


#define TUBE_PRINTSTR           0x000
#define TUBE_PRINTDEC           0x004
#define TUBE_PRINTHEX           0x008


#define TUBE_BASE 0x20038000

asm ("TUBE_BASE = 0x20038000");

// This macros inserts tube messaging as inline "C" code 
// Use this macros in   "C" interrupt handlers instead of usual tube_msg

#define INLINE_TUBE_MSG(MSG) 								\
{															\
	const char msg[]={MSG"\r\r\r\r"};								\
	char* p=msg;											\
	asm volatile ("PUSH {R4,R5}"); 							\
	asm volatile ("LDR 	R5 ,=TUBE_BASE"); 					\
	while(1){												\
		asm volatile ("LDR 	R4 ,%0"::"m"(*(int*)p));		\
		asm volatile ("REV 	R4, R4");						\
		asm volatile ("STR  R4, [R5]");						\
		if ((*(p+3))==13)									\
			break;											\
		p+=4;												\
	}														\
	asm volatile ("POP {R4,R5}"); 							\
}



#define INLINE_TUBE_HEX(hex) 	\
{	int x=hex;					\
	char tbl[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};\
	char str[]="\r\r\r\r\r\r\r\r\r\r\r\r"; 	\
	int s;						\
	str[8]=0;					\
	for(s=7;s>=0;s--){		\
		str[s]=tbl[x&0xF];		\
		x>>=4;					\
	}							\
	char* p=str;											\
	asm volatile ("PUSH {R4,R5}"); 							\
	asm volatile ("LDR 	R5 ,=TUBE_BASE"); 					\
	while(1){												\
		asm volatile ("LDR 	R4 ,%0"::"m"(*(int*)p));		\
		asm volatile ("REV 	R4, R4");						\
		asm volatile ("STR  R4, [R5]");						\
		if ((*(p+3))==13)									\
			break;											\
		p+=4;												\
	}														\
	asm volatile ("POP {R4,R5}"); 							\
}
 

#ifdef  CTUBE_ON
#define TUBE_MSG(msg) tube_msg(msg)
#define TUBE_HEX(hex) tube_hex(hex)
#endif

#ifdef CTUBE_OFF
#define TUBE_MSG(msg) 
#define TUBE_HEX(hex)
#endif
		
#endif