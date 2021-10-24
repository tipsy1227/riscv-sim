#pragma once

#define _saved_regs 14

typedef struct{
	int env[_saved_regs];
} jmp_buf[1];

int setjmp(jmp_buf);
void longjmp(jmp_buf, int);

