#ifndef HOST_CONNECTOR_INCLUDED
#define HOST_CONNECTOR_INCLUDED

#include "stdio.h"
#define TRACE(text)		fprintf (stderr, text)
//#define TRACE(text)		printf (text)

#define HOST_CONNECTOR_RESET_ON   1
#define HOST_CONNECTOR_RESET_OFF  0


#ifndef uint32 
typedef unsigned int 	uint32;
#endif
#ifndef uint16 
typedef unsigned short 	uint16;
#endif

#ifndef uint8
typedef unsigned char 	uint8;
#endif


#ifndef MEM
#define MEM(addr)  (*((unsigned volatile*)(addr)))
#endif


class C_MemSyncData{
public:
	int host_SyncWord;		///< €чейка дл€ обмена 32р слова   ( host write-only cell  )
	int host_SyncCounter;	///< €чейка-счетчик записей        ( host write-only cell  )
	int nm_SyncWord;		///< €чейка дл€ обмена 32р         ( nm-slave write-only cell )
	int nm_SyncCounter;		///< €чейка-счетчик записей        ( nm-slave write-only cell )
	
	C_MemSyncData(){
		Reset();
	}
	
	void Reset(){
		host_SyncWord=0;	
		host_SyncCounter=0;
		nm_SyncWord=0;	
        nm_SyncCounter=0;
	}
};


class C_Connector{
public:
	
	virtual int ReadElementBlock (unsigned* dst_base, int dst_offset, unsigned src_base, int src_offset, int element_size, int count)=0;
	virtual int WriteElementBlock(unsigned* src_base, int src_offset, unsigned dst_base, int dst_offset, int element_size, int count)=0;
	
	virtual int ReadMemBlock (unsigned* dst_host_addr, unsigned src_nm_addr, int size32)=0;
	virtual int WriteMemBlock(unsigned* src_host_addr, unsigned dst_nm_addr, int size32)=0;

//	virtual int ReadWord (unsigned* dst_addr, unsigned base, int offset)=0;
//	virtual int WriteWord(unsigned* src_addr, unsigned base, int offset)=0;

	virtual void Sleep(int msecs)=0;
	virtual int Sync(int val)=0;
};



#endif

