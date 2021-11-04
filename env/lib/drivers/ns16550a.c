#include <drivers/ns16550a.h>
#include <stdint.h>

#define __MAC_OS

enum {
	NS16550A_CLOCKRATE = 399193, /* clock rate of NS16550A */

	NS16550A_RBR       = 0x00,  /* Receive Buffer Register */
	NS16550A_THR       = 0x00,  /* Transmit Hold Register */
	NS16550A_IER       = 0x01,  /* Interrupt Enable Register */
	NS16550A_DLL       = 0x00,  /* Divisor LSB (LCR_DLAB) */
	NS16550A_DLM       = 0x01,  /* Divisor MSB (LCR_DLAB) */
	NS16550A_FCR       = 0x02,  /* FIFO Control Register */
	NS16550A_LCR       = 0x03,  /* Line Control Register */
	NS16550A_MCR       = 0x04,  /* Modem Control Register */
	NS16550A_LSR       = 0x05,  /* Line Status Register */
	NS16550A_MSR       = 0x06,  /* Modem Status Register */
	NS16550A_SCR       = 0x07,  /* Scratch Register */

	NS16550A_LCR_DLAB  = 0x80,  /* Divisor Latch Bit */
	NS16550A_LCR_8BIT  = 0x03,  /* 8-bit */
	NS16550A_LCR_PODD  = 0x08,  /* Parity Odd */

	NS16550A_LSR_DA    = 0x01,  /* Data Available */
	NS16550A_LSR_OE    = 0x02,  /* Overrun Error */
	NS16550A_LSR_PE    = 0x04,  /* Parity Error */
	NS16550A_LSR_FE    = 0x08,  /* Framing Error */
	NS16550A_LSR_BI    = 0x10,  /* Break indicator */
	NS16550A_LSR_RE    = 0x20,  /* THR is empty */
	NS16550A_LSR_RI    = 0x40,  /* THR is empty and line is idle */
	NS16550A_LSR_EF    = 0x80,  /* Erroneous data in FIFO */
};

static volatile uint8_t *ns16550a_ctrl_ptr;
static volatile uint32_t divisor;

/* ns16550a_init: to setup ns16550a uart device */
__attribute__((weak)) void ns16550a_init(void *uart_start, int baud_rate){
	ns16550a_ctrl_ptr = (uint8_t *)uart_start;
	divisor = (uint32_t)(NS16550A_CLOCKRATE / baud_rate);
	ns16550a_ctrl_ptr[NS16550A_LCR] = NS16550A_LCR_DLAB;
	ns16550a_ctrl_ptr[NS16550A_DLL] = divisor & 0xff;
	ns16550a_ctrl_ptr[NS16550A_DLM] = (divisor >> 8) & 0xff;
    ns16550a_ctrl_ptr[NS16550A_LCR] = NS16550A_LCR_PODD | NS16550A_LCR_8BIT;
}

/* ns16550a_read: to read a byte from uart */
__attribute__((weak)) int ns16550a_read(){
	int c;
	// wait for the data is available
	while(!(ns16550a_ctrl_ptr[NS16550A_LSR] & NS16550A_LSR_DA))
		;
	c = ns16550a_ctrl_ptr[NS16550A_RBR];

#ifdef __MAC_OS
	if(c == '\r') // -crlf (MacOS only)
		c = '\n';
#endif

	ns16550a_write(c); // write to the host before return it

	return c;
}

/* ns16550a_write: to write a byte to uart */
__attribute__((weak)) int ns16550a_write(int c){
	// wait for the line is idle 
	while (!(ns16550a_ctrl_ptr[NS16550A_LSR] & NS16550A_LSR_RI))
		;

	return ns16550a_ctrl_ptr[NS16550A_THR] = c & 0xff;
}

