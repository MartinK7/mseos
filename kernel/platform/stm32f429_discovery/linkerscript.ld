MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
	SRAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 176K
	SDRAM (rwx) : ORIGIN = 0x90000000, LENGTH = 8192K
}

SECTIONS
{
	.text :
	{
		*(.ivt)
		*(.text)
		_rodata_start = .;
		*(.rodata)
		_rodata_end = .;
	} >FLASH
	
	.data :
	{
		_data_start = .;
		*(.data)
		_data_end = .;
	} >SRAM AT >FLASH

	.bss :
	{
		_bss_start = .;
		*(.bss)
		_bss_end = .;
	} >SRAM

	.kstack (NOLOAD) :
	{
		. = ALIGN(4);
		_kstack_bot = .;
		*(.kstack)
		_kstack_top = .;
	} >SRAM

	.kheap (NOLOAD) :
	{
		. = ALIGN(4);
		*(.kheap)
	} >SRAM
	
	.uheap (NOLOAD) :
	{
		. = ALIGN(4);
		*(.uheap)
	} >SDRAM
}

