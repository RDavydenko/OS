// В VGA режиме стандартно предоставляется поле из 25 строк в каждой по 80 символов
#define VGA_LINES 25
#define VGA_COLUMNS 80
#define VGA_SCREEN_SIZE VGA_LINES * VGA_COLUMNS

unsigned int cursor_location = 0; // Позиция курсора
char* vidptr = (char*)0xb8000; // Указатель на VGA область в памяти, куда можно писать текст (0 строка, 0 столбец)

// Вывод строки на экран до '\0'
void kprint(const char* str)
{
    unsigned int i = 0;
    while (str[i] != '\0')
    {
        vidptr[cursor_location++] = str[i++];
        vidptr[cursor_location++] = 0x07; // foreground
    }
}

// Очистить экран
void clear_screen()
{
    unsigned int i = 0;
    while (i < VGA_SCREEN_SIZE)
    {
        vidptr[i++] = ' '; // пробел
        vidptr[i++] = 0x07; // foreground
    }
}

void kmain()
{
    clear_screen();
    kprint("Hello wolrd!");
}