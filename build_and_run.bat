call vars.cmd

SET "PATH=%minGW%;%gcc%;%qemu%;%PATH%"

:: При добавлении нового модуля:
:: Добавить его в компиляцию (по аналогии с output), предварительно создав для него папку (иначе будет падать с ошибкой)
:: Добавить его в параметры линковки (по аналогии с output)
:: Не забыть добавить также в Makefile

:: Компиляция
:: Kernel
i686-elf-as src/kernel.asm -o build/kernel.asm.o
i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
:: Output
i686-elf-gcc -c src/modules/output/output.c -o build/modules/output/output.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
:: Interrupts
i686-elf-gcc -c src/modules/interrupts/interrupts.c -o build/modules/interrupts/interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
:: Keyboard
i686-elf-as src/modules/keyboard/keyboard.asm -o build/modules/keyboard/keyboard.asm.o
i686-elf-gcc -c src/modules/keyboard/keyboard.c -o build/modules/keyboard/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra


:: Линковка
cd build
i686-elf-gcc -T build/linker.ld -o bin/boot/os.bin -ffreestanding -O2 -nostdlib build/kernel.o build/kernel.asm.o build/modules/output/output.o build/modules/interrupts/interrupts.o build/modules/keyboard/keyboard.o build/modules/keyboard/keyboard.asm.o -lgcc
cd ..

@REM If you can get grub-mkrescue:

REM qemu-system-i386 -cdrom iso/os.iso

@REM Else, boot directly:

echo "Build Succeed"

qemu-system-i386 -kernel bin/boot/os.bin

pause
