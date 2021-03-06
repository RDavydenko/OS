#include "interrupts.h"

extern int _read_port(int port_number);
extern void _write_port(int port_number, int value);
extern void _init_interrupts(long unsigned int *idt_ptr);

typedef struct idt_descr {
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
} IDT_Descriptor;

IDT_Descriptor IDT[256];

void init_interrupts(unsigned long handler)
{
	/* setting up interrupts to work with keyboard */
	IDT[0x21].offset_lowerbits = handler & 0xffff;
	IDT[0x21].selector = 0x08;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].offset_higherbits = (handler & 0xffff0000) >> 16;

	_write_port(0x20, 0x11);
	_write_port(0xA0, 0x11);

	_write_port(0x21, 0x20);
	_write_port(0xA1, 0x28);

	_write_port(0x21, 0x00);
	_write_port(0xA1, 0x00);

	_write_port(0x21, 0x01);
	_write_port(0xA1, 0x01);

	_write_port(0x21, 0b11111111);
	_write_port(0xA1, 0b11111111);

	/* fill the IDT descriptors */
	unsigned long idt_address = (unsigned long)IDT;
    unsigned long idt_ptr[2];
	idt_ptr[0] = (sizeof (IDT_Descriptor) * 256) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

    /* push IDT to ram */
	_init_interrupts(idt_ptr);
}

void enable_keyboard_interrupts()
{
    _write_port(0x21 , 0b11111101); // Enable IRQ1
}

void disable_keyboard_interrupts()
{
    _write_port(0x21 , 0b11111111); // Disable IRQ1
}
