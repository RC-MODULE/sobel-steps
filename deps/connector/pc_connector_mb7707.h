#include "mb7707load.h"
#include "stdio.h"
#define TRACE(text)		fprintf (stderr, text)

#define PL341_MEMC_STATUS             0x000
#define PL341_MEMC_CMD                0x004
#define PL341_DIRECT_CMD              0x008
#define PL341_MEMORY_CFG              0x00C 
#define PL341_REFRESH_PRD             0x010
#define PL341_CAS_LATENCY             0x014
#define PL341_WRITE_LATENCY           0x018
#define PL341_T_MRD                   0x01C
#define PL341_T_RAS                   0x020
#define PL341_T_RC                    0x024
#define PL341_T_RCD                   0x028
#define PL341_T_RFC                   0x02C
#define PL341_T_RP                    0x030
#define PL341_T_RRD                   0x034
#define PL341_T_WR                    0x038
#define PL341_T_WTR                   0x03C
#define PL341_T_XP                    0x040
#define PL341_T_XSR                   0x044
#define PL341_T_ESR                   0x048
#define PL341_MEMORY_CFG2             0x04C
#define PL341_MEMORY_CFG3             0x050
#define PL341_T_FAW                   0x054
#define PL341_TRD_EN                  0x05C


#define PL341_CHIP_0_CFG              0X200
#define PL341_CHIP_1_CFG              0X204
#define PL341_CHIP_2_CFG              0X208
#define PL341_CHIP_3_CFG              0X20C

#define EM0_Based				      0x40000000
#define EM1_Based				      0xC0000000

#define DMC0_APB_Based                0x20032000
#define DMC1_APB_Based                0x20031000

#define DDR_INITED 2
#define DDR_NOT_INITED 1



inline unsigned ARM2NM (unsigned arm_location){
	//	if (arm_location<0x40000000)
	//		return (((arm_location)>>2)-0x50000);
	//	else 
	return (arm_location>>2);
}

#define READ_MEM(addr,val)   PL_ReadMemBlock(access, &val, ARM2NM(addr),1)
#define WRITE_MEM(addr,val)  {PL_Word x=val; PL_WriteMemBlock(access, &x, ARM2NM(addr),1);}

volatile int DDR_EM0_Inited=DDR_NOT_INITED;		
volatile int DDR_EM1_Inited=DDR_NOT_INITED;



class C_PC_Connector_mb7707{
	
public:
	PL_Access *access;
	int Sync(int val){
		PL_Word ret;
		PL_Sync(access,val,&ret);
		return ret;
		
	}
	// 203351 
	bool isConnected(){
		return (access!=0);
	}
	C_PC_Connector_mb7707(unsigned char* mac_address,char* absfile=0){
		struct PL_Board *board;
		int boardCount;
		access=0;
		PL_Word Length = 0;

		PL_Word *Buffer = 0;
		PL_Word AddrLoad = 0;

		TRACE ("Connection to board...");
		if (PL_GetBoardDesc(mac_address, &board) != PL_OK)
		{
			TRACE( "ERROR: Can't open driver.\n");
			//return  (1);
		}

		//if (PL_ResetBoard(board)) {
		//	TRACE( "ERROR: Can't reset board  0 .\n");
		//	return  (1);
		//}
		for (int i=0 ; i<100; i++){
			if (PL_GetAccess(board, 0, &access)==0){
				break;
			}
			//TRACE( "ERROR: Can't access processor  0 on board  0  \n");
			//return  (1);
		}

		PL_Word val;
		int err=PL_ReadMemBlock(access, &val, (0x2003c050)/4,1);


		Init_DDR_EM0();
		Init_DDR_EM1();
		
		WRITE_MEM(EM0_Based,0xBABADEDA);
		PL_Word t;
		READ_MEM(EM0_Based,t);
		//_ASSERTE(t==0xBABADEDA);

		//int* buf=new int [1024*1024*2];
		//PL_WriteMemBlock(access, (PL_Word*)buf, (EM0_Based)/4,1024*1024*2);


		if (PL_LoadInitCode(access) != PL_OK)
		{
			TRACE( "ERROR: Can't load init code!\n");
			//return  (1);
		}

	

		if (PL_LoadProgramFile(access, absfile)){
			access=0;
			TRACE( "ERROR: Can't load program into board.\n");
			//return  (1);
		}

		TRACE ("OK!\n");

		//return 0;
	}

	void Init_DDR_EM0(){

		if (DDR_EM0_Inited==DDR_NOT_INITED){
			PL_Word t;
			WRITE_MEM(0x2003c050,0x1c); //DDR PHY ODT ON
			PL_Word x; 
		//	int r=PL_WriteMemBlock(access, &x, ARM2NM(0x2003c050),1);

			//tube_msg("INIT DDR EM0 ...");
			
			READ_MEM(0x2003c050,t); //DDR PHY ODT ON


			INIT_DDR_EMX(DMC0_APB_Based);
			DDR_EM0_Inited=DDR_INITED;
		}


	}



