#pragma once

extern void *finisher_start;

/* finisher interface */
void finisher_init();
void finisher_exit(int);
void finisher_reset();

