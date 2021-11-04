#include <tools.h>
#include <ctype.h>

int _isdigitof(int base, int c){
	if(base < 10){
		return c >= '0' && c < '0' + base;
	} else{
		return isdigit(c) || (c >= 'a' && c < 'a' + base);
	}
}

