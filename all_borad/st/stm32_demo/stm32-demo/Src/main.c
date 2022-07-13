
/*******************************************************************************
*   include
* *****************************************************************************/

#include "main.h"

#include "gpio.h"
#include "rcc.h"


/*******************************************************************************
*   code
* *****************************************************************************/
int main(void)
{
    ConfigPeripheralClock();
    ConfigGpio();
    while (1)
    {

    }
}


void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
