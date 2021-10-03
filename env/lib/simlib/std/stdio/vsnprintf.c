#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <tools.h>

// union for formated variable
static union{
	intmax_t i;
	uintmax_t u;
	void *p;
} var;

static int LJUST; // left adjust flag
static int FPLUS; // force plus flag
static int SPACE; // space flag
static int PRECE; // precedence flag
static int ZEROS; // zeros flag

static size_t len; // length of out array

static char tmp[sizeof(intmax_t) * 8 + 1]; // temporary buffer for integer variable

static size_t width; // minimum width of an formated variable
static size_t preci; // precision of an formated varialbe
static char prec[4]; // temporary buffer for precedence

static int sign;     // sign flag for decimal number
static size_t nprec; // length of prec array
static size_t nzero; // number of leading zeros to be pad
static size_t ncnt;  // length of the variable content

/* read_flag: read flags if any */
static void read_flag(const char **pp, va_list *vl){
	int noflag = 0;

	// keep reading flag if any
	while(!noflag){
		switch(**pp){
		case '-':
			++*pp;
			LJUST = 1;
			break;
		case '+':
			++*pp;
			FPLUS = 1;
			break;
		case ' ':
			++*pp;
			SPACE = 1;
			break;
		case '#':
			++*pp;
			PRECE = 1;
			break;
		case '0':
			++*pp;
			ZEROS = 1;
			break;
		default:
			noflag = 1;
			break;
		}
	}
}

/* read_width: read the width if any */
static void read_width(const char **pp, va_list *vl){
	if(**pp == '*'){ // read the width from the variable list
		width = (int)va_arg(*vl, int);
		++*pp;
	} else if(isdigit(**pp)){
		char buf[sizeof(size_t) * 8 + 1];
		int i = 0;
		while(isdigit(**pp))
			buf[i++] = *(*pp)++;
		buf[i] = '\0';
		width = _atoi(buf, 10);
	}
}

/* read_preci: read the precision if any */
static void read_preci(const char **pp, va_list *vl){
	if(**pp != '.')
		return;
	++*pp;

	preci = 0; // preci is default to 0 if '.' is specified
	if(**pp == '*'){ // read the precision from the variable list
		preci = (int)va_arg(*vl, int);
		++*pp;
	} else if(isdigit(**pp)){
		char buf[sizeof(size_t) * 8 + 1];
		int i = 0;
		while(isdigit(**pp))
			buf[i++] = *(*pp)++;
		buf[i] = '\0';
		preci = _atoi(buf, 10);
	}
}

/* issign: check if the specifier c is signed */
static int issign(int c){
	return c == 'd' || c == 'i';
}

/* isusign: check if the specifier c is unsigned */
static int isusign(int c){
	return c == 'u' || c == 'o' || c == 'x' || c == 'X';
}

