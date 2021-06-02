#pragma once

#include <stdint.h>	// uint8_t
#include <stdlib.h> // size_t

typedef enum {
	kb100s,
	kb400s,
	kb1000s,
	kb3200s
} i2c_speed_t;

typedef struct i2c_link_t{
	struct i2c_link_t (*init)(void);

	void (*read)(const uint8_t i2c_device_address
				,const uint8_t i2c_device_register_address
				,uint8_t* const data_to_read
				,const size_t number_of_consecutive_registers_to_read);
	
	void (*write)(const uint8_t i2c_device_address
				, const uint8_t i2c_device_register_address
				, const uint8_t* const data_to_write
				, const size_t number_of_consecutive_registers_to_write);
} i2c_link_t;

// Should be used in conjunction with a setup function.
// The struct can then be used as an interface abstraction.
// i2c_link_t i2c_setup(void);
