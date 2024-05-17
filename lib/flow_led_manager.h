#ifndef __FLOW_LED_MANAGER_H
#define __FLOW_LED_MANAGER_H

#include "pwm_manager.h"

struct flow_led_manager {
	struct pwm_manager pwm;
	unsigned char target;
	unsigned char direction;
};

int flow_led_manager_init(struct flow_led_manager *self,
			  pwm_manager_op_fn_t on, pwm_manager_op_fn_t off, void *payload);

int flow_led_manager_grow(struct flow_led_manager *self);

int flow_led_manager_step(struct flow_led_manager *self);

#endif
