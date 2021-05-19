// For intellisense.
#ifndef STM32F3
#define STM32F3
#endif

#include "inc/usart.h"
#include "inc/i2c_opencm3.h"
#include "inc/mpu6050.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>

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

#define sizeof_array(array)		( sizeof(array) / sizeof(array[0]) )
#define is_bit_set(reg, bit)	( reg & ( 1 << bit ))

int main(void)
{
	clock_setup();
	usart_setup();
	puts("Hello, we're running");
	i2c_link_t i2c = i2c_setup();
	const bool mpu_alt_addr = false;
	mpu_init(i2c, mpu_alt_addr);

	if( mpu_read_wai_register(i2c, mpu_alt_addr) )
	{
		puts("Initial read request returned correctly. Starting readouts.");

		while (true)
		{
			mpu_reading_t reading = mpu_read_sensors(i2c, mpu_alt_addr); 

			printf("Ax:%f, Ay:%f, Az:%f\n", reading.accel.x / MPU_ACCEL_SCALE_2G, reading.accel.y / MPU_ACCEL_SCALE_2G, reading.accel.z / MPU_ACCEL_SCALE_2G );
			printf("Gx:%5d, Gy:%5d, Gz:%5d\n", reading.gyro.x, reading.gyro.y, reading.gyro.z);
			printf("T:%3d\n", reading.temp);
			
			// printf("other readings are: ");
			// // Data array might have decayed into a regular pointer. resulting in size 1.
			// for(uint8_t r = 0; r < sizeof_array(reading.ext.data); r++)
			// {
			// 	printf("%d ", reading.ext.data[r]);
			// }
			// putc('\n', stdout);

			for (int i = 0; i < 1000000; i++) /* Wait a bit. */
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

