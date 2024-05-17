#include "pwm_manager.h"

int pwm_manager_init(struct pwm_manager *self, unsigned char target,
		     pwm_manager_op_fn_t on, pwm_manager_op_fn_t off, void *payload)
{
	self->counter = 0;
	self->next_target = target;
	self->signal_status = 0;
	self->on = on;
	self->off = off;
	self->payload = payload;
	/// call `off` on initialization.
	self->off(self->payload);
	return 0;
}

int pwm_manager_signal_on(struct pwm_manager *self)
{
	self->target = self->next_target;

	/// if the target is 0 (the minimum number), never call `on`.
	if (self->target == 0)
		return 0;
	if (self->signal_status == 1)
		return 0;

	self->signal_status = 1;
	return self->on(self->payload);
}

int pwm_manager_signal_off(struct pwm_manager *self)
{
	/// if the target is 255 (the maximum number), never call `off`.
	if (self->target == 255)
		return 0;
	if (self->signal_status == 0)
		return 0;

	self->signal_status = 0;
	return self->off(self->payload);
}

int pwm_manager_step(struct pwm_manager *self)
{
	/// The initial value of `counter` is 0, so when `signal_on` failed, stay on 0 and keep trying.
	if (self->counter == 0) {
		if (!pwm_manager_signal_on(self))
			self->counter++;
	} else if (self->counter == self->target) {
		if (!pwm_manager_signal_off(self))
			self->counter++;
	} else {
		self->counter++;
	}
	return 0;
}

int pwm_manager_set_target(struct pwm_manager *self, unsigned char target)
{
	self->next_target = target;
	return 0;
}
