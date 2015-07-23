#include "vic.h"	
#include "tube.h"
//#include "common.h"
//#include "defs.h"
//#include "mem_map.h"
#include "i2c_func.h"

#define ARM2NM(arm_location) ((arm_location)>>2)
#undef  MEM 
#define MEM(addr)  (*((unsigned volatile*)(ARM2NM(addr))))

#ifdef I2C_IRQ

#ifdef I2C_0
volatile int I2C_0_Handled = VECT_WAITING;

void INTERRUPT VECT_HANDLER_I2C_0 () {   
    unsigned tmp = MEM (I2C_BASE + I2C_STATUS);
    if ((tmp & I2C_IF) != 1) {
        tube_msg("I2C interrupt");
        MEM (I2C_BASE + I2C_COMMAND) = I2C_IACK;
    }
	MEM (VIC_Base0 + VIC_VECTADDR) = 1;
    I2C_0_Handled = VECT_HANDLED;
}
#endif  // I2C_0

#ifdef I2C_1
volatile int I2C_1_Handled = VECT_WAITING;

void INTERRUPT VECT_HANDLER_I2C_1 () {   
    unsigned tmp = MEM (I2C_BASE + I2C_STATUS);
    if ((tmp & I2C_IF) != 1) {
        tube_msg("I2C interrupt");
        MEM (I2C_BASE + I2C_COMMAND) = I2C_IACK;
    }
	MEM (VIC_Base0 + VIC_VECTADDR) = 1;
    I2C_1_Handled = VECT_HANDLED;
}
#endif  // I2C_1

#ifdef I2C_2
volatile int I2C_2_Handled = VECT_WAITING;

void INTERRUPT VECT_HANDLER_I2C_2 () {   
    unsigned tmp = MEM (I2C_BASE + I2C_STATUS);
    tube_msg ("VIC for I2C_2");
    tube_hex (tmp);

    if ((tmp & I2C_IF) != 0x1) {
        tube_msg("I2C interrupt");
        MEM (I2C_BASE + I2C_COMMAND) = I2C_IACK;
    }

//    MEM (I2C_BASE + I2C_COMMAND) = I2C_IACK;
	MEM (VIC_Base0 + VIC_VECTADDR) = 1;
    I2C_2_Handled = VECT_HANDLED;
}
#endif  // I2C_2

#ifdef I2C_3
volatile int I2C_3_Handled = VECT_WAITING;

void INTERRUPT VECT_HANDLER_I2C_3 () {   
    unsigned tmp = MEM (I2C_BASE + I2C_STATUS);
    if ((tmp & I2C_IF) != 1) {
        tube_msg("I2C interrupt");
        MEM (I2C_BASE + I2C_COMMAND) = I2C_IACK;
    }
	MEM (VIC_Base1 + VIC_VECTADDR) = 1;
    I2C_3_Handled = VECT_HANDLED;
}
#endif  // I2C_3

#ifdef I2C_0
void Init_VIC_I2C_0() {
	MEM (VIC_Base0 + VIC_VECTADDR28) = (unsigned) VECT_HANDLER_I2C_0;

	unsigned IrqMask = MEM (VIC_Base0 + VIC_INTENABLE);
	MEM (VIC_Base0 + VIC_INTENABLE) = IrqMask | IRQ_I2C_0;
}	
#endif  // I2C_0

#ifdef I2C_1
void Init_VIC_I2C_1() {
	MEM (VIC_Base0 + VIC_VECTADDR29) = (unsigned) VECT_HANDLER_I2C_1;

	unsigned IrqMask = MEM (VIC_Base0 + VIC_INTENABLE);
	MEM (VIC_Base0 + VIC_INTENABLE) = IrqMask | IRQ_I2C_1;
}	
#endif  // I2C_1

#ifdef I2C_2
void Init_VIC_I2C_2() {
    unsigned tmp;
    tube_msg ("Initialization VIC for I2C_2");
	MEM (VIC_Base0 + VIC_VECTADDR29) = (unsigned) VECT_HANDLER_I2C_2;

	unsigned IrqMask = MEM (VIC_Base0 + VIC_INTENABLE);
	MEM (VIC_Base0 + VIC_INTENABLE) = IrqMask | IRQ_I2C_1;
    tmp = MEM (VIC_Base0 + VIC_INTENABLE);
    tube_hex (tmp);
}	
#endif  // I2C_2

#ifdef I2C_3
void Init_VIC_I2C_3() {
	MEM (VIC_Base1 + VIC_VECTADDR1) = (unsigned) VECT_HANDLER_I2C_3;

	unsigned IrqMask = MEM (VIC_Base1 + VIC_INTENABLE);
	MEM (VIC_Base1 + VIC_INTENABLE) = IrqMask | IRQ_I2C_3;
}	
#endif  // I2C_3

int i2c_wait_irq () {
	int t;
    tube_msg ("I2C wait interrupt");
	for (t=0; t<I2C_TIMEOUT; t++){
		if (I2C_2_Handled == VECT_HANDLED){
            tube_msg ("I2C vect handled");
			return I2C_OK;
		}
	}
    tube_msg("I2C timeout");
	return I2C_FAILED;
}

#endif  // I2C_IRQ

void i2c_init (unsigned prescale, unsigned enable, unsigned irq_en) {
    unsigned control;   // Control register
    //tube_msg ("I2C INITIALIZATION");
    //tube_hex (I2C_BASE);
    // Set prescale
    MEM (I2C_BASE + I2C_PRESCALE) = (unsigned)prescale;
    // Set control
    control = (enable << 7) | (irq_en << 6);
    MEM (I2C_BASE + I2C_CONTROL) = (unsigned)control;
    //tube_msg ("    Initial I2C master!");
}

