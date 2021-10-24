#pragma once

/* driver for ns16550a UART device */
void ns16550a_init(void *, int);
int ns16550a_read();
int ns16550a_write(int);

