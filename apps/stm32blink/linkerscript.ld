SECTIONS
{
	.text : { *(.head) *(.text) }
	.data : { *(.rodata) *(.data) *(.bss) }
}

