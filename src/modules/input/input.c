#include "input.h"
#include "../keyboard/keyboard.h"
#include "../interrupts/interrupts.h"
#include "../output/output.h"

int keycode = -1;
char str[INPUT_STR_SIZE];
unsigned int str_index = 0;
unsigned long current_handler = 0;

extern void _get_key_handler();

extern void _asm_hlt(); // Инструкция hlt

void get_key_handler_c()
{
    keycode = keyboard_get_keycode();
}

void try_change_handler(unsigned long handler)
{
    if (current_handler != handler)
    {
        init_interrupts(handler);    
        current_handler = handler;
    }
}

int get_keycode()
{
    keycode = -1;

    try_change_handler((unsigned long)_get_key_handler);
    enable_keyboard_interrupts();

    while (keycode == -1)
    {
        _asm_hlt();
    }

    disable_keyboard_interrupts();

    return keycode;
}

char* available_chars =     "0123456789-=+?.,';:[]{}!@#$%^&*()_\\|`~\"/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* available_chars_all = "0123456789-=+?.,';:[]{}!@#$%^&*()_\\|`~\"/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n\t ";

char get_char_inernal(char* available_symbols)
{
    int keycode;
    char ch;
    int containsIn; // TODO: bool
    do
    {
        containsIn = 0;
        keycode = get_keycode();
        ch = get_char_from_keycode(keycode);

        // TODO: модуль arrays : bool contains(char element, char* array)
        for (int i = 0; available_symbols[i] != '\0'; i++)
        {
            if (available_symbols[i] == ch)
            {
                containsIn = 1;
            }
        }
    } while (containsIn != 1);
    
    return ch;
}

char get_char()
{
    return get_char_inernal(available_chars);
}


// TODO: пока все строки записываются в одну область памяти
// Надо либо расширить область и записывать после '\0' предыдущей строки каждую последующую
// Либо добавить возможность выделять память и освобождать ее и немного переделать здесь реализацию
char* get_line()
{
    str_index = 0;
    char ch = '\0';

    // TODO: обезопасить - выход за пределы выделенной памяти str
    do
    {
        ch = get_char_inernal(available_chars_all);
        print_char(ch);
        str[str_index++] = ch;
    } while (ch != '\n');

    str[str_index] = '\0';

    return &str[0];
}