int i2c_wait () {
    int tmp = -1;

#ifndef I2C_IRQ
    tube_msg ("        I2C wait");
    int cnt = 0;
    while ((tmp & I2C_TIP) != 0) {
        tmp = MEM (I2C_BASE + I2C_STATUS);
        if (++cnt == I2C_TIMEOUT) {
            tube_msg("I2C timeout!");
			MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
            return 0xf2ff;
        }   // if (cnt == I2C_TIMEOUT)
    }   // while ((tmp & I2C_TIP) != 0)
#else
    tmp = i2c_wait_irq ();
    if (tmp != I2C_OK) return tmp;   // timeout wait interrupt
#endif
    return I2C_OK;
}

int i2c_ack () {
    unsigned ack = 0xffff;
    // test acknolege
    ack = MEM (I2C_BASE + I2C_STATUS);
    
    if ((ack & I2C_RxACK) == 0)
        return I2C_OK;
    else {
        tube_msg("I2C no acknolege!");
		MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
        return 0xf3ff;
    }
}

int i2c_trans (unsigned data, unsigned condition) {
    int tmp = -1;
    
    MEM (I2C_BASE + I2C_TRANSMIT) = data;
    MEM (I2C_BASE + I2C_COMMAND) = condition;
    tmp = i2c_wait();
    if (tmp != I2C_OK) return tmp;
    tmp = i2c_ack ();
    if (tmp != I2C_OK) return tmp;
    return I2C_OK;
}

int i2c_write (unsigned i2c_addr, unsigned addr, unsigned data) {
    int tmp = -1;
    int cnt = 0;
    tube_msg ("I2C WRITE OPERATION");
    // Write device address
    tube_msg ("    Write device address");
    while (tmp != I2C_OK) {
        tmp = i2c_trans (i2c_addr, (I2C_STA | I2C_WR));
        if (tmp != I2C_OK) return tmp;
        if (++cnt == I2C_ATTEMPT) {
            tube_msg("No I2C device!");
			MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
            return 0xf4ff;
        }
    }   // while (tmp != I2C_OK)
    // Write subaddress
    tube_msg ("    Write subaddress");   
    tmp = i2c_trans (addr, I2C_WR);
    if (tmp != I2C_OK) {
		MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
		return tmp;
	}
    // Write data
    tube_msg ("    Write data");
    tmp = i2c_trans (data, (I2C_STO | I2C_WR));
    if (tmp != I2C_OK) {
		MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
		return tmp;
	}

    tube_msg ("    Write successful");
    return I2C_OK;
}

unsigned i2c_read (unsigned i2c_addr, unsigned addr) {
    int tmp = -1;
    int cnt = 0;
    unsigned result;    // read data
    tube_msg ("I2C READ OPERATION");
    // Write device address
    tube_msg ("    Write device address");
    tube_hex (i2c_addr);
    cnt = 0;
    while (tmp != I2C_OK) {
        tmp = i2c_trans (i2c_addr, (I2C_STA | I2C_WR));
        if (tmp != I2C_OK) return tmp;
        if (++cnt == I2C_ATTEMPT) {
            tube_msg("No I2C device!");
			MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
            return 0xf4ff;
        }
    }   // while (tmp != I2C_OK)
    // Write subaddress
    tube_msg ("    Write subaddress");
    tmp = i2c_trans (addr, I2C_WR);
    if (tmp != I2C_OK) return tmp;
    tube_msg ("    Write device address and READ condition");
    cnt = 0;
    tmp = -1;
    while (tmp != I2C_OK) {
        tmp = i2c_trans ((i2c_addr | 0x01), (I2C_STA | I2C_WR));
        if (++cnt == I2C_ATTEMPT) {
            tube_msg("No I2C device!");
            return 0xf4ff;
        }
    }   // while (tmp != I2C_OK)
    tube_msg ("    READ data");
    
    MEM (I2C_BASE + I2C_COMMAND) = I2C_STO | I2C_RD | I2C_ACK;

    tmp = i2c_wait();
    if (tmp != I2C_OK) {
		MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
		return tmp;
	}
    
    result = MEM (I2C_BASE + I2C_RECEIVE);
    tube_hex (result);
    
    return result;
}

unsigned i2c_read_tuner (unsigned i2c_addr, unsigned addr, unsigned addr1) {
    int tmp = -1;
	int data = 0;
    int cnt = 0;
    unsigned result = 0x55;    // read data
    tube_msg ("I2C READ OPERATION");
	tube_msg ("    Write device address and READ condition");
    cnt = 0;
    tmp = -1;
    while (tmp != I2C_OK) {
        tmp = i2c_trans ((i2c_addr | 0x01), (I2C_STA | I2C_WR));
        if (++cnt == I2C_ATTEMPT) {
            tube_msg("No I2C device!");
			 MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
            return 0xf4ff;
        }
    }   // while (tmp != I2C_OK)
    
	//read_data
    MEM (I2C_BASE + I2C_COMMAND) = I2C_STO | I2C_RD | I2C_ACK;
    tmp = i2c_wait();
    if (tmp != I2C_OK) {
		MEM (I2C_BASE + I2C_COMMAND) = I2C_STO;
		return tmp;
	}
    MEM(0x130000) = MEM (I2C_BASE + I2C_RECEIVE);
    
    return result;
}