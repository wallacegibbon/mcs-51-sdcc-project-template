#include "softpwm.h"

int softpwm_init(struct softpwm *self, unsigned char target, softpwm_on_fn_t on, softpwm_off_fn_t off)
{
	if (target == 0)
		return 1;
	self->counter = 0;
	self->target = target;
	self->on = on;
	self->off = off;
	/// In this PWM mechanism, `on` on startup, `off` when reach target.
	self->on();
	return 0;
}

int softpwm_step(struct softpwm *self)
{
	unsigned char tmp;

	tmp = ++self->counter;
	if (tmp == 0) {
		self->target = self->next_target;
		return self->on();
	}

	if (tmp == self->target)
		return self->off();

	return 0;
}

int softpwm_set_target(struct softpwm *self, unsigned char target)
{
	if (target == 0)
		return 1;

	self->next_target = target;
	return 0;
}
