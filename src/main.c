#include "flow_led_manager.h"
#include "soft_delay.h"
#include <mcs51/8051.h>
#include <stddef.h>

/// SFR for STC8H, set this SFR to 0 to make STC8H's P1 work like normal 8051's P1.
__sfr __at(0x91) P1M1;

__data unsigned int timer0_reset_value = 50;

void timer0_reload(void)
{
	TH0 = (65536UL - timer0_reset_value) / 256;
	TL0 = (65536UL - timer0_reset_value) % 256;
}

int led1_on(void *payload)
{
	(void)payload;
	P1_1 = 0;
	return 0;
}

int led1_off(void *payload)
{
	(void)payload;
	P1_1 = 1;
	return 0;
}

__pdata struct flow_led_manager led1;

void loop(void)
{
	flow_led_manager_grow(&led1);
	delay_ms(2);
}

void main(void)
{
	P1M1 = 0x00;

	timer0_reload();
	TMOD = 0x01;
	TF0 = 0;
	ET0 = 1;
	TR0 = 1;

	flow_led_manager_init(&led1, led1_on, led1_off, NULL);

	EA = 1;
	while (1)
		loop();
}

void t0_isr(void) __interrupt(1)
{
	timer0_reload();
	flow_led_manager_step(&led1);
}
