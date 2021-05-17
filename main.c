// For intellisense.
#ifndef STM32F3
#define STM32F3
#endif

#include "inc/usart.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>


/**
static void i2c_setup(void)
{
	rcc_periph_clock_enable(RCC_I2C1);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_set_i2c_clock_hsi(I2C1);

	i2c_reset(I2C1);
	// Setup GPIO pin GPIO_USART2_TX/GPIO9 on GPIO port A for transmit. 
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);
	gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);
	i2c_peripheral_disable(I2C1);
	//configure ANFOFF DNF[3:0] in CR1
	i2c_enable_analog_filter(I2C1);
	i2c_set_digital_filter(I2C1, 0);
	// HSI is at 8Mhz 
	i2c_set_speed(I2C1, i2c_speed_sm_100k, 8);
	//configure No-Stretch CR1 (only relevant in slave mode)
	i2c_enable_stretching(I2C1);
	//addressing mode
	i2c_set_7bit_addr_mode(I2C1);
	i2c_peripheral_enable(I2C1);
}
**/


/**
static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOE);
	gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
		GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 |
		GPIO14 | GPIO15);
}
**/

/**
static void clock_setup(void)
{
	rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
}
**/
#define I2C_ACC_ADDR 0x19
#define I2C_MAG_ADDR 0x1E
#define ACC_STATUS 0x27
#define ACC_CTRL_REG1_A 0x20
#define ACC_CTRL_REG1_A_ODR_SHIFT 4
#define ACC_CTRL_REG1_A_ODR_MASK 0xF
#define ACC_CTRL_REG1_A_XEN (1 << 0)
#define ACC_CTRL_REG4_A 0x23

#define ACC_OUT_X_L_A 0x28
#define ACC_OUT_X_H_A 0x29

int main(void)
{
	// clock_setup();
	// gpio_setup();
	usart_setup();
	puts("Hello, we're running");
	// i2c_setup();
	// uint8_t cmd = ACC_CTRL_REG1_A;
	// uint8_t data;
	// i2c_transfer7(I2C1, I2C_ACC_ADDR, &cmd, 1, &data, 1);
	// cmd = ACC_CTRL_REG4_A;
	// i2c_transfer7(I2C1, I2C_ACC_ADDR, &cmd, 1, &data, 1);
	// int16_t acc_x;
// 
	// while (1) {
// 
	// 	cmd = ACC_STATUS;
	// 	i2c_transfer7(I2C1, I2C_ACC_ADDR, &cmd, 1, &data, 1);
	// 	cmd = ACC_OUT_X_L_A;
	// 	i2c_transfer7(I2C1, I2C_ACC_ADDR, &cmd, 1, &data, 1);
	// 	acc_x = data;
	// 	cmd = ACC_OUT_X_H_A;
	// 	i2c_transfer7(I2C1, I2C_ACC_ADDR, &cmd, 1, &data, 1);
	// 	acc_x |= ((uint16_t)data << 8);
	// 	printf("data was %d\n", acc_x);
	// }

	return EXIT_SUCCESS;
}

