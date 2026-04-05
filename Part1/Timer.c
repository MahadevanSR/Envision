#include <stdint.h>

// ================= BASE ADDRESSES =================
#define GPIOA      0x40020000
#define RCC_BASE   0x40023800
#define TIM2_BASE  0x40000000

// ================= GPIO REGISTERS =================
#define GPIOA_MODER (GPIOA + 0x00)
#define GPIOA_ODR   (GPIOA + 0x14)

// ================= RCC REGISTERS =================
#define RCC_AHB1ENR (RCC_BASE + 0x30)
#define RCC_APB1ENR (RCC_BASE + 0x40)

// ================= TIM2 REGISTERS =================
#define TIM2_CR1 (TIM2_BASE + 0x00)
#define TIM2_SR  (TIM2_BASE + 0x10)
#define TIM2_PSC (TIM2_BASE + 0x28)
#define TIM2_ARR (TIM2_BASE + 0x2C)

int main(void)
{
    // ================= ENABLE CLOCKS =================

    // Enable GPIOA clock
    *((uint32_t*)(RCC_AHB1ENR)) |= (1 << 0);

    // Enable TIM2 clock
    *((uint32_t*)(RCC_APB1ENR)) |= (1 << 0);


    // ================= CONFIGURE GPIO =================

    // Set PA5 as output (clear bit 11, set bit 10)
    *((uint32_t*)(GPIOA_MODER)) &= ~(1 << 11);
    *((uint32_t*)(GPIOA_MODER)) |=  (1 << 10);


    // ================= CONFIGURE TIMER =================

    // Prescaler → 1 ms tick (assuming 16 MHz clock)
    *((uint32_t*)(TIM2_PSC)) = 15999;

    // Auto-reload → 2 sec delay (2000 ms)
    *((uint32_t*)(TIM2_ARR)) = 1999;

    // Start timer
    *((uint32_t*)(TIM2_CR1)) |= (1 << 0);


  	    while (1)
    {
        // Wait for update flag (UIF)
        while (!(*((uint32_t*)(TIM2_SR)) & (1 << 0)));

        // Clear update flag
        *((uint32_t*)(TIM2_SR)) &= ~(1 << 0);

        // Toggle LED (PA5)
        *((uint32_t*)(GPIOA_ODR)) ^= (1 << 5);
    }
}
