#include "mc5103load.h"
#define TRACE(text)		fprintf (stderr, text)

class C_PC_Connector_mc5103{
	PL_Access *access;
public:
	int Sync(int val){
		int ret;
		PL_Sync(access,val,&ret);
		return ret;
	}
	bool isConnected(){
		return (access!=0);
	}
	C_PC_Connector_mc5103(char* absfile=0){
		struct PL_Board *board;
		int boardCount;
		access=0;
		PL_Word Length = 0;
		
		PL_Word *Buffer = 0;
		PL_Word AddrLoad = 0;

		TRACE ("Connection to board...");
		if (PL_GetBoardCount(&boardCount))	{
			TRACE( "ERROR: Can't open driver.\n");
			//return  (1);
		}

		if (boardCount < 1)	{
			TRACE( "ERROR: Can't find board.\n");
			//return  (1);
		}

		if (PL_GetBoardDesc(0, &board))	{
			TRACE( "ERROR: Can't open board 0 \n");
			//return  (1);
		}

		if (absfile){
			if (PL_ResetBoard(board)) {
				TRACE( "ERROR: Can't reset board  0 .\n");
				//return  (1);
			}
			for (int i=0; i<10; i++)
				PL_ResetBoard(board);
		}

		if (PL_GetAccess(board, 0, &access)){
			TRACE( "ERROR: Can't access processor  0 on board  0  \n");
			//return  (1);
		}
		
		if (absfile) 
			if (PL_LoadProgramFile(access, absfile)){
				access=0;
				TRACE( ": : ERROR: Can't load program into board.\n");
				//return  (1);
			}

		TRACE ("OK!\n");
		//return 0;
	}
		

	int ReadMemBlock (unsigned* dst_host_addr, unsigned src_nm_addr, int size32){
		return PL_ReadMemBlock(access, (PL_Word*)dst_host_addr, src_nm_addr, size32);
	}
	int WriteMemBlock(unsigned* src_host_addr, unsigned dst_nm_addr, int size32){
		return PL_WriteMemBlock(access, (PL_Word*)src_host_addr, dst_nm_addr, size32);
	}
};