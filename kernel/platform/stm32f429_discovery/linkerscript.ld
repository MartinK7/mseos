MEMORY
{
	FLASH (rx)  : ORIGIN = 0x00800000, LENGTH = 2048K
	SRAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 176K
	SDRAM (rwx) : ORIGIN = 0x40000000, LENGTH = 8192K
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
		_start_data = .;
		*(.data)
		_end_data = .;
	} >SRAM AT >FLASH

	.bss :
	{
		_start_bss = .;
		*(.bss)
		_end_bss = .;
	} >SRAM
	
	.stack (NOLOAD) :
	{
		. = ALIGN(4);
		*(.stack)
	} >SRAM
	
	.heap (NOLOAD) :
	{
		. = ALIGN(4);
		*(.heap)
	} >SDRAM	
}

