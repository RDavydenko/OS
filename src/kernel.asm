# Declare constants used for creating a multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# header загрузчика.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Стек.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 КБ
stack_top:

# The linker script specifies _start as the entry point to the kernel and the
# bootloader will jump to this position once the kernel has been loaded. It
# doesn't make sense to return from this function as the bootloader is gone.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp # Устанавливаем указатель стека
	call kmain # Вызываем функцию kmain из kernel.c
	cli # отключение прерываний
	hlt # завершение работы
.Lhang:
	jmp .Lhang

# Set the size of the _start symbol to the current location '.' minus its start.
# This is useful when debugging or when you implement call tracing.
.size _start, . - _start
