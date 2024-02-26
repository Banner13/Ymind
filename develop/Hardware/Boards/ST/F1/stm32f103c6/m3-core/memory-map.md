Table 3. Register boundary addresses
Boundary address
Peripheral
Bus
Register map

0xA000 0000 - 0xA000 0FFF
FSMC
AHB
Section 21.6.9 on page 564

0x5000 0000 - 0x5003 FFFF
USB OTG FS
Section 28.16.6 on page 913
0x4003 0000 - 0x4FFF FFFF
Reserved
-
0x4002 8000 - 0x4002 9FFF
Ethernet
Section 29.8.5 on page 1069
0x4002 3400 - 0x4002 7FFF
Reserved
-
0x4002 3000 - 0x4002 33FF
CRC
Section 4.4.4 on page 65
0x4002 2000 - 0x4002 23FF
Flash memory interface
-
0x4002 1400 - 0x4002 1FFF
Reserved
-
0x4002 1000 - 0x4002 13FF
Reset and clock control RCC
Section 7.3.11 on page 121
0x4002 0800 - 0x4002 0FFF
Reserved
-
0x4002 0400 - 0x4002 07FF
DMA2
Section 13.4.7 on page 289
0x4002 0000 - 0x4002 03FF
DMA1
0x4001 8400 - 0x4001 FFFF
Reserved
-
0x4001 8000 - 0x4001 83FF
SDIO
Section 22.9.16 on page 621
RM0008 Rev 20
51/1134
RM0008
Memory and bus architecture
62
0x4001 5800 - 0x4001 7FFF
Reserved
APB2
-
0x4001 5400 - 0x4001 57FF
TIM11 timer
Section 16.5.11 on page 468
0x4001 5000 - 0x4001 53FF
TIM10 timer
Section 16.5.11 on page 468
0x4001 4C00 - 0x4001 4FFF
TIM9 timer
Section 16.4.13 on page 458
0x4001 4000 - 0x4001 4BFF
Reserved
-
0x4001 3C00 - 0x4001 3FFF
ADC3
Section 11.12.15 on page 252
0x4001 3800 - 0x4001 3BFF
USART1
Section 27.6.8 on page 827
0x4001 3400 - 0x4001 37FF
TIM8 timer
Section 14.4.21 on page 363
0x4001 3000 - 0x4001 33FF
SPI1
Section 25.5 on page 742
0x4001 2C00 - 0x4001 2FFF
TIM1 timer
Section 14.4.21 on page 363
0x4001 2800 - 0x4001 2BFF
ADC2
Section 11.12.15 on page 252
0x4001 2400 - 0x4001 27FF
ADC1
0x4001 2000 - 0x4001 23FF
GPIO Port G
Section 9.5 on page 194
0x4001 1C00 - 0x4001 1FFF
GPIO Port F
0x4001 1800 - 0x4001 1BFF
GPIO Port E
0x4001 1400 - 0x4001 17FF
GPIO Port D
0x4001 1000 - 0x4001 13FF
GPIO Port C
0x4001 0C00 - 0x4001 0FFF
GPIO Port B
0x4001 0800 - 0x4001 0BFF
GPIO Port A
0x4001 0400 - 0x4001 07FF
EXTI
Section 10.3.7 on page 214
0x4001 0000 - 0x4001 03FF
AFIO
Section 9.5 on page 194
Table 3. Register boundary addresses (continued)
Boundary address
Peripheral
Bus
Register map
Memory and bus architecture
RM0008
52/1134
RM0008 Rev 20
0x4000 7800 - 0x4000 FFFF
Reserved
APB1
-
0x4000 7400 - 0x4000 77FF
DAC
Section 12.5.14 on page 273
0x4000 7000 - 0x4000 73FF
Power control PWR
Section 5.4.3 on page 80
0x4000 6C00 - 0x4000 6FFF
Backup registers (BKP)
Section 6.4.5 on page 85
0x4000 6400 - 0x4000 67FF
bxCAN1
Section 24.9.5 on page 695
0x4000 6800 - 0x4000 6BFF
bxCAN2
0x4000 6000(1) - 0x4000 63FF
Shared USB/CAN SRAM 512 bytes
-
0x4000 5C00 - 0x4000 5FFF
USB device FS registers
Section 23.5.4 on page 651
0x4000 5800 - 0x4000 5BFF
I2C2
Section 26.6.10 on page 784
0x4000 5400 - 0x4000 57FF
I2C1
0x4000 5000 - 0x4000 53FF
UART5
Section 27.6.8 on page 827
0x4000 4C00 - 0x4000 4FFF
UART4
0x4000 4800 - 0x4000 4BFF
USART3
0x4000 4400 - 0x4000 47FF
USART2
0x4000 4000 - 0x4000 43FF
Reserved
-
0x4000 3C00 - 0x4000 3FFF
SPI3/I2S
Section 25.5 on page 742
0x4000 3800 - 0x4000 3BFF
SPI2/I2S
Section 25.5 on page 742
0x4000 3400 - 0x4000 37FF
Reserved
-
0x4000 3000 - 0x4000 33FF
Independent watchdog (IWDG)
Section 19.4.5 on page 499
0x4000 2C00 - 0x4000 2FFF
Window watchdog (WWDG)
Section 20.6.4 on page 506
0x4000 2800 - 0x4000 2BFF
RTC
Section 18.4.7 on page 493
0x4000 2400 - 0x4000 27FF
Reserved
-
0x4000 2000 - 0x4000 23FF
TIM14 timer
Section 16.5.11 on page 468
0x4000 1C00 - 0x4000 1FFF
TIM13 timer
0x4000 1800 - 0x4000 1BFF
TIM12 timer
Section 16.4.13 on page 458
0x4000 1400 - 0x4000 17FF
TIM7 timer
Section 17.4.9 on page 481
0x4000 1000 - 0x4000 13FF
TIM6 timer
0x4000 0C00 - 0x4000 0FFF
TIM5 timer
Section 15.4.19 on page 423
0x4000 0800 - 0x4000 0BFF
TIM4 timer
0x4000 0400 - 0x4000 07FF
TIM3 timer
0x4000 0000 - 0x4000 03FF
TIM2 timer
