#pragma once

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

/*
* literals for sifive test device
*/
enum{
	TEST_FAIL  = 0x3333, // code for FAIL
	TEST_PASS  = 0x5555, // code for PASS
	TEST_RESET = 0x7777, // code for RESET
};

/*
* prototypes for timer
*/
long long get_mtime();

long long get_mtimecmp();
void set_mtimecmp(long long);

