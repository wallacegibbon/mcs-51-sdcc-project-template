#ifndef __WARNING_H
#define __WARNING_H

// #warning "hello, this is a normal header file"

#include <mcs51/8051.h>

static inline int blah()
{
	P3_1 = 1;
	return 0;
}

#endif
