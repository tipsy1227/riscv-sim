#pragma once

void trap_handler();

void *get_trap_hd(int);
void *set_trap_hd(int, void *);

