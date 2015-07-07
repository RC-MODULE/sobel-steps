// 576p
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "i2c_func.h"


void Init_Cache();
void Init_VIC();
void Init_DDR_EM0();
void Init_DDR_EM1();

#define ARM2NM(arm_location) ((arm_location)>>2)
#undef  MEM 
#define MEM(addr)  (*((unsigned volatile*)(ARM2NM(addr))))



void Init_HDMI_Phys(){
    MEM(0x2003c000) = 0x00000000; // 800f0000h
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00002ac1;
} // Init_HDMI_Phys



int Init_HDMI()
{  unsigned prescale = 0x6b;      		 // prescale for 54 MHz
   int ret;
   int data_ic=0;

   i2c_init (prescale, I2C_EN, I2C_IRQ_EN);
	
    // write data
   // ret=i2c_write (0x72,0x32, 0xCF);
//	ret=i2c_read(0x72,0x32);

    ret =i2c_write (0x72,0x08, 0x37)  ;
//	ret|=i2c_write (0x7a,0x2f, 0x01)<<1;
	ret|=i2c_write (0x72,0x4a, 0x0c)<<2;
	ret|=i2c_write (0x72,0x48, 0x10)<<3;
//	ret|=i2c_write (0x72,0x33, 0)<<4;

	return ret;    
} // Init_HDMI
    


void Init_VDU(int W, int H , unsigned Y0, unsigned U0,  unsigned V0, unsigned Y1, unsigned U1,  unsigned V1 )
{
	MEM(0x8017300c)=0x1 ;     //сброс Контроллера Video
	
	unsigned VDU_Y_SIZE=((H-1)<<16)+W-1;
	unsigned VDU_UV_SIZE=((H/2-1)<<16)+((W/2)-1);
	
	MEM(0x80173418)=VDU_Y_SIZE; 	//SIZE_V_SIZE_H для Y (после масшатабирования)
	MEM(0x8017341c)=VDU_UV_SIZE; 	//SIZE_V/2_SIZE_H/2 для C (после масшатабирования)
	MEM(0x80173420)=0x00000101;
	MEM(0x80173424)=0x0000FEFE;
	MEM(0x80173428)=0x00000101;
	MEM(0x8017342c)=0x0;
	MEM(0x80173430)=0x0;
	MEM(0x80173448)=0x0;
	MEM(0x8017344c)=0x00000101;
	MEM(0x80173450)=0x0000FEFE;
	MEM(0x80173454)=0x00000101;
	MEM(0x80173458)=0x0;
	MEM(0x8017345c)=0x0;
	MEM(0x80173474)=VDU_Y_SIZE; // SIZE_V_SIZE_H для Y (после обрезания)
	MEM(0x8017347c)=0x0;
	MEM(0x80173480)=0x00040000;
	MEM(0x80173484)=0x10000000;
	 
	MEM(0x80173504)=0x00030213;
	MEM(0x80173508)=0x00d03090;
	MEM(0x8017350c)=0x00000000;
	MEM(0x80173510)=0x052C0087;
	MEM(0x80173514)=0x02710360;
	MEM(0x80173518)=0x024002CF;
	MEM(0x8017351C)=0x4440000C;
	MEM(0x80173520)=0x00050000;
	 
	MEM(0x80173904)=0x0000100;
	 
	MEM(0x80173908)=Y0; //BA_0 Y
	MEM(0x8017390c)=U0; //BA_0 CB
	MEM(0x80173910)=V0; //BA_0 CR
	MEM(0x80173914)=Y1; //BA_1 Y
	MEM(0x80173918)=U1; //BA_1 CB
	MEM(0x8017391C)=V1; //BA_1 CR
	 
	MEM(0x80173920)=VDU_Y_SIZE; //SIZE_V_SIZE_H для Y
	MEM(0x80173924)=VDU_UV_SIZE; //SIZE_V/2_SIZE_H/2 для C
	MEM(0x80173928)=((W/2)<<16)+(W); //FULL_SIZE_C_FULL_SIZE_Y = SIZE_H/2_SIZE_H
	MEM(0x8017392c)=0x00000000;
    MEM(0x80173930)=0x00000000;
	 
	MEM(0x80173008)=0x205;      //2=SW_EN, 5=MVL_EN + VDU_EN
	MEM(0x80173308)=0xFFFFFFFF; 
 
} // Init_VDU

int Start_VDU(int W, int H, unsigned Y0, unsigned Y1) {

	unsigned U0=Y0+H*W;
	unsigned V0=U0+H*W/4;

        MEM(0x80179000) = 1; // enable to change clock
	MEM(0x80179004) = 1; // 0 - SD 27 MHz, 1 - HD 74,25MHz
	
	Init_HDMI_Phys();
	
	Init_HDMI();
	
	Init_VDU(W,H,Y0,U0,V0,Y0,U0,V0);
		
	return 1;
}
