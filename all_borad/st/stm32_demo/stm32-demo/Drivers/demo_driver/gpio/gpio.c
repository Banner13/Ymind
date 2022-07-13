


/*******************************************************************************
*   include
* *****************************************************************************/
#include "stm32f103x6.h"

#include "gpio.h"

/*******************************************************************************
*   code
* *****************************************************************************/
void ConfigGpio(void)
{

    GPIOA->CRH |= GPIO_CRH_MODE9_1;
    GPIOA->CRH |= GPIO_CRH_MODE10_1;
    
    GPIOA->CRH &= ~GPIO_CRH_CNF9_Msk;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_Msk;

    GPIOA->BSRR |= GPIO_BSRR_BS9;
    GPIOA->BSRR |= GPIO_BSRR_BS10;


}



