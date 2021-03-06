// For intellisense.
#ifndef STM32F3
#define STM32F3
#endif

#include "inc/usart.h"
#include "inc/i2c_opencm3.h"
#include "inc/mpu6050.h"
#include "inc/lsm303DLHC.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "inc/acc_att_est.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>

static void clock_setup(void)
{
	rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_48MHZ]);
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

	// lsm303_t lsm_sensor = lsm_init(i2c, configurations[enabled]);
	// lsm_acc_reading_t lsm_reading = lsm_read_acc(lsm_sensor);
	// printf("lsm data: x %d, y %d, z %d", lsm_reading.x, lsm_reading.y, lsm_reading.z );



	const bool mpu_alt_addr = false;
	mpu_t sensor = mpu_init(i2c, mpu_alt_addr);

	if( mpu_read_wai_register(sensor) )
	{
		puts("Initial read request returned correctly. Starting readouts.");

		while (true)
		{
			mpu_reading_t reading = mpu_read_sensors(sensor); 

			float 	x_acc = reading.accel.x / MPU_ACCEL_SCALE_2G, 
					y_acc = reading.accel.y / MPU_ACCEL_SCALE_2G, 
					z_acc = reading.accel.z / MPU_ACCEL_SCALE_2G;

			// float	x_gyr = reading.gyro.x / MPU_GYRO_SCALE_0, 
			// 		y_gyr = reading.gyro.y / MPU_GYRO_SCALE_0, 
			// 		z_gyr = reading.gyro.z / MPU_GYRO_SCALE_0;

			// float sum_acc = fabs(x_acc) +  fabs(y_acc) +  fabs(z_acc); 
			attitude_t att = estimate_attitude(x_acc, y_acc, z_acc);

			// printf("AccX:%f, AccY:%f, AccZ:%f\n", x_acc, y_acc, z_acc );
			printf("AttX:%f, AttY:%f, AttZ:%f\n", att.r, att.p, att.y );
			// printf("As:%f",sum_acc);
			// printf("Gx:%f, Gy:%f, Gz:%f\n", x_gyr, y_gyr, z_gyr );
			// printf("T:%3d\n", reading.temp);
			
			// printf("other readings are: ");
			// // Data array might have decayed into a regular pointer. resulting in size 1.
			// for(uint8_t r = 0; r < sizeof_array(reading.ext.data); r++)
			// {
			// 	printf("%d ", reading.ext.data[r]);
			// }
			// putc('\n', stdout);

			for (int i = 0; i < 100000; i++) /* Wait a bit. */
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

