#include "flow_led_manager.h"

int flow_led_manager_init(struct flow_led_manager *self,
			  pwm_manager_op_fn_t on, pwm_manager_op_fn_t off, void *payload)
{
	self->direction = 1;
	self->target = 0;
	if (pwm_manager_init(&self->pwm, self->target, on, off, payload))
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

	if (pwm_manager_set_target(&self->pwm, self->target))
		return 1;

	return 0;
}

int flow_led_manager_step(struct flow_led_manager *self)
{
	return pwm_manager_step(&self->pwm);
}
