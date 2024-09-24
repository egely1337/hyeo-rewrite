#ifndef TIMER_H
#define TIMER_H
#include <typedefs.h>
#include <isr.h>
#include <io.h>
#define TIMER_FREQUENCY (uint16_t)1193182
void timer_init(void);
#endif