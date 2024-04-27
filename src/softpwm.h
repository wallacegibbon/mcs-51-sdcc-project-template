#ifndef __SOFTPWM_H
#define __SOFTPWM_H

typedef int (*softpwm_on_fn_t)();
typedef int (*softpwm_off_fn_t)();

struct softpwm {
	unsigned char counter;
	unsigned char target;
	unsigned char next_target;
	/// flag to avoid calling `on` when it's already in `on` state. (same effect for `off` state)
	unsigned char signal_status;
	softpwm_on_fn_t on;
	softpwm_off_fn_t off;
};

int softpwm_init(struct softpwm *self, unsigned char target, softpwm_on_fn_t on, softpwm_off_fn_t off);
int softpwm_step(struct softpwm *self);
int softpwm_set_target(struct softpwm *self, unsigned char target);

#endif
