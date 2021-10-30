#include <stdio.h>
#include <stdbool.h>

#include "preemptive.h"

int empty; // indicate buffer empty
int buf;   // buffer for the character

/* Producer: produce one character at a time from 'A' to 'Z' and start from 'A' again */
void Producer(){
	static int wcount = 'A'; // word count
	while(true){
		int delay = 300000000;

		if(empty){
			// generate a character and store it to the shared buffer
			buf = wcount;
			empty = false;

			wcount = (wcount == 'Z')? 'A': wcount + 1; // update the word count
		}

		// hold a while to slow down the generate rate
		for(int i = 0; i < delay; ++i)
			asm volatile("");
	}
}

/* Consumer: consume character generate by Producer and print it to the standard output */
void Consumer(){
	while(true){
		if(!empty){
			// print the character to the standard output
			putchar(buf);
			empty = true;
		}
	}
}

/* main: setup shared buffer, create a thread for Consumer and call Producer as itself */
int main(){
	empty = true;
	thread_create(Consumer);
	Producer();
}

