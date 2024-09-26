/*
 *	file: timer.c
 *	author: egely1337
 *	purpose: PIT driver 
 */

#include <timer.h>
#include <terminal.h>
#include <sched.h>

HYEO_EXPORT void timer_handler(registers_t regs) {
	schedule();
}

void timer_init(void) {
	register_interrupt_handler(IRQ0, &timer_handler);
	uint16_t divisior = TIMER_FREQUENCY / 100;

	// init timer
	outb(0x43, 0x36);
	outb(0x40, LOW_16(divisior));
	outb(0x40, HIGH_16(divisior));
}