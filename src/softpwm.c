#include "softpwm.h"

int softpwm_init(struct softpwm *self, unsigned char target, softpwm_on_fn_t on, softpwm_off_fn_t off)
{
	self->counter = 0;
	self->target = target;
	self->next_target = target;
	self->signal_status = 0;
	self->on = on;
	self->off = off;
	return 0;
}

static int softpwm_signal_on(struct softpwm *self)
{
	/// if the target is 0 (the minimum number), never call `on`.
	if (self->next_target == 0)
		return 1;

	self->target = self->next_target;

	/// do not call `off` if it's already off.
	if (self->signal_status == 1)
		return 0;

	self->signal_status = 1;
	return self->on();
}

static int softpwm_signal_off(struct softpwm *self)
{
	/// if the target is 255 (the maximum number), never call `off`.
	if (self->target == 255)
		return 0;

	/// do not call `off` if it's already off.
	if (self->signal_status == 0)
		return 0;

	self->signal_status = 0;
	return self->off();
}

int softpwm_step(struct softpwm *self)
{
	/// The initial value of `counter` is 0, so when `signal_on` failed, stay on 0 and keep trying.
	if (self->counter == 0) {
		if (!softpwm_signal_on(self))
			self->counter++;
	} else if (self->counter == self->target) {
		if (!softpwm_signal_off(self))
			self->counter++;
	} else {
		self->counter++;
	}
	return 0;
}

int softpwm_set_target(struct softpwm *self, unsigned char target)
{
	self->next_target = target;
	return 0;
}
