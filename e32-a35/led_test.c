#include <stdint.h>

#define GPIO_BASE  0x00040100UL
#define GPIO_DIR   (*(volatile uint32_t *)(GPIO_BASE + 0x00))
#define GPIO_DATA  (*(volatile uint32_t *)(GPIO_BASE + 0x08))

#define LED_GREEN  (1U << 7)
#define LED_BLUE   (1U << 8)
#define LED_RED    (1U << 14)

#define LED_MASK (LED_GREEN | LED_BLUE | LED_RED)

static void delay(volatile uint32_t count)
{
    while (count--)
        __asm__ volatile ("nop");
}

int main(void)
{
    GPIO_DIR = LED_MASK;

    while (1) {
        GPIO_DATA = LED_GREEN;
        delay(1000000);

        GPIO_DATA = LED_BLUE;
        delay(1000000);

        GPIO_DATA = LED_RED;
        delay(1000000);

        GPIO_DATA = LED_MASK;
        delay(1000000);

        GPIO_DATA = 0;
        delay(1000000);
    }

    return 0;
}
