#pragma once

#include "i2c.h"

/** MPU register definitions **/
#define MPU_REGISTER_ACCEL_X_OUT_H      0x3B
#define MPU_REGISTER_ACCEL_Y_OUT_H      0x3D
#define MPU_REGISTER_ACCEL_Z_OUT_H      0x3F
#define MPU_REGISTER_TEMP_OUT_H         0x41
#define MPU_REGISTER_GYRO_X_OUT_H       0x43
#define MPU_REGISTER_GYRO_Y_OUT_H       0x45
#define MPU_REGISTER_GYRO_Z_OUT_H       0x47
#define MPU_REGISTER_EXT_SENS_DATA_00   0x49

#define MPU_REGISTER_PWR_MGMT_1         0x6B
#define MPU_REGISTER_PWR_MGMT_2         0x6C

#define MPU_REGISTER_WHOAMI             0x75
#define MPU_WHOAMI_RESPONSE             104

/** MPU sensor-readout types **/ 
typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} accel_reading_t;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} gyro_reading_t;

typedef uint16_t temp_reading_t;

typedef struct {
    uint8_t data[24];
} ext_sens_reading_t;

typedef struct {
    accel_reading_t     accel;
    gyro_reading_t      gyro;
    temp_reading_t      temp;
    ext_sens_reading_t  ext;
} mpu_reading_t;

/** MPU configuration types **/

typedef struct {

} mpu_configs_t;

#define sizeof_array(array)		( sizeof(array) / sizeof(array[0]) )
#define init_uint16(array, index_high, index_low)    ( (uint16_t)(array[index_high]  << 8) | array[index_low] )

void mpu_init()
{
	uint8_t pwr_mgmt_1 = 0;
	i2c_read(MPU_REGISTER_PWR_MGMT_1, false, &pwr_mgmt_1, 1);
	printf("pwr management reading is: %i\n", pwr_mgmt_1);
	if(pwr_mgmt_1 == 64)
	{
		pwr_mgmt_1 = 0;
		i2c_write(MPU_REGISTER_PWR_MGMT_1, false, &pwr_mgmt_1, 1);
	}
}


bool mpu_read_wai_register()
{
    uint8_t reading = 0;
    i2c_read(MPU_REGISTER_WHOAMI, false, &reading, 1);
    return reading == MPU_WHOAMI_RESPONSE ? true : false;
}

accel_reading_t mpu_read_accelerometer()
{
    uint8_t data[sizeof(accel_reading_t)];
    i2c_read(MPU_REGISTER_ACCEL_X_OUT_H, false, data, sizeof_array(data));
    accel_reading_t reading = { init_uint16(data, 0, 1),init_uint16(data, 2, 3), init_uint16(data, 4, 5)};
    return reading;
}

gyro_reading_t mpu_read_gyroscope()
{
    uint8_t data[sizeof(gyro_reading_t)];
    i2c_read(MPU_REGISTER_GYRO_X_OUT_H, false, data, sizeof_array(data));
    gyro_reading_t reading = { init_uint16(data, 0, 1),init_uint16(data, 2, 3), init_uint16(data, 4, 5)};
    return reading;
}

temp_reading_t mpu_read_thermometer()
{
    uint8_t data[sizeof(temp_reading_t)];
    i2c_read(MPU_REGISTER_TEMP_OUT_H, false, data, sizeof_array(data));
    temp_reading_t reading = { init_uint16(data, 0, 1)};
    return reading;
}

ext_sens_reading_t mpu_read_ext_data()
{
    uint8_t data[sizeof(ext_sens_reading_t)];
    i2c_read(MPU_REGISTER_EXT_SENS_DATA_00, false, data, sizeof_array(data));
    ext_sens_reading_t reading;
    memcpy(reading.data, data, sizeof(ext_sens_reading_t));
    return reading;
}

mpu_reading_t mpu_read_sensors()
{
    mpu_reading_t reading = { mpu_read_accelerometer(), mpu_read_gyroscope(), mpu_read_thermometer(), mpu_read_ext_data() };
    return reading;
}
