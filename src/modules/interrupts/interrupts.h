#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#define INTERRUPT_GATE 0x8e

void init_interrupts(unsigned long handler);
void enable_keyboard_interrupts();
void disable_keyboard_interrupts();

#endif //__INTERRUPTS_H__