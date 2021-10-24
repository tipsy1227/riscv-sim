/*
* literals for ns16550a UART device
*/
enum{
	RBR = 0,   // Receive Buffer Register
	THR = 0,   // Transmit Hold Register
	DLO = 0,   // Lower part of Divisor
	DUP = 1,   // Upper part of Divisor
	LCR = 3,   // Line Control Register
	LSR = 5,   // Line Status Register

	LCR_DLAB = 0x80, // Divisor Latch Bit
	LCR_8BIT = 0x03, // 8-bit
	LCR_PODD = 0x08, // Odd-Parity

	LSR_TI = 0x40, // Transmitter Idle
	LSR_DA = 0x01, // Data Available
};

char *uart_ctrl_ptr = (char *)0x10000000; // address of UART device
int divisor = 1; // divisor for 399193 baud

/*
* control characters
*/
enum{
	EOT = 0x04,
};

/* main: setup UART and echo characters read from the host */
int main(){
	// setup UART to be 399193 baud, 8 bit transmission, and with odd parity
	uart_ctrl_ptr[LCR] = LCR_DLAB;
	uart_ctrl_ptr[DLO] = divisor & 0xff;
	uart_ctrl_ptr[DUP] = (divisor >> 8) & 0xff;
	uart_ctrl_ptr[LCR] = LCR_8BIT | LCR_PODD;

	// write back all characters read from the host until it's a EOT character
	int c;
	do{
		while(!(uart_ctrl_ptr[LSR] & LSR_DA)) // polling for data being available
			;
		c = uart_ctrl_ptr[RBR]; // read from the host

		while(!(uart_ctrl_ptr[LSR] & LSR_TI)) // polling for transmiter being idle
			;
		uart_ctrl_ptr[THR] = c; // write to the host
	} while(c != EOT);
}

