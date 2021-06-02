#pragma once

// Acceleromter registers:
#define CTRL_REG1_A      0x20     
#define CTRL_REG2_A      0x21     
#define CTRL_REG3_A      0x22     
#define CTRL_REG4_A      0x23     
#define CTRL_REG5_A      0x24     
#define CTRL_REG6_A      0x25     
#define REFERENCE_A      0x26     
#define STATUS_REG_A     0x27     
#define OUT_X_L_A        0x28     
#define OUT_X_H_A        0x29     
#define OUT_Y_L_A        0x2A     
#define OUT_Y_H_A        0x2B     
#define OUT_Z_L_A        0x2C     
#define OUT_Z_H_A        0x2D     
#define FIFO_CTRL_REG_A  0x2E     
#define FIFO_SRC_REG_A   0x2F     
#define INT1_CFG_A       0x30  
#define INT1_SRC_A       0x31     
#define INT1_THS_A       0x32     
#define INT1_DURATION_A  0x33     
#define INT2_CFG_A       0x34     
#define INT2_SRC_A       0x35     
#define INT2_THS_A       0x36     
#define INT2_DURATION_A  0x37     
#define CLICK_CFG_A      0x38     
#define CLICK_SRC_A      0x39     
#define CLICK_THS_A      0x3A     

// Magnetometer registers:
#define TIME_LIMIT_A     0x3B
#define TIME_LATENCY_A   0x3C
#define TIME_WINDOW_A    0x3D
#define CRA_REG_M        0x00
#define OUT_X_L_M        0x04 
#define OUT_Z_H_M        0x05 
#define OUT_Z_L_M        0x06 
#define OUT_Y_H_M        0x07 
#define OUT_Y_L_M        0x08 
#define SR_REG_M         0x09 
#define IRA_REG_M        0x0A 
#define IRB_REG_M        0x0B 
#define IRC_REG_M        0x0C 
#define TEMP_OUT_H_M     0x31
#define TEMP_OUT_L_M     0x32

// Accelerometer SADs:
#define LSM_ACC_SAD_R    0x33
#define LSM_ACC_SAD_W    0x32

// Magnetometer SADs:
#define LSM_MAG_SAD_R    0x3D
#define LSM_MAG_SAD_W    0x3C

#include "i2c.h"
#include <stdbool.h>

// Typedefs for configuring the sensor:

