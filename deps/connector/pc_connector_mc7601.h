#include "MC7601_LL_Host.h"

#include "connector.h"
#include "crtdbg.h"
#include "windows.h"

const unsigned int CORE_NUMBER = 0;
const int IP_ADDRESS = 0x0201A8C0; // 192.168.1.2


class C_PC_Connector_mc7601: public C_Connector{
public:
	WR_Access *access;
	C_PC_Connector_mc7601(char* absfile=0){
		WR_Board *board;
		WR_channel_conf conf;
		int boardCount;
		WR_Word Length = 0;

		WR_Word *Buffer = 0;
		WR_Word AddrLoad = 0;

		WR_SetChannel(conf, ANMETHERNET, IP_ADDRESS, 6901);
		
		//TRACE ("Connection to board...");
	
		if (WR_GetBoardDesc(&conf, &board) != WR_OK)
		{
			//TRACE("ERROR: Can't open board!\n");
			//return (1);
		}

		
		//if (absfile) 
		if (WR_GetAccess(board, CORE_NUMBER, &access) != WR_OK)
		{
			//TRACE( "ERROR: Can't access processor  0 on board  0  \n");
			//return  (1);
		}

		if (WR_LoadInitCode(access) != WR_OK)
		{
			//TRACE ("ERROR: Can't load init code!\n");
			//return  (1);
		}

		if (WR_LoadProgramFile(access, absfile, 0xFFFFFFFF) != WR_OK)
		{
			//cout << NM_PART_FILE_NAME << " :: ERROR: Can't load program!\n";
			//return  (1);
		}

		//return 0;

	}
	int Sync(int val){
		WR_Word ret;
		WR_Sync(access,0xFFFFFFFF,val,&ret);
		return ret;
	}
	// int Handshake();  Derivated from C_Syncro
	//{
	//	static int counter=0;
	//	int ret=Sync(SYNCRO_HANDSHAKE+counter);
	//	_ASSERTE(ret==SYNCRO_HANDSHAKE+counter);
	//	return (ret==SYNCRO_HANDSHAKE+counter);
	//}
	//----------------------------------------------------------------------------------------------------
	//int ReadElementBlock (unsigned* dst_base, int dst_offset, unsigned src_base, int src_offset, int element_size, int count){return 0;}//=0;
	int ReadElementBlock (unsigned* dst_base, int dst_offset, unsigned src_base, int src_offset, int element_size, int count){
		_ASSERTE((dst_offset*element_size)%4==0);
		_ASSERTE((src_offset*element_size)%4==0);
		//_ASSERTE((count     *element_size)%4==0);

		// округляем общий размер блока вниз до кратного 4 байтам
		if (element_size%4){
			int n=count*element_size;	// точный размер блока для чтения в байтах
			while (n%4){
				n-=element_size;
				count--;
			}
		}


		//memcpy((void*)((uint32)dst_base+dst_offset*element_size), (void*)(src_base+src_offset*element_size), count*element_size);
		WR_ReadMemBlock(access, 
			(WR_Word*)(dst_base+(dst_offset*element_size>>2)), 
			src_base+(src_offset*element_size>>2),
			count*element_size>>2);

		return count;
	}


	int WriteElementBlock(unsigned* src_base, int src_offset, unsigned dst_base, int dst_offset, int element_size, int count){
		_ASSERTE((dst_offset*element_size)%4==0);
		_ASSERTE((src_offset*element_size)%4==0);
		//_ASSERTE((count     *element_size)%4==0);

		// округляем общий размер блока вниз до кратного 4 байтам
		if (element_size%4){
			int n=count*element_size;	// точный размер блока для записи в байтах
			while (n%4){
				n-=element_size;
				count--;
			}
		}

		//memcpy((void*)(dst_base+dst_offset*element_size), (void*)((uint32)src_base+src_offset*element_size), count*element_size);
		WR_WriteMemBlock(access, 
			(WR_Word*)(src_base+(src_offset*element_size>>2)),
			dst_base+(dst_offset*element_size>>2),
			count*element_size>>2);
		return count;
	}

	//----------------------------------------------------------------------------------------------------

	int ReadMemBlock(unsigned* dst_host_addr, unsigned src_nm_addr, int size){
		return WR_ReadMemBlock(access, (WR_Word*)dst_host_addr, src_nm_addr, size);
	}
	int WriteMemBlock(unsigned* src_host_addr, unsigned dst_nm_addr, int size32){
		return WR_WriteMemBlock(access, (WR_Word*)src_host_addr, dst_nm_addr, size32);
	}

	//----------------------------------------------------------------------------------------------------

	//virtual unsigned OffsetAddr(unsigned* pBase, int nOffset){
	//		unsigned nBase=(unsigned)pBase;
	//		return  (nBase+nOffset);
	//}

	//int ReadWord (unsigned* dst_addr, unsigned base, int offset){
	//	return WR_ReadMemBlock(access, (WR_Word*)dst_addr, base+offset, 1);
	//}

	//int WriteWord(unsigned* src_addr, unsigned base, int offset){
	//	return WR_WriteMemBlock(access, (WR_Word*)src_addr, base+offset, 1);
	//}

	void Sleep(int msecs){
		::Sleep(msecs);
	}

};