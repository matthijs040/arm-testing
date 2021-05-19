#include "../inc/mpu6050.h"
#include <string.h>
#include <stdio.h>

mpu_t mpu_init(i2c_link_t i2c, bool alt_addr)
{
	uint8_t pwr_mgmt_1 = 0;
	i2c.read( MPU_I2C_ADDR(alt_addr), MPU_REGISTER_PWR_MGMT_1, &pwr_mgmt_1, 1);
	printf("pwr management reading is: %i\n", pwr_mgmt_1);
	if(pwr_mgmt_1 == 64)
	{
		pwr_mgmt_1 = 0;
		i2c.write(MPU_I2C_ADDR(alt_addr), MPU_REGISTER_PWR_MGMT_1, &pwr_mgmt_1, 1);
	}

    mpu_t ret = { i2c, alt_addr};
    return ret;
}

bool mpu_read_wai_register(const mpu_t mpu)
{
    uint8_t reading = 0;
    mpu.i2c_conn.read(MPU_I2C_ADDR(mpu.alt_addr), MPU_REGISTER_WHOAMI, &reading, 1);
    return reading == MPU_WHOAMI_RESPONSE ? true : false;
}

accel_reading_t mpu_read_accelerometer(const mpu_t mpu)
{
    uint8_t data[sizeof(accel_reading_t)];
    mpu.i2c_conn.read(MPU_I2C_ADDR(mpu.alt_addr), MPU_REGISTER_ACCEL_X_OUT_H, data, sizeof_array(data));
    accel_reading_t reading = { init_uint16(data, 0, 1),init_uint16(data, 2, 3), init_uint16(data, 4, 5)};
    return reading;
}

gyro_reading_t mpu_read_gyroscope(const mpu_t mpu)
{
    uint8_t data[sizeof(gyro_reading_t)];
    mpu.i2c_conn.read(MPU_I2C_ADDR(mpu.alt_addr), MPU_REGISTER_GYRO_X_OUT_H, data, sizeof_array(data));
    gyro_reading_t reading = { init_uint16(data, 0, 1),init_uint16(data, 2, 3), init_uint16(data, 4, 5)};
    return reading;
}

temp_reading_t mpu_read_thermometer(const mpu_t mpu)
{
    uint8_t data[sizeof(temp_reading_t)];
    mpu.i2c_conn.read(MPU_I2C_ADDR(mpu.alt_addr), MPU_REGISTER_TEMP_OUT_H, data, sizeof_array(data));
    temp_reading_t reading = { init_uint16(data, 0, 1)};
    return reading;
}

ext_sens_reading_t mpu_read_ext_data(const mpu_t mpu)
{
    uint8_t data[sizeof(ext_sens_reading_t)];
    mpu.i2c_conn.read(MPU_I2C_ADDR(mpu.alt_addr), MPU_REGISTER_EXT_SENS_DATA_00, data, sizeof_array(data));
    ext_sens_reading_t reading;
    memcpy(reading.data, data, sizeof(ext_sens_reading_t));
    return reading;
}

mpu_reading_t mpu_read_sensors(const mpu_t mpu)
{
    mpu_reading_t reading = { mpu_read_accelerometer(   mpu)
                            , mpu_read_gyroscope(       mpu)
                            , mpu_read_thermometer(     mpu)
                            , mpu_read_ext_data(        mpu) };
    return reading;
}