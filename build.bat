call vars.cmd

SET "PATH=%minGW%;%gcc%;%qemu%;%PATH%"

i686-elf-as src/kernel.asm -o build/kernel.asm.o
i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

cd build
i686-elf-gcc -T linker.ld -o ../bin/boot/os.bin -ffreestanding -O2 -nostdlib kernel.o kernel.asm.o -lgcc
cd ..

@REM If you can get grub-mkrescue:

REM grub-mkrescue -o iso/os.iso bin

@REM Else, boot directly:

echo "Build Succeed"

pause