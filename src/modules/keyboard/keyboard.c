#include "keyboard.h"
#include "../output/output.h"

extern int _read_port(int port_number);
extern void _write_port(int port_number, int value);

int keyboard_get_keycode()
{
    int keycode = 0;

	/* write EOI */
	_write_port(0x20, 0x20);

	unsigned char status = _read_port(KEYBOARD_STATUS_PORT);

	if (status & 0x01)
	{
		keycode = _read_port(KEYBOARD_DATA_PORT);
        return keycode;
	}

    return keycode;
}


/*
  This array is taken from http://www.osdever.net/bkerndev/Docs/keyboard.htm
*/
const char KEYBOARD_MAP[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

char get_char_from_keycode(int keycode)
{
    return KEYBOARD_MAP[(char)keycode];
}