/* read_spcf: read out the formated variable according to the specifier */
static void read_spcf(const char **pp, va_list *vl){
	int spcf;

	enum {H_MDFR, HH_MDFR, L_MDFR, LL_MDFR, J_MDFR, Z_MDFR, T_MDFR, N_MDFR} mdfr;

	// read the length modifier
	switch(**pp){
	case 'h':
		if(*(*pp + 1) == 'h'){
			*pp += 2;
			mdfr = HH_MDFR;
		} else{
			++*pp;
			mdfr = H_MDFR;
		}
		break;
	case 'l':
		if(*(*pp + 1) == 'l'){
			*pp += 2;
			mdfr = LL_MDFR;
		} else{
			++*pp;
			mdfr = L_MDFR;
		}
		break;
	case 'j':
		++*pp;
		mdfr = J_MDFR;
		break;
	case 'z':
		++*pp;
		mdfr = Z_MDFR;
		break;
	case 't':
		++*pp;
		mdfr = T_MDFR;
		break;
	default:
		mdfr = N_MDFR;
		break;
	}

	// read the content of variable into var
	spcf = **pp;
	if(issign(spcf)){
		switch(mdfr){
		case H_MDFR:
			var.i = (short)va_arg(*vl, int);
			break;
		case HH_MDFR:
			var.i = (signed char)va_arg(*vl, int);
			break;
		case L_MDFR:
			var.i = (long)va_arg(*vl, long);
			break;
		case LL_MDFR:
			var.i = (long long)va_arg(*vl, long long);
			break;
		case J_MDFR:
			var.i = (intmax_t)va_arg(*vl, intmax_t);
			break;
		case Z_MDFR:
			var.i = (size_t)va_arg(*vl, size_t);
			break;
		case T_MDFR:
			var.i = (ptrdiff_t)va_arg(*vl, ptrdiff_t);
			break;
		default:
			var.i = (int)va_arg(*vl, int);
			break;
		}
	} else if(isusign(spcf)){
		switch(mdfr){
		case H_MDFR:
			var.u = (unsigned short)va_arg(*vl, unsigned int);
			break;
		case HH_MDFR:
			var.u = (unsigned char)va_arg(*vl, unsigned int);
			break;
		case L_MDFR:
			var.u = (unsigned long)va_arg(*vl, unsigned long);
			break;
		case LL_MDFR:
			var.u = (unsigned long long)va_arg(*vl, unsigned long long);
			break;
		case J_MDFR:
			var.u = (uintmax_t)va_arg(*vl, uintmax_t);
			break;
		case Z_MDFR:
			var.u = (size_t)va_arg(*vl, size_t);
			break;
		case T_MDFR:
			var.u = (ptrdiff_t)va_arg(*vl, ptrdiff_t);
			break;
		default:
			var.u = (unsigned int)va_arg(*vl, unsigned int);
			break;
		}
	} else if(spcf == 'c'){ /* wide char unimplemented */
		var.i = (int)va_arg(*vl, int);
	} else if(spcf == 's'){ /* wide char pointer unimplemented */
		var.p = (void *)va_arg(*vl, void *);
	} else if(spcf == 'p'){
		var.p = (void *)va_arg(*vl, void *);
	} else if(spcf == 'n'){
		switch(mdfr){
		case H_MDFR:
			*(short *)va_arg(*vl, short *) = len;
			break;
		case HH_MDFR:
			*(signed char *)va_arg(*vl, signed char *) = len;
			break;
		case L_MDFR:
			*(long *)va_arg(*vl, long *) = len;
			break;
		case LL_MDFR:
			*(long long *)va_arg(*vl, long long *) = len;
			break;
		case J_MDFR:
			*(intmax_t *)va_arg(*vl, intmax_t *) = len;
			break;
		case Z_MDFR:
			*(size_t *)va_arg(*vl, size_t *) = len;
			break;
		case T_MDFR:
			*(ptrdiff_t *)va_arg(*vl, ptrdiff_t *) = len;
			break;
		default:
			*(int *)va_arg(*vl, int *) = len;
			break;
		}
	}

	// setup the formated variable
	switch(spcf){
	case 'd': case 'i':
		// set the sign flag if needed
		if(var.i < 0 || FPLUS || SPACE)
			sign = 1;

		if(preci != 0 || var.i != 0){ // no digits is output when precision is 0 and the value of the variable is also 0
			ncnt = strlen(_utoa(llabs(var.i), tmp, 10)); // convert the absolute value of the integer into a decimal string
			if(preci != SIZE_MAX && ncnt < preci) // if precision is specified and is greater than the number of the digits
				nzero += preci - ncnt;
		}
		break;
	case 'u':
		if(preci != 0 || var.i != 0){ // no digits is output when precision is 0 and the value of the variable is also 0
			ncnt = strlen(_utoa(var.u, tmp, 10)); // convert the integer into a decimal string
			if(preci != SIZE_MAX && ncnt < preci) // if precision is specified and is greater than the number of the digits
				nzero += preci - ncnt;
		}
		break;
	case 'o':
		if(preci != 0 || var.i != 0){ // no digits is output when precision is 0 and the value of the variable is also 0
			ncnt = strlen(_utoa(var.u, tmp, 8)); // convert the integer into a octal string
			if(preci != SIZE_MAX && ncnt < preci) // if precision is specified and is greater than the number of the digits
				nzero += preci - ncnt;
		}

		// add a leading '0' if there is no one
		if(PRECE && nzero == 0 && tmp[0] != '0'){
			strcpy(prec, "0");
			nprec = strlen(prec);
		}
		break;
	case 'x': case 'X':
		if(preci != 0 || var.i != 0){ // no digits is output when precision is 0 and the value of the variable is also 0
			ncnt = strlen(_utoa(var.u, tmp, 16)); // convert the integer into a hexidecimal string
			if(spcf == 'X'){ // convert all digits into uppercase if specifier is 'X'
				for(char *p = tmp; *p; p++)
					*p = toupper(*p);
			}
			if(preci != SIZE_MAX && ncnt < preci) // if precision is specified and is greater than the number of the digits
				nzero += preci - ncnt;
		}

		// add a leading "0x" or "0X"
		if(PRECE){
			strcpy(prec, (spcf == 'x')? "0x": "0X");
			nprec = strlen(prec);
		}
		break;
	case 'c':
		// copy the character into tmp array
		tmp[ncnt++] = (char)var.i;
		tmp[ncnt] = '\0';
		break;
	case 's':
		// copy preci characters at most if precision specified
		ncnt = min(strlen((char *)var.p), preci);
		break;
	case 'p':
		// convert the pointer into a hexidecimal number
		ncnt = strlen(_utoa((unsigned int)var.p, tmp, 16));
		break;
	}
}

