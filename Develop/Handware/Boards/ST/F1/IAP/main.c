/* **************************
 * 2023 - 2 - 12
 * su zhou
 * huke
 * *************************/

/* *****************************************************************************
 *	include
 * ************************************************************************** */
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "retarget.h"
#include <stdio.h>

/* *****************************************************************************
 *	code
 * ************************************************************************** */
static inline void RccInit(void)
{
    RCC_DeInit();
    RCC_HSICmd(ENABLE);
    while(RESET == RCC_GetFlagStatus(RCC_FLAG_HSIRDY));

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_1);

    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);

    RCC_PLLCmd(ENABLE);
    while (RESET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY));

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (0x08 != RCC_GetSYSCLKSource());
}

static inline void UsartInit(void)
{
    USART_InitTypeDef USART_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

    CLEAR_BIT(USART1->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
    CLEAR_BIT(USART1->CR3, (USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL));

    USART_Cmd(USART1, ENABLE);
}

int main(void)
{
    RccInit();
    UsartInit();
    RetargetInit(USART1);

    while (1)
    {
        // printf("hello world\r\n");
    }

    return 0;
}