// Control register 1 A:
#define CR1A__ODR_OFFSET 4
typedef enum lsm_data_rate_t {
    CR1A__ODR_Hz0             =   ( 0b0000 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz1             =   ( 0b0001 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz10            =   ( 0b0010 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz25            =   ( 0b0011 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz50            =   ( 0b0100 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz100           =   ( 0b0101 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz200           =   ( 0b0110 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz400           =   ( 0b0111 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz1620          =   ( 0b1000 << CR1A__ODR_OFFSET ),
    CR1A__ODR_Hz1344_Hz5376   =   ( 0b1001 << CR1A__ODR_OFFSET ) // Low power has to be enabled for the 5376Hz speed.
} lsm_data_rate_t;

#define CR1A__Xen   0x01
#define CR1A__Yen   0x02
#define CR1A__Zen   0x04
#define CR1A__LPen  0x08
#define CR1A__NONE  0x00

// Control register 2 A: 
#define CR2A__HPM_OFFSET 4
typedef enum CR2A__HPM
{
    CR2A__HPM_reset_reading           = ( 0b00 << CR2A__HPM_OFFSET ),
    CR2A__HPM_with_reference_signal   = ( 0b01 << CR2A__HPM_OFFSET ),
    CR2A__HPM_normal_mode             = ( 0b10 << CR2A__HPM_OFFSET ),
    CR2A__HPM_autoreset_on_interrupt  = ( 0b11 << CR2A__HPM_OFFSET ),
} CR2A__HPM;

#define CR2A__FDS   0x8
#define CR2A__NONE  0x0


#define CR3A__I1_CLICK    0x80
#define CR3A__I1_AOI1     0x40
#define CR3A__I1_AOI2     0x20
#define CR3A__I1_DRDY1    0x10
#define CR3A__I1_DRDY2    0x08
#define CR3A__I1_WTM      0x04
#define CR3A__I1_OVERRUN  0x02
#define CR3A__NONE        0x0

#define CR4A__BDU    0x80
#define CR4A__BLE    0x40

#define CR4A__FS_OFFSET 4
typedef enum CR4A_FS {
    CR4A__FS_g2  = ( 0b00 << CR4A__FS_OFFSET ) ,
    CR4A__FS_g4  = ( 0b01 << CR4A__FS_OFFSET ) ,
    CR4A__FS_g8  = ( 0b10 << CR4A__FS_OFFSET ) ,
    CR4A__FS_g16 = ( 0b11 << CR4A__FS_OFFSET )
} CR4A_FS;

#define CR4A__HR     0x08
#define CR4A__SIM    0x01
#define CR4A__NONE   0x0

#define CR5A__BOOT       0x80
#define CR5A__FIFO_EN    0x40
#define CR5A__LIR_INT1   0x08
#define CR5A__D4D_INT1   0x04
#define CR5A__LIR_INT2   0x02
#define CR5A__D4D_INT2   0x01
#define CR5A__NONE       0x0

#define CR6A__I2_CLICKen 0x80
#define CR6A__I2_INT1    0x40
#define CR6A__I2_INT2    0x20
#define CR6A__BOOT_I1    0x10
#define CR6A__P2_ACT     0x08
#define CR6A__H_LACTIVE  0x02
#define CR6A__NONE       0x0


typedef struct lsm_config_t {
    const uint8_t CR1A;
    const uint8_t CR2A;
    const uint8_t CR3A;
    const uint8_t CR4A;
    const uint8_t CR5A;
    const uint8_t CR6A;
} lsm_config_t;

typedef enum lsm_configurations {
    initial,
    enabled,
    LSM_CONFIGURATIONS
}lsm_configurations;

static const lsm_config_t configurations[LSM_CONFIGURATIONS] = 
{ // Default configuration. Sensor disabled.
    {  
        .CR1A = CR1A__ODR_Hz0 | CR1A__LPen | CR1A__Zen | CR1A__Yen | CR1A__Xen,
        .CR2A = CR2A__HPM_reset_reading,
        .CR3A = CR3A__NONE,
        .CR4A = CR4A__FS_g2,
        .CR5A = CR5A__NONE,
        .CR6A = CR6A__NONE
    },  // Enabled Configuration. Sensor enabled at 100Hz
    { 
        .CR1A = CR1A__ODR_Hz100 | CR1A__LPen | CR1A__Zen | CR1A__Yen | CR1A__Xen,
        .CR2A = CR2A__HPM_reset_reading,
        .CR3A = CR3A__NONE,
        .CR4A = CR4A__FS_g2,
        .CR5A = CR5A__NONE,
        .CR6A = CR6A__NONE
    }
};

// Typedefs for sensor and its readouts:
typedef struct lsm303_t {
    const i2c_link_t i2c_conn;
    const lsm_config_t config;
}lsm303_t;


typedef struct lsm_acc_reading_t {
    int16_t x;
    int16_t y;
    int16_t z;
} lsm_acc_reading_t;

typedef struct lsm_mag_reading_t {
    const int16_t x;
    const int16_t y;
    const int16_t z;
} lsm_mag_reading_t;

typedef int16_t lsm_tmp_reading_t;

typedef struct lsm_reading_t {
    const lsm_acc_reading_t acc;
    const lsm_mag_reading_t mag;
    const lsm_tmp_reading_t tmp;
} lsm_reading_t;


lsm303_t lsm_init(const i2c_link_t i2c, const lsm_config_t configuration);

lsm_acc_reading_t lsm_read_acc(const lsm303_t lsm);

lsm_mag_reading_t lsm_read_mag(const lsm303_t lsm);

lsm_tmp_reading_t lsm_read_tmp(const lsm303_t lsm);

lsm_reading_t lsm_read_sensors(const lsm303_t lsm);