/* append: append nc of c to the out array with length n */
static void append(size_t nc, char c, char *out, size_t n){
	if(out && len < n - 1){
		size_t p = (len + nc < n - 1)? nc: n - 1 - len;
		for(size_t i = 0; i < p; ++i)
			out[len + i] = c;
	}
	len += nc;
}

/* appendsign: append the the sign flag to the out array */
static void appendsign(char *out, size_t n){
	if(out && len < n - 1){
		if(var.i < 0)
			out[len] = '-';
		else if(FPLUS)
			out[len] = '+';
		else
			out[len] = ' ';
	}
	++len;
}

/* vsnprintf: write formatted datas from variable argument list to a sized buffer */
int vsnprintf(char * out, size_t n, const char* fmt, va_list vl)
{
	len = 0;          // len default to 0
	for(const char *p = fmt; *p; ++p){
		if(*p != '%'){ // copy character into out and continue to the next character if it is not a '%'
			if(out && len < n - 1)
				out[len] = *p;
			++len;
			continue;
		}

		if(*++p == '%'){ // if the next charcter is also '%'
			if(out && len < n - 1)
				out[len] = *p;
			++len;
			continue;
		}

		// otherwise it is a specifier
		LJUST = FPLUS = SPACE \
		  = PRECE = ZEROS = 0; // all flags default to 0

		width = 0;        // width default to 0
		preci = SIZE_MAX; // preci default to SIZE_MAX
		sign = 0; // sign default to 0
		nprec = 0; // nprec default to 0
		nzero = 0; // nzero default to 0
		ncnt = 0; // ncnt default to 0

		read_flag(&p, &vl);  // read all flags
		read_width(&p, &vl); // read the width
		read_preci(&p, &vl); // read the precision
		read_spcf(&p, &vl);  // read the variable

		// write the formated variable into out array
		int spcf = *p;
		size_t vwidth = sign + nprec + nzero + ncnt;

		if(ZEROS){ // pad zeros after sign and precidence 
			// append a sign if any
			if(sign)
				appendsign(out, n);

			// append a precedence if any
			if(nprec > 0){
				if(out && len < n - 1)
					strncpy(out + len, prec, nprec);
				len += nprec;
			}

			// pad zeros
			if(!LJUST && vwidth < width)
				append(width - vwidth, '0', out, n);
		} else{ // pad blanks before sign character
			// pad blanks
			if(!LJUST && vwidth < width)
				append(width - vwidth, ' ', out, n);

			// append a sign if any
			if(sign)
				appendsign(out, n);

			// append a precedence if any
			if(nprec > 0){
				if(out && len < n - 1)
					strncpy(out + len, prec, nprec);
				len += nprec;
			}
		}

		if(nzero > 0) // append zeros specified by precision
			append(nzero, '0', out, n);

		// copied the content into out array
		if(ncnt > 0){
			if(out && len < n - 1){
				strncpy(out + len, (spcf == 's')? (char *)var.p: tmp, (len + ncnt < n - 1)? ncnt: n - 1 - len);
			}
			len += ncnt;
		}

		// right pad with ' '
		if(LJUST && vwidth < width)
			append(width - vwidth, ' ', out, n);
	}

	if(out && len < n - 1)
		out[(len < n)? len: n - 1] = '\0';

	return len;
}

