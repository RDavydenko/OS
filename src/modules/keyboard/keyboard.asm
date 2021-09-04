.global _keyboard_handler

_keyboard_handler:
	call keyboard_handler_c
	iret
