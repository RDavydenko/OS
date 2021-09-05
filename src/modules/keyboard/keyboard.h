#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

int keyboard_get_keycode();
char get_char_from_keycode(int keycode);

#endif //__KEYBOARD_H__