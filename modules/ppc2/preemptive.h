#pragma once

#define MAXTHREADS 4   // maximum threads that can run concurrently (not including the scheduler)
#define STACKSIZE 4096 // maximum stack size of a thread

void preempt_start();
int thread_create(void *);
void thread_yield();
void thread_exit();

void mti_handler();
