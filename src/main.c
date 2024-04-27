#include "basic_timer.h"
#include "softpwm.h"
#include <mcs51/8051.h>

__sfr __at(0x91) P1M1;

__xdata struct basic_timer0 t0;

/// this is not a real delay_ms, use T0 and unsigned counter to do the soft delay later.
void delay_ms(unsigned int n)
{
	int i, j;
	while (n--) {
		for (i = 0; i < 8; i++)
			for (j = 0; j < 128; j++)
				;
	}
}

int led1_on()
{
	P1_1 = 0;
	return 0;
}

int led1_off()
{
	P1_1 = 1;
	return 0;
}

struct flow_led_manager {
	struct softpwm pwm;
	unsigned char target;
	unsigned char direction;
};

int flow_led_manager_init(struct flow_led_manager *self)
{
	self->direction = 1;
	self->target = 0;
	if (softpwm_init(&self->pwm, self->target, led1_on, led1_off))
		return 1;
	return 0;
}

int flow_led_manager_grow(struct flow_led_manager *self)
{
	if (self->direction) {
		self->target++;
		if (self->target == 255)
			self->direction = 0;
	} else {
		self->target--;
		if (self->target == 0)
			self->direction = 1;
	}

	if (softpwm_set_target(&self->pwm, self->target))
		return 1;

	return 0;
}

int flow_led_manager_step(struct flow_led_manager *self)
{
	return softpwm_step(&self->pwm);
}

__pdata struct flow_led_manager led1;

void main()
{
	P1M1 = 0x00;

	basic_timer0_init(&t0, 50);
	basic_timer0_run(&t0);

	flow_led_manager_init(&led1);

	EA = 1;

	while (1) {
		flow_led_manager_grow(&led1);
		delay_ms(8);
	}
}

void t0_isr() __interrupt(1)
{
	basic_timer0_reload(&t0);
	flow_led_manager_step(&led1);
}
