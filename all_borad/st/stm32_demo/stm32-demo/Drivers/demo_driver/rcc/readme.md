

###RCC
	RCC用于配置、控制时钟源。CPU作为系统的大脑，而时钟是一个系统的心脏。
	
	在STM32F103中、默认使用了8MHz的HSI来作为系统时钟源。你也可以使用HSE或者是PLL时钟。
	// PLL(Phase Locked Loop)： 为锁相回路或锁相环，用来统一整合时钟信号，使高频器件正常工作，如内存的存取资料等。

	在修改系统时钟源时、需要注意的问题：
	经过配置后的时钟作用在AHB总线上、相当于主动脉、也可以理解为系统时钟吧。

	HSI与HSE的区别在于两点：
	一、启动速度			HSI > HSE
	二、准确性			HSE > HSI

	PLL需要配置，可以根据需要选择HSI或者HSE来配置。

	系统时钟源的影响：
	All 连接在AHB上的外设。
	需要特殊注意的有：
		1.Flash 根据时钟频率，调整读、写时的延迟。
			/* 48 < SYSCLK <= 72 => 2WS (3 CPU cycles) */
			/* 24 < SYSCLK <= 48 => 1WS (2 CPU cycles) */
			/* else SYSCLK < 24MHz default LL_FLASH_LATENCY_0 0WS */
		2.在STM32F103中的USB需要使用48MHz的固定频率。
	
	so,我现在对时钟并没有特殊要求，决定使用默认系统时钟，8Mhz的HSI。
###留坑：
	RCC也可以用于复位相关工作、暂时不用。
	需要与Cortex系统时钟分别开来(显然我现在还不明白Cortex系统时钟的作用，不然我会说的清楚一点)。
