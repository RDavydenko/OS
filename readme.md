Разработка ОС в Windows
===============================================

Необходимо
----------------------------

- MinGW
	- Скачать и установить http://www.mingw.org/download/installer
	- Установить в `C:\MinGW\`
- i686-elf компилятор (GCC)
	- Скачать и распаковать https://drive.google.com/file/d/0B85K_c7mx3QjUnZuaFRPWlBIcXM/edit?usp=sharing
	- Распаковать в `C:\software\ghost-i686-elf-tools` так, чтобы следующей была папка `bin`: `C:\software\ghost-i686-elf-tools\bin`
- QEMU (эмулятор)
	- Скачать последний x64 установщик из http://qemu.weilnetz.de/w64/
	- Установить в `C:\Program Files\qemu`


Сборка и запуск ОС
----------------------------

1. Установите все указанное выше
2. Отредактируйте `vars.cmd` так, чтобы переменные указывали на папки, куда устанавливались программы:
	- установите `minGW` переменную в директорию `bin` MinGW: `SET "minGW=C:\MinGW\bin"`
	- установите `gcc` перменную в папку `bin` компилятора `gcc`: `SET "gcc=C:\software\ghost-i686-elf-tools\bin"`
	- установите `qemu` переменную в папку с эмулятором `qemu`: `SET "qemu=C:\Program Files\qemu"`
3. Запустите `build_and_run.bat`, чтобы собрать ОС и запустить в QEMU
	- Запустите `build.bat` чтобы собрать ОС
	- Запустите `run.bat` чтобы запустить ОС в QEMU.(подразумевается, что сборка была произведена раньше)


Структура проекта
----------------------------
bin/boot - os.bin - бинарник ОС
bin/boot/grub - grub.cfg - конфигурация Grub

build - linker.ld - файл конфигурации линкера
build - *.o - объектные файлы

src - исходный код ОС
src - kernel.* - исходники ядра

vars.cmd - файл с переменными
build.bat - батник для билда ОС и запусука ее в QEMU
run.bat - батник для запуска ОС в QEMU


Полезные ссылки о разработки ОС
----------------------------

- [OSdev.org](http://wiki.osdev.org)
