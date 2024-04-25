#include "warning.h"
#include <mcs51/8051.h>

void main(void)
{
	P1_1 = 0;
	P2_1 = 1;
	blah();
}
