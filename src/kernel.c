#include "modules/output/output.h"
#include "modules/input/input.h"
#include "modules/keyboard/keyboard.h"
#include "modules/cursor/cursor.h"
#include "modules/convert/convert.h"

void kmain()
{
    clear_screen();

    disable_cursor();

    print("Welcome\nHello wolasdadrd!\nVasya\n");

    // char* line = get_line();
    // print("Your line: ");
    // print(line);

    // Получение любой клавиши
    print("Your keycode: ");
    int keycode = get_keycode();
    print(itoa(keycode));
    print(". This is char: ");
    char ch = get_char_from_keycode(keycode);
    print_char(ch);
    print(". ASCII code: ");
    print(itoa((int)ch));

    // Получение только символа
    print("\nYour char: ");
    ch = get_char();
    print_char(ch);

    // Получение строки
    print("\nEnter your string: ");
    char* str = get_line();
    print("Your string: ");
    print(str);
}