/*
 *	file: timer.c
 *	author: egely1337
 *	purpose: PIT driver 
 */

#include <timer.h>
#include <terminal.h>
#include <sched.h>

uint32_t timer_to_schedule = 0;
HYEO_EXPORT void timer_handler(registers_t* regs) {
	// Increase timer.
	timer_to_schedule++;

	printf("timer");

	// Schedule
	schedule();
}

void timer_init(void) {
	// Initialize timer
	register_interrupt_handler(IRQ0, &timer_handler);
	uint16_t divisior = TIMER_FREQUENCY / 100;

	outb(0x43, 0x36);
	outb(0x40, LOW_16(divisior));
	outb(0x40, HIGH_16(divisior));
}