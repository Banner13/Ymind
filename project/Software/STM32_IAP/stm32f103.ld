/* **************************
 * 2023 - 2 - 11
 * su zhou
 * huke
 * *************************/

/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
RAM (xrw)       : ORIGIN = __RAM, LENGTH = __RAM_SIZE
FLASH (rx)      : ORIGIN = __FLASH, LENGTH = __FLASH_SIZE
}

/* Define output sections */
SECTIONS
{
    /* first set sp(stack) when power up , 
        then call boot_entry */
    . = ALIGN(4);
    .set_stack :
    {
        KEEP(*(.set_stack))
    } >FLASH

    /* jump to the target address , 
    that usually points to the Reset_Handler */
    . = ALIGN(4);
    .boot_entry :
    {
        KEEP(*(.boot_entry))
    } >FLASH
  
    /* code */
    . = ALIGN(4);
    .text :
    {
        *(.text)           /* .text sections (code) */
        *(.text*)
    } >FLASH

    /* only read data */
    . = ALIGN(4);
    .rodata :
    {
        *(.rodata)           /* .rodata sections (only read data) */
        *(.rodata*)
    } >FLASH

    . = ALIGN(4);
    _sidata = LOADADDR(.data);
    /* initialized data */
    .data :
    {
        _sdata = .;
        *(.data)           /* .data sections (data) */
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT> FLASH

    /* not initialized data */
    . = ALIGN(4);
    .bss :
    {
        _sbss = .; 
        *(.bss)             /* .bss sections (data) */
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;  
        end = __bss_end__; /* c need '__bss_end__' */
    } >RAM
}


