#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#define INTERRUPT_GATE 0x8e

typedef struct idt_descr {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
} IDT_Descriptor;

void init_interrupts();
void enable_keyboard_interrupts();
void disable_keyboard_interrupts();

#endif //__INTERRUPTS_H__