# ---------------------------
# 2023 - 2 - 11
# su zhou
# huke
# ---------------------------
.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

/* STM32F103C6T6 RAM and FLASH */
.global __RAM, __RAM_SIZE, __FLASH, __FLASH_SIZE
.equ  __RAM,            0x20000000
.equ  __RAM_SIZE,       0x00002800      /* 10K RAM */
.equ  __FLASH,          0x08000000
.equ  __FLASH_SIZE,     0x00008000      /* 32K FLASH */

__stack_top = __RAM + __RAM_SIZE; 

/* copy form stm32_startup.s */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

/* linker script entry */

/* set sp */
.section .set_stack,"a",%progbits
.word __stack_top
.size .set_stack, .-.set_stack

/* boot entry */
.section .boot_entry,"a",%progbits
.word Reset_Handler
.size .boot_entry, .-.boot_entry

/* reset entry */
.section .text.code
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
/* need copy data,bss form FLASH to RAM  - code form stm32*/
/* Copy the data segment initializers from flash to SRAM */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    movs r3, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

LoopCopyDataInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc CopyDataInit
  
/* Zero fill the bss segment. */
    ldr r2, =_sbss
    ldr r4, =_ebss
    movs r3, #0
    b LoopFillZerobss

FillZerobss:
    str  r3, [r2]
    adds r2, r2, #4

LoopFillZerobss:
    cmp r2, r4
    bcc FillZerobss

    bl main
    bl Error_Loop

Error_Loop:
    b Error_Loop
.size Reset_Handler, .-Reset_Handler



