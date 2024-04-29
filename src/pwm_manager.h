#ifndef __PWM_MANAGER_H
#define __PWM_MANAGER_H

typedef int (*pwm_manager_op_fn_t)(void *unused_var1, void *unused_var2, void *unused_var3);

struct pwm_manager {
	unsigned char counter;
	unsigned char target;
	unsigned char next_target;
	/// flag to avoid calling `on` when it's already in `on` state. (same effect for `off` state)
	unsigned char signal_status;
	pwm_manager_op_fn_t on;
	pwm_manager_op_fn_t off;
};

int pwm_manager_init(struct pwm_manager *self, unsigned char target, pwm_manager_op_fn_t on, pwm_manager_op_fn_t off);

int pwm_manager_step(struct pwm_manager *self);

int pwm_manager_set_target(struct pwm_manager *self, unsigned char target);

#endif
