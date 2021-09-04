MinGW = C:\MinGW\bin
gcc = C:\software\ghost-i686-elf-tools\bin
qemu = C:\Program Files\qemu

export PATH := $(MinGW);$(gcc);$(qemu)



all: modules kernel link run



modules: output interrupts keyboard
# При добавлении нового модуля добавить вручную папку до него. Например, src/modules/output
# Также добавить его компиляцию по аналогии с output, заменив только путь и название файла
# Также добавить его объектный файл (*.o) в команду секции link
# Не забыть добавить также в build_and_run.bat

output:
	@i686-elf-gcc -c src/modules/output/output.c -o build/modules/output/output.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

interrupts:
	@i686-elf-gcc -c src/modules/interrupts/interrupts.c -o build/modules/interrupts/interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

keyboard:
	@i686-elf-as src/modules/keyboard/keyboard.asm -o build/modules/keyboard/keyboard.asm.o
	@i686-elf-gcc -c src/modules/keyboard/keyboard.c -o build/modules/keyboard/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wchar-subscripts



kernel:
	@i686-elf-as src/kernel.asm -o build/kernel.asm.o
	@i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra



link:
	@i686-elf-gcc -T build/linker.ld -o bin/boot/os.bin -ffreestanding -O2 -nostdlib build/kernel.o build/kernel.asm.o build/modules/output/output.o build/modules/interrupts/interrupts.o build/modules/keyboard/keyboard.o build/modules/keyboard/keyboard.asm.o -lgcc



run:
	#@qemu-system-i386 -cdrom iso/os.iso
	@qemu-system-i386 -kernel bin/boot/os.bin
