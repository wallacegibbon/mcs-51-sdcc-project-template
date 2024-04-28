#ifndef __SOFTPWM_H
#define __SOFTPWM_H

typedef int (*softpwm_op_fn_t)(void *unused_var1, void *unused_var2, void *unused_var3);

struct softpwm {
	unsigned char counter;
	unsigned char target;
	unsigned char next_target;
	/// flag to avoid calling `on` when it's already in `on` state. (same effect for `off` state)
	unsigned char signal_status;
	softpwm_op_fn_t on;
	softpwm_op_fn_t off;
};

int softpwm_init(struct softpwm *self, unsigned char target, softpwm_op_fn_t on, softpwm_op_fn_t off);
int softpwm_step(struct softpwm *self);
int softpwm_set_target(struct softpwm *self, unsigned char target);

#endif
