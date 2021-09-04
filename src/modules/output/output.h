#ifndef __OUTPUT_H__
#define __OUTPUT_H__

// В VGA режиме стандартно предоставляется поле из 25 строк в каждой по 80 символов
#define VGA_LINES 25
#define VGA_COLUMNS 80
#define VGA_SCREEN_SIZE VGA_LINES * VGA_COLUMNS

void print(const char* str);
void print_char(char ch);
void clear_screen();

#endif //__OUTPUT_H__