#include "warning.h"
#include <mcs51/8051.h>

__data unsigned char *d1;
__idata unsigned char *d2;
__pdata unsigned char *d3;
__xdata unsigned char *d4;
__code unsigned char *d5;
unsigned char *d6;

void main(void)
{
	P1_1 = 0;
	P2 = sizeof(d1);
	P2 = sizeof(d2);
	P2 = sizeof(d3);
	P2 = sizeof(d4);
	P2 = sizeof(d5);
	P2 = sizeof(d6);
	blah();
}
