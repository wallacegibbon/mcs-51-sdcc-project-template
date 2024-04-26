#ifndef __BASIC_TIMER_H
#define __BASIC_TIMER_H

struct basic_timer0 {
	unsigned int reset_value;
	unsigned char is_running;
};

int basic_timer0_reload(struct basic_timer0 *self);
int basic_timer0_init(struct basic_timer0 *self, unsigned int reset_value);
int basic_timer0_run(struct basic_timer0 *self);
int basic_timer0_pause(struct basic_timer0 *self);

#endif
