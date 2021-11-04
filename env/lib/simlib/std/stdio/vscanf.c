#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <tools.h>

// enum for the length modifier
enum {H_MDFR, HH_MDFR, L_MDFR, LL_MDFR, J_MDFR, Z_MDFR, T_MDFR, N_MDFR};

/* getch: get a char from the source string */
static int getch(){
	return getchar();
}

/* getch: unget a char from the source string */
static int ungetch(int c){
	return ungetchar(c);
}

/* read_ignore: read optional ignore flag for the specifier */
static int read_ignore(const char **ff){
	int i = 0;
	if(**ff == '*'){
		i = 1;
		++(*ff);
	}
	return i;
}

/* read_width: read optional width for the specifier */
static size_t read_width(const char **ff){
	size_t w = 0;
	if(isdigit(**ff)){
		int c;
		w = 0;
		while(isdigit(c = **ff)){
			w = w * 10 + (c-'0');
			(*ff)++;
		}
	}
	return w;
}

/* read_mdfr: read optional length modifier for the specifier */
static int read_mdfr(const char **pp){
	int m;
	// read the length modifier
	switch(**pp){
	case 'h':
		if(*(*pp + 1) == 'h'){
			*pp += 2;
			m = HH_MDFR;
		} else{
			++*pp;
			m = H_MDFR;
		}
		break;
	case 'l':
		if(*(*pp + 1) == 'l'){
			*pp += 2;
			m = LL_MDFR;
		} else{
			++*pp;
			m = L_MDFR;
		}
		break;
	case 'j':
		++*pp;
		m = J_MDFR;
		break;
	case 'z':
		++*pp;
		m = Z_MDFR;
		break;
	case 't':
		++*pp;
		m = T_MDFR;
		break;
	default:
		m = N_MDFR;
		break;
	}
	return m;
}

/* peek_int: check if the following input is a valid integer */
static int peek_int(int base){
	int c;
	while(isspace(c=getch()))
		;
	ungetch(c);
	return c == '+' || c == '-' || _isdigitof(base, c);
}

/* peek_char: check if the following input is a valid character */
static int peek_char(){
	int c = getch();
	ungetch(c);
	return c != EOF;
}

/* peek_str: check if the following input is a valid sring */
static int peek_str(){
	int c;
	while(isspace(c=getch()))
		;
	ungetch(c);
	return c != EOF;
}

/* peek_brac: check if the following input is a valid spanset */
static int peek_brac(int reverse, char *cset){
	int c = getch();
	ungetch(c);
	return (reverse)? strchr(cset, c) == NULL: strchr(cset, c) != NULL;
	
}

/* store_int: store integers */
static void store_int(va_list *vl, int ignore, size_t width, int mdfr, int base){
	int c, sign;
	intmax_t v;
	if(width == 0)
		width = SIZE_MAX;
	c = getch();
	sign = (c == '-')? -1: 1;
	v = 0;
	if(c == '+' || c == '-'){
		c = getch(), --width;
	}

	if(base == 16 && c == '0'){
		if((c = getch()) == 'x' || c == 'X'){
			c = getch();
			width -= 2;
		} else{
			ungetch(c);
			c = '0';
		}
	}

	while(width > 0 && _isdigitof(base, c)){
		int n = (isdigit(c))? c-'0': tolower(c)-'a'+10;
		v = v * base + n;
		c = getch(), --width;
	}
	ungetch(c);
	if(!ignore){
		switch(mdfr){
		case H_MDFR:
			*(short *)va_arg(*vl, short *) = sign * v;
			break;
		case HH_MDFR:
			*(char *)va_arg(*vl, char *) = sign * v;
			break;
		case L_MDFR:
			*(long *)va_arg(*vl, long *) = sign * v;
			break;
		case LL_MDFR:
			*(long long *)va_arg(*vl, long long *) = sign * v;
			break;
		case J_MDFR:
			*(intmax_t *)va_arg(*vl, intmax_t *) = sign * v;
			break;
		case Z_MDFR:
			*(size_t *)va_arg(*vl, size_t *) = sign * v;
			break;
		case T_MDFR:
			*(ptrdiff_t *)va_arg(*vl, ptrdiff_t *) = sign * v;
			break;
		default:
			*(int *)va_arg(*vl, int *) = sign * v;
			break;
		}
	}
}

/* store_char: store characters */
static void store_char(va_list *vl, int ignore, size_t width){
	int c;
	char *p;

	if(width == 0)
		width = 1;

	if(!ignore)
		p = (char *)va_arg(*vl, char *);

	c = getch();
	while(width > 0 && c != EOF){
		if(!ignore)
			*p++ = c;
		c = getch(), --width;
	}
	ungetch(c);
}

