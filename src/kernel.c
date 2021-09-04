#include "modules/output/output.h"
#include "modules/interrupts/interrupts.h"

void kmain()
{
    clear_screen();
    print("Welcome\nHello wolasdadrd!\nVasya\n");

    init_interrupts();
    enable_keyboard_interrupts();

    while(1);
}