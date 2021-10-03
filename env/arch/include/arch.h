#pragma once

/* uart drivers */
void _uart_init();
int _uart_read();
int _uart_write(int c);

/* finisher drivers */
void _finisher_init();
void _finisher_exit(int status);
void _finisher_test_reset();