	void Init_DDR_EM1(){

		if (DDR_EM1_Inited==DDR_NOT_INITED){
			WRITE_MEM(0x2003c064,0x1c); //DDR PHY ODT ON

			PL_Word t;
			READ_MEM(0x2003c064,t); //DDR PHY ODT ON

			//tube_msg("INIT DDR EM1 ...");
			INIT_DDR_EMX(DMC1_APB_Based);
			DDR_EM1_Inited=DDR_INITED;
		}

	}

	void INIT_DDR_EMX(unsigned DMCX_APB_Based){
		PL_Word v;
		int i;
		volatile static unsigned PL341_Direct_Cmd[]={
			0x000c0000,    //nop
			0x00000000,    //precharge
			0x00040000,    //autorefresh
			0x00040000,    //autorefresh
			0x00080852,    //modereg 0
			0x00090004,    //modereg 1 - ODT 75
		};

		WRITE_MEM(DMCX_APB_Based+PL341_MEMC_CMD,0x00000003);
		//while ((MEM(DMCX_APB_Based+PL341_MEMC_STATUS)&0x3) != 0x2) {}

		WRITE_MEM(DMCX_APB_Based+PL341_MEMC_CMD,0x00000004);
		
		do {
			READ_MEM(DMCX_APB_Based+PL341_MEMC_STATUS,v);
				
		} while (v&0x3!= 0x0);

		
		READ_MEM(DMCX_APB_Based+PL341_MEMC_STATUS,v);
		WRITE_MEM(0x180200,v);

		WRITE_MEM(DMCX_APB_Based+PL341_REFRESH_PRD,0x00000a28); //

		WRITE_MEM(DMCX_APB_Based+PL341_CAS_LATENCY,0x0000000a); //CAS=4

		WRITE_MEM(DMCX_APB_Based+PL341_TRD_EN,0x00000003);

		// tCK=1/324 MHz = 0.003086 * 10^-6 = 3.086 ns= 3 ns
		// tACLK = 1/162= 0.00617 * 10^-6 = 6.17 ns = 6 ns
		WRITE_MEM(DMCX_APB_Based+PL341_T_RAS,0x0000000F); // tRAS = 45 ns / tCK = 15 = 0xF
		WRITE_MEM(DMCX_APB_Based+PL341_T_RC ,0x00000014);  // tRC  = 60 ns / tCK = 20 = 0x14
		WRITE_MEM(DMCX_APB_Based+PL341_T_RCD,0x00000305); // tRCD = 15 ns / tCK = 5  = 0x5
		WRITE_MEM(DMCX_APB_Based+PL341_T_RFC,0x0000132B); // tRFC=127,5 ns/tACLK - 3 = 19 = 0x13; tRFC = 127,5 ns/tACLK= 42,5 = 0x2B;
		WRITE_MEM(DMCX_APB_Based+PL341_T_RP ,0x00000005);  // tRP  = 15 ns / tCK = 5 = 0x5; tRP  = 15 ns / tACLK -3 = 2,5 - 3 =0
		WRITE_MEM(DMCX_APB_Based+PL341_T_RRD,0x00000004); // tRRD = 10 ns / tCK = 3,33=4
		WRITE_MEM(DMCX_APB_Based+PL341_T_WR ,0x00000005);  // tWR  = 15 ns / tCK = 5
		WRITE_MEM(DMCX_APB_Based+PL341_T_WTR,0x00000003); // tWTR = 7,5 ns/ tCK = 2,5=3
		WRITE_MEM(DMCX_APB_Based+PL341_T_XP ,0x00000002);  // tXP = 2
		WRITE_MEM(DMCX_APB_Based+PL341_T_XSR,0x000000c8); //
		WRITE_MEM(DMCX_APB_Based+PL341_T_ESR,0x000000c8); //
		WRITE_MEM(DMCX_APB_Based+PL341_T_MRD,0x00000002);

		WRITE_MEM(DMCX_APB_Based+PL341_MEMORY_CFG, 0x0001001a); //1 chip 14 row 10 column
		WRITE_MEM(DMCX_APB_Based+PL341_MEMORY_CFG2,0x00000030);

		WRITE_MEM(DMCX_APB_Based+0x200,0x00001ff0); //BA-RA-CA

		for(i=0; i<sizeof(PL341_Direct_Cmd)/4;i++){
			WRITE_MEM(DMCX_APB_Based+PL341_DIRECT_CMD,PL341_Direct_Cmd[i]);
		}

		WRITE_MEM(DMCX_APB_Based+PL341_MEMC_CMD,0x00000000);
		
		int r=READ_MEM(DMCX_APB_Based+PL341_MEMC_STATUS,v);
		//do{
		//	READ_MEM(DMCX_APB_Based+PL341_MEMC_STATUS,v);
		//		
		//} while (v&0x3 != 0x1);

	}

	int ReadMemBlock (unsigned* dst_host_addr, unsigned src_nm_addr, int size32){
		return PL_ReadMemBlock(access, (PL_Word*)dst_host_addr, src_nm_addr, size32);
	}
	int WriteMemBlock(unsigned* src_host_addr, unsigned dst_nm_addr, int size32){
		return PL_WriteMemBlock(access, (PL_Word*)src_host_addr, dst_nm_addr, size32);
	}

};


