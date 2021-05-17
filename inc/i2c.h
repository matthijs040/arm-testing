#pragma once

// For intellisense.
#ifndef STM32F3
#define STM32F3
#endif
#define NOP __asm__("nop");

#include <stdio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>

static void i2c_setup(void)
{
	rcc_periph_clock_enable(RCC_I2C1);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_set_i2c_clock_hsi(I2C1);

    i2c_reset(I2C1);
	// Setup GPIO pin 6 and 7 on GPIO port B for alternate function. 
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8 | GPIO9);
    // Set alternate function to i2c.
    // In page 55 of datasheet. I2C1-SCL and SDA.
	gpio_set_af(GPIOB, GPIO_AF4, GPIO8 | GPIO9);
	i2c_peripheral_disable(I2C1);
	//configure ANFOFF DNF[3:0] in CR1
	i2c_enable_analog_filter(I2C1);
	i2c_set_digital_filter(I2C1, 0);
	// HSI is at 8Mhz 
	i2c_set_speed(I2C1, i2c_speed_fm_400k, 64);
	//configure No-Stretch CR1 (only relevant in slave mode)
	i2c_enable_stretching(I2C1);
	//addressing mode
	i2c_set_7bit_addr_mode(I2C1);

	i2c_peripheral_enable(I2C1);
    
}

#define MPU_I2C_ADDR_LOW 104 // 0b1101000   if AD0 pin on the mpu is low
#define MPU_I2C_ADDR_SET 105 // 0b1101001   if AD0 pin on the mpu is set
#define MPU_WAI_REG 0x75

static bool i2c_read(uint8_t initial_register, bool is_alt_addr_pin_set, uint8_t* data, size_t number_of_consecutive_registers)
{
    // i2c_send_start(I2C1);
  
    if(is_alt_addr_pin_set)
        i2c_transfer7(I2C1, MPU_I2C_ADDR_SET, &initial_register , sizeof(initial_register) , data, number_of_consecutive_registers );
    else
        i2c_transfer7(I2C1, MPU_I2C_ADDR_LOW, &initial_register , sizeof(initial_register) , data, number_of_consecutive_registers );
    return true;
    
}