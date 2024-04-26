#include "basic_timer.h"
#include <mcs51/8051.h>

int basic_timer0_init(struct basic_timer0 *self, unsigned int reset_value)
{
	self->reset_value = reset_value;
	self->is_running = 0;

	if (basic_timer0_reload(self))
		return 1;

	TMOD = 0x01;
	TF0 = 0;
	ET0 = 1;

	return 0;
}

int basic_timer0_reload(struct basic_timer0 *self)
{
	TH0 = (65536UL - self->reset_value) / 256;
	TL0 = (65536UL - self->reset_value) % 256;
	return 0;
}

int basic_timer0_run(struct basic_timer0 *self)
{
	TR0 = 1;
	self->is_running = 1;
	return 0;
}

int basic_timer0_pause(struct basic_timer0 *self)
{
	TR0 = 0;
	self->is_running = 0;
	return 0;
}
