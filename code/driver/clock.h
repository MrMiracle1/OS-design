#ifndef __DRIVER_CLOCK_H__
#define __DRIVER_CLOCK_H__

#include <libs/ctype.h>

extern volatile size_t ticks;

void clock_init(void);

#endif /* !__KERN_DRIVER_CLOCK_H__ */