ENTRY(_start)

MEMORY
{
    ram (wx) : ORIGIN = 0x20000000, LENGTH = 320K		/*max 320k*/
}

MEMORY
{
    bssram (wx) : ORIGIN = 0x20050000, LENGTH = 96K  	/*max 96k*/
}

SECTIONS
{
    .text 0x20000000 : 
    {
        *(.text.vector)
		*(.text.irq_entry)
        *(.text.startup)
        *(.text)
        *(.rodata)
        *(.rodata.*)
		*(.data)
        . = ALIGN(32);
        *(.fat_temp)
		. = ALIGN(32);
		*(.usb_var_cbw)
		. = ALIGN(32);
		*(.usb_dat_buf)
		
    } > ram
		
    .bss 0x20050000 : 
    {
        __bss_start = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .; 
    } > bssram
	

	
	
	/*PROVIDE(__rdat = 0x21000000);*/
}
