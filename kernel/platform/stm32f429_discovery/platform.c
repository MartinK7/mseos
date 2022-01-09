
#include "sys/tick.h"
#include "stm32f4xx.h"

volatile void irq_systick(void)
{
	tick_irq_callback_increment(1);
}

static uint32_t core_clock_get(void)
{
	// TODO Calcualtion
	return 16000000;
}

static void clock_init(void)
{
	// TODO
}

static void systick_init(void)
{
	NVIC_SetPriorityGrouping(0x03U);
	SysTick_Config(core_clock_get()/1000);
	SysTick->CTRL |= 0x04U;
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
}

static void rcc_init(void)
{
	RCC->AHB1ENR |= \
	RCC_AHB1ENR_GPIOAEN | \
	RCC_AHB1ENR_GPIOBEN | \
	RCC_AHB1ENR_GPIOCEN | \
	RCC_AHB1ENR_GPIODEN | \
	RCC_AHB1ENR_GPIOEEN | \
	RCC_AHB1ENR_GPIOFEN | \
	RCC_AHB1ENR_GPIOGEN;
}

static void gpio_init(void)
{
	//                  FMC            FMC
	GPIOB->AFR[0]  &= ~(0xFU<<( 5-0)*4|0xFU<<( 6-0)*4|0);
	GPIOB->AFR[0]  |=  (0xCU<<( 5-0)*4|0xCU<<( 6-0)*4|0);
	GPIOB->AFR[1]  &= ~(0             |0             |0);
	GPIOB->AFR[1]  |=  (0             |0             |0);
	GPIOB->MODER   &= ~(0x3U<<( 5*2)  |0x3U<<( 6*2)  |0);
	GPIOB->MODER   |=  (0x2U<<( 5*2)  |0x2U<<( 6*2)  |0);
	GPIOB->OSPEEDR &= ~(0x3U<<( 5*2)  |0x3U<<( 6*2)  |0);
	GPIOB->OSPEEDR |=  (0x2U<<( 5*2)  |0x2U<<( 6*2)  |0);
	GPIOB->OTYPER  &= ~(0x1U<<( 5*1)  |0x1U<<( 6*1)  |0);
	GPIOB->OTYPER  |=  (0x0U<<( 5*1)  |0x0U<<( 6*1)  |0);
	GPIOB->PUPDR   &= ~(0x3U<<( 5*2)  |0x3U<<( 6*2)  |0);
	GPIOB->PUPDR   |=  (0x0U<<( 5*2)  |0x0U<<( 6*2)  |0);

	//                  FMC
	GPIOC->AFR[0]  &= ~(0xFU<<( 0-0)*4|0);
	GPIOC->AFR[0]  |=  (0xCU<<( 0-0)*4|0);
	GPIOC->AFR[1]  &= ~(0             |0);
	GPIOC->AFR[1]  |=  (0             |0);
	GPIOC->MODER   &= ~(0x3U<<( 0*2)  |0);
	GPIOC->MODER   |=  (0x2U<<( 0*2)  |0);
	GPIOC->OSPEEDR &= ~(0x3U<<( 0*2)  |0);
	GPIOC->OSPEEDR |=  (0x2U<<( 0*2)  |0);
	GPIOC->OTYPER  &= ~(0x1U<<( 0*1)  |0);
	GPIOC->OTYPER  |=  (0x0U<<( 0*1)  |0);
	GPIOC->PUPDR   &= ~(0x3U<<( 0*2)  |0);
	GPIOC->PUPDR   |=  (0x0U<<( 0*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            FMC
	GPIOD->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0             |0             |0             |0             |0             |0);
	GPIOD->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0             |0             |0             |0             |0             |0);
	GPIOD->AFR[1]  &= ~(0             |0             |0xFU<<( 8-8)*4|0xFU<<( 9-8)*4|0xFU<<(10-8)*4|0xFU<<(14-8)*4|0xFU<<(15-8)*4|0);
	GPIOD->AFR[1]  |=  (0             |0             |0xCU<<( 8-8)*4|0xCU<<( 9-8)*4|0xCU<<(10-8)*4|0xCU<<(14-8)*4|0xCU<<(15-8)*4|0);
	GPIOD->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOD->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 8*2)  |0x2U<<( 9*2)  |0x2U<<(10*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOD->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOD->OSPEEDR |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 8*2)  |0x2U<<( 9*2)  |0x2U<<(10*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOD->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 8*1)  |0x1U<<( 9*1)  |0x1U<<(10*1)  |0x1U<<(14*1)  |0x1U<<(15*1)  |0);
	GPIOD->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 8*1)  |0x0U<<( 9*1)  |0x0U<<(10*1)  |0x0U<<(14*1)  |0x0U<<(15*1)  |0);
	GPIOD->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOD->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 8*2)  |0x0U<<( 9*2)  |0x0U<<(10*2)  |0x0U<<(14*2)  |0x0U<<(15*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC
	GPIOE->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0xFU<<( 7-0)*4|0             |0             |0             |0             |0             |0             |0             |0             |0);
	GPIOE->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0xCU<<( 7-0)*4|0             |0             |0             |0             |0             |0             |0             |0             |0);
	GPIOE->AFR[1]  &= ~(0             |0             |0             |0xFU<<( 8-8)*4|0xFU<<( 9-8)*4|0xFU<<(10-8)*4|0xFU<<(11-8)*4|0xFU<<(12-8)*4|0xFU<<(13-8)*4|0xFU<<(14-8)*4|0xFU<<(15-8)*4|0);
	GPIOE->AFR[1]  |=  (0             |0             |0             |0xCU<<( 8-8)*4|0xCU<<( 9-8)*4|0xCU<<(10-8)*4|0xCU<<(11-8)*4|0xCU<<(12-8)*4|0xCU<<(13-8)*4|0xCU<<(14-8)*4|0xCU<<(15-8)*4|0);
	GPIOE->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 7*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOE->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 7*2)  |0x2U<<( 8*2)  |0x2U<<( 9*2)  |0x2U<<(10*2)  |0x2U<<(11*2)  |0x2U<<(12*2)  |0x2U<<(13*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOE->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 7*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOE->OSPEEDR |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 7*2)  |0x2U<<( 8*2)  |0x2U<<( 9*2)  |0x2U<<(10*2)  |0x2U<<(11*2)  |0x2U<<(12*2)  |0x2U<<(13*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOE->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 7*1)  |0x1U<<( 8*1)  |0x1U<<( 9*1)  |0x1U<<(10*1)  |0x1U<<(11*1)  |0x1U<<(12*1)  |0x1U<<(13*1)  |0x1U<<(14*1)  |0x1U<<(15*1)  |0);
	GPIOE->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 7*1)  |0x0U<<( 8*1)  |0x0U<<( 9*1)  |0x0U<<(10*1)  |0x0U<<(11*1)  |0x0U<<(12*1)  |0x0U<<(13*1)  |0x0U<<(14*1)  |0x0U<<(15*1)  |0);
	GPIOE->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 7*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOE->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 7*2)  |0x0U<<( 8*2)  |0x0U<<( 9*2)  |0x0U<<(10*2)  |0x0U<<(11*2)  |0x0U<<(12*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0x0U<<(15*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC
	GPIOF->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0xFU<<( 2-0)*4|0xFU<<( 3-0)*4|0xFU<<( 4-0)*4|0xFU<<( 5-0)*4|0             |0             |0             |0             |0             |0);
	GPIOF->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0xCU<<( 2-0)*4|0xCU<<( 3-0)*4|0xCU<<( 4-0)*4|0xCU<<( 5-0)*4|0             |0             |0             |0             |0             |0);
	GPIOF->AFR[1]  &= ~(0             |0             |0             |0             |0             |0             |0xFU<<(11-8)*4|0xFU<<(12-8)*4|0xFU<<(13-8)*4|0xFU<<(14-8)*4|0xFU<<(15-8)*4|0);
	GPIOF->AFR[1]  |=  (0             |0             |0             |0             |0             |0             |0xCU<<(11-8)*4|0xCU<<(12-8)*4|0xCU<<(13-8)*4|0xCU<<(14-8)*4|0xCU<<(15-8)*4|0);
	GPIOF->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 2*2)  |0x3U<<( 3*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOF->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 2*2)  |0x2U<<( 3*2)  |0x2U<<( 4*2)  |0x2U<<( 5*2)  |0x2U<<(11*2)  |0x2U<<(12*2)  |0x2U<<(13*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOF->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 2*2)  |0x3U<<( 3*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOF->OSPEEDR |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 2*2)  |0x2U<<( 3*2)  |0x2U<<( 4*2)  |0x2U<<( 5*2)  |0x2U<<(11*2)  |0x2U<<(12*2)  |0x2U<<(13*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOF->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 2*1)  |0x1U<<( 3*1)  |0x1U<<( 4*1)  |0x1U<<( 5*1)  |0x1U<<(11*1)  |0x1U<<(12*1)  |0x1U<<(13*1)  |0x1U<<(14*1)  |0x1U<<(15*1)  |0);
	GPIOF->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 2*1)  |0x0U<<( 3*1)  |0x0U<<( 4*1)  |0x0U<<( 5*1)  |0x0U<<(11*1)  |0x0U<<(12*1)  |0x0U<<(13*1)  |0x0U<<(14*1)  |0x0U<<(15*1)  |0);
	GPIOF->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 2*2)  |0x3U<<( 3*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOF->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 2*2)  |0x0U<<( 3*2)  |0x0U<<( 4*2)  |0x0U<<( 5*2)  |0x0U<<(11*2)  |0x0U<<(12*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0x0U<<(15*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            LED_GREEN      LED_RED
	GPIOG->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0xFU<<( 4-0)*4|0xFU<<( 5-0)*4|0             |0             |0             |0             |0);
	GPIOG->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0xCU<<( 4-0)*4|0xCU<<( 5-0)*4|0             |0             |0             |0             |0);
	GPIOG->AFR[1]  &= ~(0             |0             |0             |0             |0xFU<<( 8-8)*4|0xFU<<(15-8)*4|0xFU<<(13-8)*4|0xFU<<(14-8)*4|0);
	GPIOG->AFR[1]  |=  (0             |0             |0             |0             |0xCU<<( 8-8)*4|0xCU<<(15-8)*4|0x0U<<(13-8)*4|0x0U<<(14-8)*4|0);
	GPIOG->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<( 8*2)  |0x3U<<(15*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0);
	GPIOG->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 4*2)  |0x2U<<( 5*2)  |0x2U<<( 8*2)  |0x2U<<(15*2)  |0x1U<<(13*2)  |0x1U<<(14*2)  |0);
	GPIOG->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<( 8*2)  |0x3U<<(15*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0);
	GPIOG->OSPEEDR |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 4*2)  |0x2U<<( 5*2)  |0x2U<<( 8*2)  |0x2U<<(15*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0);
	GPIOG->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 4*1)  |0x1U<<( 5*1)  |0x1U<<( 8*1)  |0x1U<<(15*1)  |0x1U<<(13*1)  |0x1U<<(14*1)  |0);
	GPIOG->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 4*1)  |0x0U<<( 5*1)  |0x0U<<( 8*1)  |0x0U<<(15*1)  |0x0U<<(13*1)  |0x0U<<(14*1)  |0);
	GPIOG->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<( 8*2)  |0x3U<<(15*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0);
	GPIOG->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 4*2)  |0x0U<<( 5*2)  |0x0U<<( 8*2)  |0x0U<<(15*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0);

	//                  BUT_USER
	GPIOA->AFR[0]  &= ~(0xFU<<( 0-0)*4|0);
	GPIOA->AFR[0]  |=  (0x0U<<( 0-0)*4|0);
	GPIOA->AFR[1]  &= ~(0             |0);
	GPIOA->AFR[1]  |=  (0             |0);
	GPIOA->MODER   &= ~(0x3U<<( 0*2)  |0);
	GPIOA->MODER   |=  (0x0U<<( 0*2)  |0);
	GPIOA->OSPEEDR &= ~(0x3U<<( 0*2)  |0);
	GPIOA->OSPEEDR |=  (0x0U<<( 0*2)  |0);
	GPIOA->OTYPER  &= ~(0x1U<<( 0*1)  |0);
	GPIOA->OTYPER  |=  (0x0U<<( 0*1)  |0);
	GPIOA->PUPDR   &= ~(0x3U<<( 0*2)  |0);
	GPIOA->PUPDR   |=  (0x2U<<( 0*2)  |0);
}

