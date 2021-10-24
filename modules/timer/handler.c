#include "timer.h"

static char *uart_ctrl_ptr = (char *)0x10000000; // address of UART device

static int *finisher_ctrl_ptr = (int *)0x100000; // address of Finisher device

int period = 10000000; // period of timer interrupt
int epoch = 10;

/* _trap_handler: Ivoke the corresponding handler according to the mcause register */
void _trap_handler(int mcause, int mepc, int *regs){
	int intr = (mcause < 0)? 1: 0;
	int code = mcause & 0x7fffffff;

	if(intr){
		switch(code){
		case 7: // a machine timer interrupt occur
			long long time = get_mtime();
			set_mtimecmp(get_mtimecmp() + period);
			if(time < period * epoch){
				// output the time to the host in number of seconds
				while(!(uart_ctrl_ptr[LSR] & LSR_TI))
					;
				uart_ctrl_ptr[THR] = time/10000000 + '0';
			} else{ // stop emulation normally
				while(!(uart_ctrl_ptr[LSR] & LSR_TI))
					;
				uart_ctrl_ptr[THR] = '\n';
				*finisher_ctrl_ptr = TEST_PASS;
			}
			break;
		default: // stop emulation if an unhandlable interrupt occur
			*finisher_ctrl_ptr = 0x8000 | (mcause << 16) | TEST_FAIL;
			break;
		}
	} else // stop emulation if exception occur
		*finisher_ctrl_ptr = (mcause << 16) | TEST_FAIL;
}

