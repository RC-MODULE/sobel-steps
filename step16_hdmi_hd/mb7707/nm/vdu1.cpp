// 1080p из vdu.cpp.003
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "i2c_func.h"


void Init_Cache();
void Init_VIC();
void Init_DDR_EM0();
void Init_DDR_EM1();

#define HD_1920

#define ARM2NM(arm_location) ((arm_location)>>2)
#undef  MEM 
#define MEM(addr)  (*((unsigned volatile*)(ARM2NM(addr))))

unsigned YCbCr( int R, int G, int B);

void Init_HDMI_Phys(){
    MEM(0x2003c000) = 0x00000000;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00000001;
    MEM(0x2003c000) = 0x00002ac1;	 
}



int Init_HDMI(){

    unsigned prescale = 0x6b;     // prescale for 54 MHz
   // initial I2C master
    i2c_init (prescale, I2C_EN, I2C_IRQ_EN);
  // initial I2C master for HDMI
	int ret;
	int data_ic=0;
    // write data
        ret =i2c_write (0x72,30, 0xCF);
	ret =i2c_read(0x72,30);
        ret =i2c_write (0x72,0x08, 0x37)  ;
	ret|=i2c_write (0x7a,0x2f, 0x01)<<1;
	ret|=i2c_write (0x72,0x4a, 0x0c)<<2;
	ret|=i2c_write (0x72,0x48, 0x10)<<3;
	ret|=i2c_write (0x72,0x33, 0x00)<<4;
	return ret;    
}                  
    


