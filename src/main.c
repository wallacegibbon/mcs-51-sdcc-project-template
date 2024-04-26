#include "warning.h"
#include <mcs51/8051.h>

/// For more details on this topic (__data, __xdata, etc.),
/// Search for "intrinsic named address spaces" (or "storage classes" in old releases) in documents.

__data unsigned char *d1;
__idata unsigned char *d2;
__pdata unsigned char *d3;
__xdata unsigned char *d4;
__code unsigned char *d5;
unsigned char *d6;

struct blah {
	unsigned int id;
	unsigned char cnt;
};

// __xdata struct blah a, *pa;
__pdata struct blah a, *pa;

void main(void)
{
	P1_1 = 0;
	P2 = sizeof(d1);
	P2 = sizeof(d2);
	P2 = sizeof(d3);
	P2 = sizeof(d4);
	P2 = sizeof(d5);
	P2 = sizeof(d6);
	a.id = 1;
	a.cnt = 2;
	pa->id = 11;
	pa->cnt = 22;
	blah();
}