void platform_init(void)
{
	// Enable FPU (set CP10 and CP11 Full Access)
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	clock_init();
	systick_init();
	rcc_init();
	gpio_init();
}

// "FAKESPACE file" This is converted executable from apps/stm32blink/
static volatile const uint32_t __attribute__((aligned(4))) bin2c__stm32blink_elf_bin[] = {
		0x4558454d, 0x00000000, 0x00000011, 0x00000400, 0xb087b480, 0x6078af00, 0x687b6039, 0xd1022b00,
		0x33fff04f, 0x2300e036, 0xe02e617b, 0x681b683b, 0x2b30781b, 0xf44fd102, 0xe0015300, 0x4380f44f,
		0x61934a17, 0x613b2300, 0x693be002, 0x613b3301, 0x4a14693b, 0xd9f84293, 0x681b683b, 0x2b30781b,
		0xf04fd102, 0xe0015300, 0x4380f04f, 0x61934a0c, 0x60fb2300, 0x68fbe002, 0x60fb3301, 0x4a0968fb,
		0xd9f84293, 0x3301697b, 0x697b617b, 0x6f80f5b3, 0x2337d3cc, 0x371c4618, 0xbc8046bd, 0xbf004770,
		0x40021800, 0x0001869f, 0xffffffff
};

