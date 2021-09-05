#include "cursor.h"

extern void _write_port(int port_number, int value);

// https://wiki.osdev.org/Text_Mode_Cursor

void disable_cursor()
{
	_write_port(0x3D4, 0x0A);
	_write_port(0x3D5, 0x20);
}
