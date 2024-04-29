#include "soft_delay.h"

/// this is not a real delay_ms, use T0 and unsigned counter to do the soft delay later.
void delay_ms(unsigned int n)
{
	while (n--)
		delay_1ms();
}