void platform_register(void)
{
	for(uint32_t i = 0; i < 10; ++i)
	{
		GPIOG->BSRR = GPIO_BSRR_BS13 | GPIO_BSRR_BR14;
		tick_delay(100);
		GPIOG->BSRR = GPIO_BSRR_BR13 | GPIO_BSRR_BS14;
		tick_delay(100);
	}
	GPIOG->BSRR = GPIO_BSRR_BR13 | GPIO_BSRR_BR14;

	// Load application to RAM from "FAKESPACE filesystem"
	uint32_t __attribute__((aligned(4))) ram[sizeof(bin2c__stm32blink_elf_bin) / sizeof(*bin2c__stm32blink_elf_bin)];
	for(uint32_t i = 0; i < sizeof(bin2c__stm32blink_elf_bin) / sizeof(*bin2c__stm32blink_elf_bin); ++i)
		ram[i] = bin2c__stm32blink_elf_bin[i];

	// Check MEXE
	for(uint32_t i = 0; i < 4; ++i)
		if(((uint8_t*)bin2c__stm32blink_elf_bin)[i] != "MEXE"[i])
			return;

	// Calculate pointer
	int (*mexe_main)(int argc, char *argv[]) = (void*)((uint8_t*)ram + ram[2]);

	// Execute
	// In GDB:
	// add-symbol-file cmake-build-debug/apps/stm32blink/stm32blink.elf &ram[0]
	char *arg[1] = {"0"};
	int retval = mexe_main(1, arg);
	(void)retval;
}
