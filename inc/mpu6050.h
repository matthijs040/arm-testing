#pragma once

#include "i2c_opencm3.h"
#include <stdbool.h>

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

#define MPU_I2C_ADDR_LOW 104 // 0b1101000   if AD0 pin on the mpu is low
#define MPU_I2C_ADDR_SET 105 // 0b1101001   if AD0 pin on the mpu is set
#define MPU_I2C_ADDR(alt) (alt ? MPU_I2C_ADDR_SET : MPU_I2C_ADDR_LOW)

#define MPU_ACCEL_SCALE_2G      16384
#define MPU_ACCEL_SCALE_4G      8192
#define MPU_ACCEL_SCALE_8G      4096
#define MPU_ACCEL_SCALE_16G     2048

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

typedef enum {
    g2,
    g4,
    g8,
    g16 
} accel_sensitivity_t;

typedef enum {
    degPs250,
    degPs500,
    degPs1000,
    degPs2000,
} gyro_sensitivity_t;

typedef struct {
} mpu_comm_config_t;

typedef struct {
    accel_sensitivity_t acc_sens;
    gyro_sensitivity_t  gyr_sens;
} mpu_sensor_config_t;

#define sizeof_array(array)		( sizeof(array) / sizeof(array[0]) )
#define init_uint16(array, index_high, index_low)    ( (uint16_t)(array[index_high]  << 8) | array[index_low] )

void mpu_init(i2c_link_t i2c, bool alt_addr);

bool mpu_read_wai_register(i2c_link_t i2c, bool alt_addr);

accel_reading_t mpu_read_accelerometer(i2c_link_t i2c, bool alt_addr);

gyro_reading_t mpu_read_gyroscope(i2c_link_t i2c, bool alt_addr);

temp_reading_t mpu_read_thermometer(i2c_link_t i2c, bool alt_addr);

ext_sens_reading_t mpu_read_ext_data(i2c_link_t i2c, bool alt_addr);

mpu_reading_t mpu_read_sensors(i2c_link_t i2c, bool alt_addr);