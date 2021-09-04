#include "output.h"

unsigned int cursor_location = 0; // Позиция курсора
unsigned int current_style = 0x07;
char* vidptr = (char*)0xb8000; // Указатель на начало видеопамяти

// Вывод строки на экран до '\0'
void kprint(const char* str)
{
    for (unsigned int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            cursor_location = ((cursor_location / (VGA_COLUMNS * 2)) + 1) * (VGA_COLUMNS * 2);
        }
        else if (str[i] == '\r')
        {
            cursor_location -= cursor_location % (VGA_COLUMNS * 2);
        }
        else 
        {
            vidptr[cursor_location++] = str[i];
            vidptr[cursor_location++] = current_style; // foreground
        }
    }
}

// Очистить экран
void clear_screen()
{
    unsigned int i = 0;
    while (i < VGA_SCREEN_SIZE)
    {
        vidptr[i++] = ' '; // пробел
        vidptr[i++] = current_style; // foreground
    }
}