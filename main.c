// For intellisense.
#ifndef STM32F3
#define STM32F3
#endif

#include "inc/usart.h"
#include "inc/i2c.h"

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

static void clock_setup(void)
{
	rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSE8_72MHZ]);
}

int _write(int file, char *ptr, int len)
{
    int i;
    if (file == 1) 
    {
        for (i = 0; i < len; i++) 
        {
		    if (ptr[i] == '\n') 
		    	usart_send_blocking(USART2, '\r');
		    
            usart_send_blocking(USART2, ptr[i]);
	    }
        return i;
    }
    errno = EIO;
    return -1;
}

#define WHOAMI_REGISTER		0x75
#define MPU6050_IDENTITY 	104
#define MPU6050_INITIAL_READOUT_REGISTER	0x3B
#define sizeof_array(array) ( sizeof(array) / sizeof(array[0]) )

typedef enum
{
	accel_x_out_h = 0,
	accel_x_out_l = 1,
	accel_y_out_h, 		
	accel_y_out_l, 		
	accel_z_out_h, 		
	accel_z_out_l, 		
	temp_y_out_h, 		
	temp_y_out_l, 		
	gyro_x_out_h, 		
	gyro_x_out_l, 		
	gyro_y_out_h, 		
	gyro_y_out_l, 		
	gyro_z_out_h, 		
	gyro_z_out_l, 		
	ext1, 				
	ext2, 				
	ext3, 				
	ext4,
	MPU_READING_SIZE=18
}mpu_reading_t;


int main(void)
{
	clock_setup();
	usart_setup();
	puts("Hello, we're running");
	i2c_setup();
	uint8_t who_am_i = 0;
	if( i2c_read(WHOAMI_REGISTER, false, &who_am_i, 1 ) 
		&& who_am_i == MPU6050_IDENTITY )
	{
		puts("Initial read request returned correctly. Starting readouts.");

		uint8_t readouts[MPU_READING_SIZE];

		while (true)
		{
			i2c_read(MPU6050_INITIAL_READOUT_REGISTER, false, readouts, 1);
			printf("accelerometer readings are: x:%i, y:%i, z:%i\n", 
					(uint16_t)readouts[accel_x_out_h], 
					(uint16_t)readouts[accel_y_out_h], 
					(uint16_t)readouts[accel_z_out_h] );

			for (int i = 0; i < 4000000; i++) /* Wait a bit. */
			__asm__("nop");
		}
	}
	else
	{
		puts("read request to MPU failed");
		printf("registers I2C1_ISR: '%li' I2C_CR1: '%li',  I2C_CR2 '%li'\n", I2C1_ISR, I2C1_CR1, I2C1_CR2 );
	}



	return EXIT_SUCCESS;
}

