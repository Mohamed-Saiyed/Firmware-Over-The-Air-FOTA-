ENTRY(Reset_Handler)



MEMORY
{
	FLASH(rx)	: ORIGIN = 0x08000000 , LENGTH = 64K
	SRAM(xrw)	: ORIGIN = 0x20000000 , LENGTH = 20K
}

SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);
		*(.isr_vector)
		. = ALIGN(4);	
		
	}> FLASH
	
	.text :
	{
		. = ALIGN(4);
		*(.text)
		*(.text.*)
		*(.eh_frame)
		*(.init)
		*(.fini)
		*(.init_*)
		*(.fini_*)
		. = ALIGN(4);
		_etext = . ;
		
	}> FLASH
	
	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		
	}> FLASH
	
	_la_data = LOADADDR(.data) ;
	
	.data :
	{
		. = ALIGN(4);
		_sdata = . ;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		_edata = . ;
		
	}> SRAM AT > FLASH
	
	.bss :
	{
		. = ALIGN(4);
		_sbss = . ;
		__bss_start__ = _sbss;
		*(.bss)
		*(.bss.*)
		*(.comment)
		. = ALIGN(4);
		_ebss = . ;
		__bss_end__ = _ebss ;
		_exit = _ebss ;
		
	}> SRAM AT > FLASH
	
}
