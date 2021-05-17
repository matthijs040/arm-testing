// For intellisense.
#ifndef STM32F3
#define STM32F3
#endif

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include <libopencm3/stm32/usart.h>

#include <stdbool.h>
#include <stdio.h>

static void usart_setup(void)
{
    usart_disable       (USART2);
	
	rcc_periph_clock_enable(RCC_USART2);
	rcc_periph_clock_enable(RCC_GPIOA);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
	// Mapping for these values is given in page 53 of the datasheet.
	gpio_set_af(	GPIOA, GPIO_AF7, GPIO2| GPIO3);
    
	usart_set_baudrate      (USART2, 115200);
    usart_set_databits      (USART2, 8);
    usart_set_parity        (USART2, USART_PARITY_NONE);
    usart_set_stopbits      (USART2, USART_STOPBITS_1);
    usart_set_mode          (USART2, USART_MODE_TX_RX);
    usart_set_flow_control  (USART2, USART_FLOWCONTROL_NONE);


    usart_enable(USART2);
}

/*
 * console_putc(char c)
 *
 * Send the character 'c' to the USART, wait for the USART
 * transmit buffer to be empty first.
 */
void console_putc(char c)
{
	usart_wait_send_ready(USART2);
	usart_send_blocking(USART2, c + '0' );
}



/*
 * void console_puts(char *s)
 *
 * Send a string to the console, one character at a time, return
 * after the last character, as indicated by a NUL character, is
 * reached.
 */
void console_puts(char *s)
{
	while (*s != '\000') {
		console_putc(*s);
		/* Add in a carraige return, after sending line feed */
		if (*s == '\n') {
			console_putc('\r');
		}
		s++;
	}
}



static void gpio_setup(void)
{
	/* Enable GPIOA clock. */
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Set GPIO5 (in GPIO port A) to 'output push-pull'. */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);



}

int main(void)
{
	int i;

    // rcc_clock_setup_pll(&rcc_hse8mhz_configs[RCC_CLOCK_HSE8_72MHZ]);
	
	rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);


	gpio_setup();
    usart_setup();

	/* Blink the LED (PC8) on the board. */
	while (true) 
    {
		/* Using API function gpio_toggle(): */
		gpio_toggle(GPIOA, GPIO5);	/* LED on/off */
        console_puts("Hello world.");
		for (i = 0; i < 2000000; i++) /* Wait a bit. */
			__asm__("nop");
	}

	return 0;
}