/* store_str: store non-space string */
static void store_str(va_list *vl, int ignore, size_t width){
	int c;
	char *p;
	if(!ignore)
		p = (char *)va_arg(*vl, char *);

	if(width == 0){
		c = getch();
		while(c != EOF && !isspace(c)){
			if(!ignore)
				*p++ = c;
			c = getch();
		}
	} else{
		c = getch();
		while(width > 0 && c != EOF && !isspace(c)){
			if(!ignore)
				*p++ = c;
			c = getch(), --width;
		}
	}
	if(!ignore)
		*p = '\0';
	ungetch(c);
}

/* store_brac: store scanset */
static void store_brac(va_list *vl, int ignore, size_t width, int reverse, char *cset){
	int c;
	char *p;
	if(!ignore)
		p = (char *)va_arg(*vl, char *);

	if(width == 0){
		c = getch();
		int span = (reverse)? strchr(cset, c) == NULL: strchr(cset, c) != NULL;
		while(c != EOF && span){
			if(!ignore)
				*p++ = c;
			c = getch();
			span = (reverse)? strchr(cset, c) == NULL: strchr(cset, c) != NULL;
		}
	} else {
		c = getch();
		int span = (reverse)? strchr(cset, c) == NULL: strchr(cset, c) != NULL;
		while(width > 0 && c != EOF && span){
			if(!ignore)
				*p++ = c;
			c = getch(), --width;
			span = (reverse)? strchr(cset, c) == NULL: strchr(cset, c) != NULL;
		}
	}
	if(!ignore)
		*p = '\0';
	ungetch(c);
}

/* store_count: store the number of successful conversion so far */
static void store_count(va_list *vl, int ignore, int nc){
	if(!ignore)
		*(int *)va_arg(*vl, int *) = nc;
}

/* vscanf: read formatted data from stdio into variable argument list */
int vscanf(const char *fmt, va_list vl){
	int c;
	size_t width;
	int mdfr;
	if((c=getch()) == EOF)
		return EOF;
	ungetch(c);

	int nc = 0;
	for(const char *f = fmt; *f; ++f){
		int ignore;
		int spcf;
		size_t npeek;
		int base;
		char buf[3];
		int reverse;
		char cset[128];
		char *p;

		if(*f != '%'){
			if(isspace(*f)){
				while(isspace((c=getch())))
					;
				ungetch(c);
			} else if((c=getch()) != *f){
				ungetch(c);
				goto ret;
			}
			continue;
		}
		++f;

		// read sub-specifier if needed
		ignore = read_ignore(&f);
		width = read_width(&f);
		mdfr = read_mdfr(&f);

		// store data to the next element in variable argument list
		spcf = *f;
		switch(spcf){
		case 'i': // integer specifier
			while(isspace(c=getch()))
				;
			if(c != '+' && c != '-' && !isdigit(c)){
				ungetch(c);
				goto ret;
			} else{
				buf[npeek++] = c;
				if(c == '+' || c == '-')
					c = getch(), buf[npeek++] = c;
				if(c == '0'){
					if((c=getch()) == 'x' || c == 'X')
						base = 16;
					else
						base = 8;
					buf[npeek++] = c;
				} else
					base = 10;
				while(npeek > 0)
					ungetch(buf[--npeek]);
			}
			store_int(&vl, ignore, width, mdfr, base);
			++nc;
			break;
		case 'd': case 'u': // dicimal number specifier
			base = 10;
			if(!peek_int(base))
				goto ret;
			store_int(&vl, ignore, width, mdfr, base);
			++nc;
			break;
		case 'o': // octal number specifier
			base = 8;
			if(!peek_int(base))
				goto ret;
			store_int(&vl, ignore, width, mdfr, base);
			++nc;
			break;
		case 'x': case 'p': // hexadecimal number specifier
			base = 16;
			if(!peek_int(base))
				goto ret;
			store_int(&vl, ignore, width, mdfr, base);
			++nc;
			break;
		case 'c': // char specifier
			if(!peek_char())
				goto ret;
			store_char(&vl, ignore, width);
			++nc;
			break;
		case 's': // string specifier
			if(!peek_str())
				goto ret;
			store_str(&vl, ignore, width);
			++nc;
			break;
		case '[': // scanset specifier
			p = cset;
			reverse = 0;
			if(*(f+1) == '^'){
				reverse = 1;
				++f;
			}
			while((c=*++f) != '\0' && c != ']')
				*p++ = c;
			if(c == '\0')
				--f;
			*p = '\0';

			if(!peek_brac(reverse, cset))
				goto ret;
			store_brac(&vl, ignore, width, reverse, cset);
			++nc;
			break;
		case 'n': // count specifier
			store_count(&vl, ignore, nc);
			++nc;
			break;
		case '%': // %
			if((c=getch()) != spcf){
				ungetch(c);
				goto ret;
			}
			break;
		}
	}
ret:
	return nc;
}

