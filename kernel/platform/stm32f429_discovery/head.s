	.section .ivt
	.word     _stack       /* _estack */
	.word     _reset       /* Reset_Handler */
	.word     _loop        /* NMI_Handler */
	.word     _loop        /* HardFault_Handler */
	.word     _loop        /* MemManage_Handler */
	.word     _loop        /* BusFault_Handler */
	.word     _loop        /* UsageFault_Handler */
	.word     0            /* 0 */
	.word     0            /* 0 */
	.word     0            /* 0 */
	.word     0            /* 0 */
	.word     _loop        /* SVC_Handler */
	.word     _loop        /* DebugMon_Handler */
	.word     0            /* 0 */
	.word     _loop        /* PendSV_Handler */
	.word     _loop        /* SysTick_Handler */
	/* External Interrupts */
	.word     _loop        /* Window WatchDog              */
	.word     _loop        /* PVD through EXTI Line detection */
	.word     _loop        /* Tamper and TimeStamps through the EXTI line */
	.word     _loop        /* RTC Wakeup through the EXTI line */
	.word     _loop        /* FLASH                        */
	.word     _loop        /* RCC                          */
	.word     _loop        /* EXTI Line0                   */
	.word     _loop        /* EXTI Line1                   */
	.word     _loop        /* EXTI Line2                   */
	.word     _loop        /* EXTI Line3                   */
	.word     _loop        /* EXTI Line4                   */
	.word     _loop        /* DMA1 Stream 0                */
	.word     _loop        /* DMA1 Stream 1                */
	.word     _loop        /* DMA1 Stream 2                */
	.word     _loop        /* DMA1 Stream 3                */
	.word     _loop        /* DMA1 Stream 4                */
	.word     _loop        /* DMA1 Stream 5                */
	.word     _loop        /* DMA1 Stream 6                */
	.word     _loop        /* ADC1, ADC2 and ADC3s         */
	.word     _loop        /* CAN1 TX                      */
	.word     _loop        /* CAN1 RX0                     */
	.word     _loop        /* CAN1 RX1                     */
	.word     _loop        /* CAN1 SCE                     */
	.word     _loop        /* External Line[9:5]s          */
	.word     _loop        /* TIM1 Break and TIM9          */
	.word     _loop        /* TIM1 Update and TIM10        */
	.word     _loop        /* TIM1 Trigger and Commutation and TIM11 */
	.word     _loop        /* TIM1 Capture Compare         */
	.word     _loop        /* TIM2                         */
	.word     _loop        /* TIM3                         */
	.word     _loop        /* TIM4                         */
	.word     _loop        /* I2C1 Event                   */
	.word     _loop        /* I2C1 Error                   */
	.word     _loop        /* I2C2 Event                   */
	.word     _loop        /* I2C2 Error                   */
	.word     _loop        /* SPI1                         */
	.word     _loop        /* SPI2                         */
	.word     _loop        /* USART1                       */
	.word     _loop        /* USART2                       */
	.word     _loop        /* USART3                       */
	.word     _loop        /* External Line[15:10]s        */
	.word     _loop        /* RTC Alarm (A and B) through EXTI Line */
	.word     _loop        /* USB OTG FS Wakeup through EXTI line */
	.word     _loop        /* TIM8 Break and TIM12         */
	.word     _loop        /* TIM8 Update and TIM13        */
	.word     _loop        /* TIM8 Trigger and Commutation and TIM14 */
	.word     _loop        /* TIM8 Capture Compare         */
	.word     _loop        /* DMA1 Stream7                 */
	.word     _loop        /* FMC                         */
	.word     _loop        /* SDIO                         */
	.word     _loop        /* TIM5                         */
	.word     _loop        /* SPI3                         */
	.word     _loop        /* UART4                        */
	.word     _loop        /* UART5                        */
	.word     _loop        /* TIM6 and DAC1&2 underrun errors */
	.word     _loop        /* TIM7                         */
	.word     _loop        /* DMA2 Stream 0                */
	.word     _loop        /* DMA2 Stream 1                */
	.word     _loop        /* DMA2 Stream 2                */
	.word     _loop        /* DMA2 Stream 3                */
	.word     _loop        /* DMA2 Stream 4                */
	.word     _loop        /* Ethernet                     */
	.word     _loop        /* Ethernet Wakeup through EXTI line */
	.word     _loop        /* CAN2 TX                      */
	.word     _loop        /* CAN2 RX0                     */
	.word     _loop        /* CAN2 RX1                     */
	.word     _loop        /* CAN2 SCE                     */
	.word     _loop        /* USB OTG FS                   */
	.word     _loop        /* DMA2 Stream 5                */
	.word     _loop        /* DMA2 Stream 6                */
	.word     _loop        /* DMA2 Stream 7                */
	.word     _loop        /* USART6                       */
	.word     _loop        /* I2C3 event                   */
	.word     _loop        /* I2C3 error                   */
	.word     _loop        /* USB OTG HS End Point 1 Out   */
	.word     _loop        /* USB OTG HS End Point 1 In    */
	.word     _loop        /* USB OTG HS Wakeup through EXTI */
	.word     _loop        /* USB OTG HS                   */
	.word     _loop        /* DCMI                         */
	.word     _loop        /* Reserved                     */
	.word     _loop        /* Hash and Rng                 */
	.word     _loop        /* FPU                          */
	.word     _loop        /* UART7                        */
	.word     _loop        /* UART8                        */
	.word     _loop        /* SPI4                         */
	.word     _loop        /* SPI5                         */
	.word     _loop        /* SPI6                         */
	.word     _loop        /* SAI1                         */
	.word     _loop        /* LTDC_IRQHandler              */
	.word     _loop        /* LTDC_ER_IRQHandler           */
	.word     _loop        /* DMA2D                        */          
