#include "../inc/i2c_opencm3.h"

#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include <string.h>

static void i2c_read(uint8_t i2c_addr, uint8_t initial_register, uint8_t* data, size_t registers_to_read)
{  
    i2c_transfer7(I2C1, i2c_addr, &initial_register , sizeof(initial_register) , data, registers_to_read );
}

static void i2c_write(uint8_t i2c_addr, uint8_t initial_register, uint8_t* data, size_t registers_to_write)
{
	uint8_t bytes_to_write[registers_to_write + sizeof(initial_register)];
	bytes_to_write[0] = initial_register;
	memcpy(bytes_to_write + sizeof(initial_register), data, registers_to_write);	

    i2c_transfer7(I2C1, i2c_addr, bytes_to_write , sizeof_array(bytes_to_write) , NULL, 0 );
}

i2c_link_t i2c_setup(void)
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
    
    i2c_link_t ret = { i2c_read, i2c_write};   
    return ret; 
}

