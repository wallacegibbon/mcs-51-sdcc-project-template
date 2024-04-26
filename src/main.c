#include "warning.h"
#include <mcs51/8051.h>

/// For more details on this topic (__data, __xdata, etc.),
/// Search for "intrinsic named address spaces" (or "storage classes" in old releases) in documents.

__data unsigned char *d1;
__idata unsigned char *d2;
__pdata unsigned char *d3;
__xdata unsigned char *d4;
__code unsigned char *d5;
unsigned char *d6;

struct my_record {
	unsigned int id;
	unsigned char cnt;
};

int my_record_init(struct my_record *self, int id, int cnt)
{
	self->id = id;
	self->cnt = cnt;
	return 0;
}

int my_record_next(struct my_record *self)
{
	return self->cnt++;
}

__pdata struct my_record a, *pa;

void main(void)
{
	unsigned char tmp;
	P1_1 = 0;
	P2 = sizeof(d1);
	P2 = sizeof(d2);
	P2 = sizeof(d3);
	P2 = sizeof(d4);
	P2 = sizeof(d5);
	P2 = sizeof(d6);
	a.id = 1;
	a.cnt = 2;
	pa->id = 11;
	pa->cnt = 22;

	my_record_init(pa, 11, 0);
	tmp = my_record_next(pa);
	blah();
}
