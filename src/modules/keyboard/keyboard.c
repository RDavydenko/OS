#include "keyboard.h"
#include "../output/output.h"

extern int _read_port(int port_number);
extern void _write_port(int port_number, int value);

void keyboard_handler_c()
{
    int keycode = 0;

	/* write EOI */
	_write_port(0x20, 0x20);

	unsigned char status = _read_port(KEYBOARD_STATUS_PORT);

	if (status & 0x01)
	{
		keycode = _read_port(KEYBOARD_DATA_PORT);

        if(!(keycode < 0))
        {
            print_char(KEYBOARD_MAP[(char)keycode]);
        }

        //return keycode;
	}

    //return keycode;
}
