MEMORY {
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
}

SECTIONS {
	. = ORIGIN(rom);

	.vectors : {
		*(.vectors)
	} >rom

	.text : {
		__sec_text_begin = .;
		*(.text)
		*(.rodata)
		*(.rodata*)
		__sec_text_end = .;
	} >rom

	.data : {
		__sec_data_begin = .;
		*(.data)
		__sec_data_end = .;
	} >ram AT >rom

	. = ALIGN(4);

	.bss : {
		__sec_bss_begin = .;
		*(.bss)
		*(COMMON)
		__sec_bss_end = .;
	} >ram

	. = ALIGN(4);

	__sec_stack_begin = .;
	__sec_stack_end = ORIGIN(ram) + LENGTH(ram) - 4;
}

_end = .;
PROVIDE(end = .);