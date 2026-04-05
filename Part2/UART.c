#include <stdint.h>

/* Base Addresses */
#define GPIOA 0x40020000
#define RCCbase 0x40023800
#define USART2base 0x40004400

/* RCC Registers */
#define RCCAHB1 (RCCbase + 0x30)
#define RCCAPB1 (RCCbase + 0x40)

/* GPIO Registers */
#define GPIOA_MODER (GPIOA + 0x00)
#define GPIOA_AFRL  (GPIOA + 0x20)

/* USART Registers */
#define USART_SR (USART2base + 0x00)
#define USART_DR (USART2base + 0x04)
#define USART_BRR (USART2base + 0x08)
#define USART_CR1 (USART2base + 0x0C)

/* Function to send one character */
void UART_SendChar(char c)
{
    while (!(*((uint32_t*)(USART_SR)) & (1 << 7))); // Wait TXE
    *((uint32_t*)(USART_DR)) = c;
}

/* Function to send string */
void UART_SendString(char *str)
{
    while (*str)
    {
        UART_SendChar(*str++);
    }
}

int main(void)
{
    /* 1. Enable clocks */
    *((uint32_t*)(RCCAHB1)) |= (1 << 0);   // Enable GPIOA
    *((uint32_t*)(RCCAPB1)) |= (1 << 17);  // Enable USART2

    /* 2. Set PA2 to Alternate Function mode */
    *((uint32_t*)(GPIOA_MODER)) &= ~(3 << (2 * 2)); // Clear
    *((uint32_t*)(GPIOA_MODER)) |= (2 << (2 * 2));  // AF mode

    /* 3. Select AF7 (USART2) for PA2 */
    *((uint32_t*)(GPIOA_AFRL)) &= ~(0xF << (2 * 4));
    *((uint32_t*)(GPIOA_AFRL)) |= (7 << (2 * 4));

    /* 4. Set baud rate (Assuming 16 MHz clock, 9600 baud) */
    *((uint32_t*)(USART_BRR)) = 0x0683;

    /* 5. Enable UART */
    *((uint32_t*)(USART_CR1)) |= (1 << 13); // UE
    *((uint32_t*)(USART_CR1)) |= (1 << 3);  // TE

    while (1)
    {
        UART_SendString("London is Blue\r\n");

        for (int i = 0; i < 1000000; i++); // crude delay
    }

    return 0;
}
