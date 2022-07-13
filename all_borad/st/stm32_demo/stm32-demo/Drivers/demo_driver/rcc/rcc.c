

/*******************************************************************************
*   include
* *****************************************************************************/
#include "stm32f103x6.h"

#include "rcc.h"

/*******************************************************************************
*   code
* *****************************************************************************/
void ConfigPeripheralClock(void)
{

#ifdef GPIOA_CLOCK_ENABLE
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
#endif

#ifdef USART_CLOCK_ENABLE
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
#endif



}


