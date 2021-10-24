#pragma once

extern void *uart_start;

/* uart interface */
void uart_init(int);
int uart_read();
int uart_write(int);