void Init_VDU(int W, int H , unsigned Y0, unsigned U0,  unsigned V0, unsigned Y1, unsigned U1,  unsigned V1, int offset )
{ unsigned *p;
   MEM(0x8017300c)=0x1 ;     //сброс ВК
//   unsigned offset = 20;
   unsigned VDU_Y_SIZE=((H-1-offset)<<16)+W-1-offset;
   unsigned VDU_UV_SIZE=(((H-offset)/2-1)<<16)+(((W-offset)/2)-1);// was H/2-1
// DIF registers:
//30000 vsync=0 при прямом, 200 видеоданные сопровождаются синхронизацией
#ifdef HD_1920
MEM(0x80173504)=0x0003021a;    // mode 1a: 1080P 30hz, if 1b then 25 hz
MEM(0x80173508)=0x00e08080;   // BG color YCbCr чисто green
MEM(0x8017350c)=offset/2+((offset/2)<<16);    // xstart+(ystart<<16) нач. к-ты основного слоя
MEM(0x80173510)=0x0429010f;  // интервалы развёрток
MEM(0x80173514)=0x04650898;  // размеры кадра, включая промежутки < 1125 | 2200 >
MEM(0x80173518)=0x0438077b;  // видимая часть:размеры img < 1080 | 1915 >
MEM(0x8017351c)=0x942c0058; // позиция гор. синхронизации
MEM(0x80173520)=0x00050000;    // длина vsync=5
#else
MEM(0x80173504)=0x00030213;
MEM(0x80173508)=0x00108080;   // Y,Cb,Cr
MEM(0x8017350c)=0x00000000;
MEM(0x80173510)=0x052c0087;
MEM(0x80173514)=0x02710360;
MEM(0x80173518)=0x024002cf;
MEM(0x8017351c)=0x4440000c;
MEM(0x80173520)=0x00050000;

#endif
//----------------------------
MEM(0x80173400)=0;
MEM(0x80173404)=0; // отключены масштабирование и обрезание
MEM(0x80173408)=0;
MEM(0x8017340c)=0;
MEM(0x80173410)=0;
MEM(0x80173414)=0;
MEM(0x80173418)=VDU_Y_SIZE;    // размер после масштабирования
MEM(0x8017341c)=VDU_UV_SIZE;   // размер после масштабирования
MEM(0x80173420)=0; 
MEM(0x80173424)=0;
MEM(0x80173428)=0;
MEM(0x8017342c)=0;
MEM(0x80173430)=0;
MEM(0x80173434)=0;
MEM(0x80173438)=0;
MEM(0x8017343c)=0;
MEM(0x80173448)=0;
MEM(0x8017344c)=0;
MEM(0x80173450)=0;
MEM(0x80173454)=0;
MEM(0x80173458)=0;
MEM(0x8017345c)=0;
MEM(0x80173460)=0;
MEM(0x80173470)=0;
MEM(0x80173474)=VDU_Y_SIZE;  // размер после обрезания(одинаков для Y и C)
MEM(0x80173478)=0; //0x5ac00cb;
MEM(0x8017347c)=0x00000000; // матрица преобразования цветов
MEM(0x80173480)=0x00040000; // из YCbCr в YCbCr
MEM(0x80173484)=0x10000000;



// OSD filter & headers	
MEM(0x80173700)= 0x00000000;  // адрес заголовка 0
MEM(0x80173704)= 0x00000000;  // адрес заголовка 1
MEM(0x80173708)= 0x813c17;    // 3 слова к-тов  из RGB 
MEM(0x8017370c)= 0x384ad0d;
MEM(0x80173710)= 0x1054cc38;
MEM(0x80173714)= 0x7f;  // fifo end (const)
MEM(0x80173718)= 1;     // 1 ARGB color format else 0: RGBA
MEM(0x8017371c)= 0x0;
MEM(0x80173720)= 0x0;
//       заголовки графического слоя ( 6 32р. слов):
p=(unsigned int*)0x0c0000000; // заголовок: 3 раза по 64бит
p[0]=0x10000000; // от этого бреда ничего не зависит 
p[1]=0x10000000;
p[2]=1000+(1080<<16);  // размеры img (при изменении "не поддерживается")
p[3]=0x1000100; // начало img
p[4]=1920; p[5]=0; // df=0:это 565
// Основной слой:
//1:полукадры в разных областях, 
//2:черезстрочный, 4:макроблочный если не 100
//100 тройное разделение Y, Cb, Cr
//200 4:2:2 else 4:2:0
MEM(0x80173904)=0x100; // все биты безразличны, in linux это=0
//0 это 4:2:0 прогрессивный кадр	 
	MEM(0x80173908)=Y0; //BA_0 Y
	MEM(0x8017390c)=U0; //BA_0 Cb
	MEM(0x80173910)=V0; //BA_0 Cr
	MEM(0x80173914)=Y1; //BA_1 Y
	MEM(0x80173918)=U1; //BA_1 Cb
	MEM(0x8017391C)=V1; //BA_1 Cr
	MEM(0x80173920)=VDU_Y_SIZE;  // ((H-21)<<16)+W-21
	MEM(0x80173924)=VDU_UV_SIZE; // (((H-20)/2-1)<<16)+(((W-20)/2)-1)
	MEM(0x80173928)=((W/2)<<16)+W; // периоды строк в памяти для C и Y и без -1 обе
	MEM(0x8017392c)=0x1310000; // linux 0xf310000;
        MEM(0x80173930)=0x0;       // linux 0x6f22c6;
        MEM(0x80173934)=0x365;     // linux
        MEM(0x80173938)=0x0000000; // linux
	MEM(0x8017393c)=0;
	
	MEM(0x80173504)=0x00030213;   //!!

MEM(0x80173008)=0x205;      //5=MVL_EN + VDU_EN,
//MEM(0x80173008)=0x1;      //1=VDU_EN,
// 200 заголовки не используются, адреса указаны в MI_MVL_XX_BA(908...)
MEM(0x80173308)=0;//xFFFFFFFF; //разрешение всех прерываний

} // Init_VDU

int Start_VDU(int W, int H, unsigned Y0, unsigned Y1, int offset) 
{

	unsigned U0=Y0+H*W;
	unsigned V0=U0+((H*W)>>2);
#ifdef HD_1920
        MEM(0x80172000) = 0x00000001; // enable to change clock
	MEM(0x80172004) = 0x00000001; // 0 - SD 27 MHz, 1 - HD 74,25MHz
#endif
	Init_HDMI_Phys();
	
	int ret=Init_HDMI();
	
	Init_VDU(W,H,Y0,U0,V0,Y0,U0,V0,offset);
	
	return 1;
}
