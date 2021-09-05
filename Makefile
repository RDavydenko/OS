MinGW = C:\MinGW\bin
gcc = C:\software\ghost-i686-elf-tools\bin
qemu = C:\Program Files\qemu

export PATH := $(MinGW);$(gcc);$(qemu)



all: modules kernel link run




modules: output interrupts keyboard input convert cursor utils
# При добавлении нового модуля добавить вручную папку до него. Например, src/modules/output
# Также добавить его компиляцию по аналогии с output или input (тут компилируется также asm-файл), заменив только путь и название файла
# Также добавить его объектный файл (*.o) из папки build в команду секции link
# Не забыть добавить также в build_and_run.bat

output:
	@i686-elf-gcc -c src/modules/output/output.c -o build/modules/output/output.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

interrupts:
	@i686-elf-gcc -c src/modules/interrupts/interrupts.c -o build/modules/interrupts/interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

keyboard:
	@i686-elf-gcc -c src/modules/keyboard/keyboard.c -o build/modules/keyboard/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

input: 
	@i686-elf-as src/modules/input/input.asm -o build/modules/input/input.asm.o
	@i686-elf-gcc -c src/modules/input/input.c -o build/modules/input/input.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

convert: 
	@i686-elf-gcc -c src/modules/convert/convert.c -o build/modules/convert/convert.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	
cursor:
	@i686-elf-gcc -c src/modules/cursor/cursor.c -o build/modules/cursor/cursor.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

utils: 
	@i686-elf-as src/modules/utils/utils.asm -o build/modules/utils/utils.asm.o
	




kernel:
	@i686-elf-as src/kernel.asm -o build/kernel.asm.o
	@i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra





link:
	@i686-elf-gcc -T build/linker.ld -o bin/boot/os.bin -ffreestanding -O2 -nostdlib build/kernel.o build/kernel.asm.o build/modules/output/output.o build/modules/interrupts/interrupts.o build/modules/keyboard/keyboard.o build/modules/input/input.o build/modules/input/input.asm.o build/modules/convert/convert.o build/modules/cursor/cursor.o build/modules/utils/utils.asm.o -lgcc





run:
	#@qemu-system-i386 -cdrom iso/os.iso
	@qemu-system-i386 -kernel bin/boot/os.bin
