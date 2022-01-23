
#include "sys/tick.h"
#include "sys/kheap.h"
#include "sys/scheduler.h"
#include "sys/memops.h"
#include "stm32f4xx.h"

__attribute__((naked))
void irq_systick(void)
{
	__asm volatile (
		// [ASSEMBLY CODE]                         [C equivalent pseudo code]
		//
		"push  {r3, lr}                     \n" // tick_increment_irq_cb(1);
		"movs  r0, #1                       \n" // ..
		"bl    tick_increment_irq_cb        \n" // ..
		"pop   {r3, lr}                     \n" // ..
		"b     scheduler_switch_task_irq_cb \n" // goto scheduler_switch_task_irq_cb;
	);
}

static uint32_t core_clock_get(void)
{
	// TODO Calculation
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

	// Test what happen if systick interrupt occurs before scheduler is ready? - Fix
	for(volatile int i=0;i<1000000;++i) __asm volatile("nop");
}

// "FAKESPACE file" This is converted executable from apps/stm32blink/
const uint32_t __attribute__((aligned(4))) bin2c__stm32blink_elf_bin[] = {
		0x4558454d, 0x00000000, 0x00000011, 0x00000400, 0xb086b580, 0x6078af00, 0x613b687b, 0x617b2300,
		0x693be03f, 0xd1092b00, 0x2b05697b, 0x4b22d106, 0xf44f681b, 0x21017200, 0x47984820, 0x2b00693b,
		0x4b1fd103, 0x4798681b, 0x4b1ee002, 0x4798681b, 0x60fb2300, 0x68fbe002, 0x60fb3301, 0x3301693b,
		0xfb024a19, 0x68fbf203, 0xd8f4429a, 0x2b00693b, 0x4b16d103, 0x4798681b, 0x4b15e002, 0x4798681b,
		0x60bb2300, 0x68bbe002, 0x60bb3301, 0x3301693b, 0xfb024a0d, 0x68bbf203, 0xd8f4429a, 0x3301697b,
		0x693b617b, 0x015b3301, 0x429a697a, 0xbf00d3b9, 0x3718bf00, 0xbd8046bd, 0x080001c4, 0x00000011,
		0x080001ac, 0x080001b0, 0x000186a0, 0x080001b4, 0x080001b8, 0xffffffff
};

// Dummy
void syscall_open(void){GPIOG->BSRR = GPIO_BSRR_BS13;}
void syscall_close(void){GPIOG->BSRR = GPIO_BSRR_BS14;}
void syscall_read(void){GPIOG->BSRR = GPIO_BSRR_BR13;}
void syscall_write(void){GPIOG->BSRR = GPIO_BSRR_BR14;}
void syscall_flush(void){}
void syscall_ioctl(void){}

void platform_register(void)
{
	// Load application to RAM from "FAKESPACE filesystem"
//	uint32_t *app1 = kheap_alloc(sizeof(bin2c__stm32blink_elf_bin));
	uint32_t *app2 = kheap_alloc(sizeof(bin2c__stm32blink_elf_bin));

	for(uint32_t i = 0; i < sizeof(bin2c__stm32blink_elf_bin) / sizeof(*bin2c__stm32blink_elf_bin); ++i) {
//		app1[i] = bin2c__stm32blink_elf_bin[i];
		app2[i] = bin2c__stm32blink_elf_bin[i];
	}

	// Check MEXE
	for(uint32_t i = 0; i < 4; ++i)
		if(/*((uint8_t*)app1)[i] != "MEXE"[i] ||*/ ((uint8_t*)app2)[i] != "MEXE"[i])
			return;

	// Calculate pointer
//	void (*mexe1_start)(void *data) = (void*)(((uint8_t*)app1 + app1[2]));
	void (*mexe2_start)(void *data) = (void*)(((uint8_t*)app2 + app2[2]));

//	scheduler_create_task(app1, mexe1_start, (void*)3, 512);
	scheduler_create_task(app2, mexe2_start, (void*)0, 512);
}
