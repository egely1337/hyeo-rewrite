/*
 *  file: reboot.c
 *  author: egely1337
 *  purpose: rebooting 
 */


#include <reboot.h>

/*
 *	author: egely1337
 *	purpose: rebooting the operating system (8042 reset)
 *	params: no params
 */
void reboot() {
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    hlt();
}