#define I2C_HDMI
//#define I2C_IRQ
//#define I2C_2
// I2C base address definition
#ifdef I2C_HDMI
#define I2C_BASE 		0x80171000
#endif

#ifdef I2C_0
#define I2C_BASE 		0x20020000
#endif

#ifdef I2C_1
#define I2C_BASE 		0x20021000
#endif

#ifdef I2C_2
#define I2C_BASE 		0x20026000
#endif

#ifdef I2C_3
#define I2C_BASE 		0x2002d000
#endif

#define I2C_HDMI_BASE 	0x80171000

#define I2C_0_BASE 		0x20020000

#define I2C_1_BASE 		0x20021000

#define I2C_2_BASE 		0x20026000

#define I2C_3_BASE 		0x2002d000

#ifdef I2C_HDMI
#define MULTI_SCTL          0x80172000
#define I2C_INT_STAT        0xa0
#define I2C_INT_TYPE_ENA    0x94
#define I2C_INT_TYPE        0x98
#define I2C_INT_ENA         0x9c
#endif

// I2C constraints 
#define I2C_TIMEOUT 	0x1000
#define I2C_ATTEMPT 	0x10

// I2C registers
#define I2C_PRESCALE 	0x00
#define I2C_CONTROL 	0x04
#define I2C_TRANSMIT 	0x08
#define I2C_RECEIVE 	0x08
#define I2C_COMMAND 	0x0c
#define I2C_STATUS   	0x0c

#define I2C_EN          1
#ifndef I2C_IRQ
#define I2C_IRQ_EN      0
#else
#define I2C_IRQ_EN      1
#endif

#define SCTL            0x2003c000
#define SCTL_IRQ_RST    0x8


// I2C commands
// Transmit
#define I2C_STA   	    0x80
#define I2C_STO   	    0x40
#define I2C_WR   	    0x10
#define I2C_RD   	    0x20
#define I2C_ACK   	    0x08
#define I2C_IACK   	    0x01
// Receive
#define I2C_RxACK   	0x80
#define I2C_TIP       	0x02
#define I2C_IF       	0x01

#define I2C_FAILED      0xffff  // 0xffff - unachievable value for I2C transaction
#define I2C_OK          0x1

/*
 * Initialization I2C controller
 * prescale: prescale for SCL, depend on I2C clock
 * enable: 1 - enable I2C controller, 0 - disable I2C controller
 * irq_en: 1 - interrupt enabel (don't use), 0 - disable interrupt
 */
	void i2c_init (unsigned prescale, unsigned enable, unsigned irq_en);


/*
 * Write I2C data
 * i2c_addr: I2C device address
 * addr: subaddress (device register address)
 * data: data for write
 * RETURN:
 * I2C_OK == 1, if write successful
 * I2C_FAILED == 0xffff, if write operation failed
 */
int i2c_write (unsigned i2c_addr, unsigned addr, unsigned data);

/*
 * Read I2C data
 * i2c_addr: I2C device address
 * addr: subaddress (device register address)
 * RETURN:
 * I2C_FAILED == 0xffff, if read operation failed
 * data, if read successful
 */
unsigned i2c_read (unsigned i2c_addr, unsigned addr);

/*
 * I2C transaction
 * Write registers TRANSMIT and COMMAND of I2C controller,
 * wait TIP and check acknoledge (RxACK)
 * data: data for TRANSMIT register
 * condition: data for COMMAND register
 * RETURN:
 * I2C_OK == 1, if RxACK
 * I2C_FAILED == 0xffff, if no TIP or no RxACK
 */
int i2c_trans (unsigned data, unsigned condition);

/*
 * Wait TIP
 * RETURN:
 * I2C_OK == 1, if TIP
 * I2C_FAILED == 0xffff, if no TIP
 */
int i2c_wait ();

/*
 * Check acknoledge (RxACK)
 * RETURN:
 * I2C_OK == 1, if RxACK
 * I2C_FAILED == 0xffff, if no RxACK
 */
int i2c_ack ();

/*
 * Wiat I2C interrupt
 * not use!
 */
int i2c_wait_irq ();


void i2c_irq_handler ();
