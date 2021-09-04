call vars.cmd

SET "PATH=%minGW%;%gcc%;%qemu%;%PATH%"

:: При добавлении нового модуля:
:: Добавить его в компиляцию (по аналогии с output), предварительно создав для него папку (иначе будет падать с ошибкой)
:: Добавить его в параметры линковки (по аналогии с output)
:: Не забыть добавить также в Makefile

:: Компиляция
i686-elf-as src/kernel.asm -o build/kernel.asm.o
i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/modules/output/output.c -o build/modules/output/output.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

:: Линковка
cd build
i686-elf-gcc -T linker.ld -o ../bin/boot/os.bin -ffreestanding -O2 -nostdlib kernel.o kernel.asm.o modules/output/output.o -lgcc
cd ..

@REM If you can get grub-mkrescue:

REM qemu-system-i386 -cdrom iso/os.iso

@REM Else, boot directly:

echo "Build Succeed"

qemu-system-i386 -kernel bin/boot/os.bin

pause
