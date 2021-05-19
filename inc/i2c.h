#pragma once

// For intellisense.
#ifndef STM32F3
#define STM32F3
#endif

#define NOP __asm__("nop");
#define sizeof_array(array)		( sizeof(array) / sizeof(array[0]) )


#include <stdio.h>
#include <string.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>



typedef struct i2c_link {
	void (*read)(uint8_t i2c_device_address
				,uint8_t i2c_device_register_address
				,uint8_t* data_to_read
				,size_t number_of_consecutive_registers_to_read);
	
	void (*write)(uint8_t i2c_device_address
				, uint8_t i2c_device_register_address
				, uint8_t* data_to_write
				, size_t number_of_consecutive_registers_to_write);
} i2c_link_t;

// Should be used in conjunction with a setup function.
// The struct can then be used as an interface abstraction.
// i2c_link_t i2c_setup(void);
