#include "../inc/lsm303DLHC.h"

#define sizeof_array(array)		                    ( sizeof(array) / sizeof(array[0]) )
#define init_uint16(array, index_high, index_low)   ( (uint16_t)(array[index_high]  << 8) | array[index_low] )

lsm303_t lsm_init(const i2c_link_t i2c, const lsm_config_t configuration)
{
    // Write the accelerometer control registers to the IC:
    i2c.write(LSM_ACC_SAD_W, CTRL_REG1_A, &configuration.CR1A, 1 );
    i2c.write(LSM_ACC_SAD_W, CTRL_REG2_A, &configuration.CR2A, 1 );
    i2c.write(LSM_ACC_SAD_W, CTRL_REG3_A, &configuration.CR3A, 1 );
    i2c.write(LSM_ACC_SAD_W, CTRL_REG4_A, &configuration.CR4A, 1 );
    i2c.write(LSM_ACC_SAD_W, CTRL_REG5_A, &configuration.CR5A, 1 );
    i2c.write(LSM_ACC_SAD_W, CTRL_REG6_A, &configuration.CR6A, 1 );

    lsm303_t ret = {i2c, configuration};
    return ret;
}

lsm_acc_reading_t lsm_read_acc(const lsm303_t lsm)
{
    
    lsm_acc_reading_t ret = { 0,0,0 };

    if( ( lsm.config.CR1A && CR1A__Xen ) && 
        ( lsm.config.CR1A && CR1A__Yen ) &&
        ( lsm.config.CR1A && CR1A__Zen ) )
        {
            uint8_t data[sizeof(lsm_acc_reading_t)];
            lsm.i2c_conn.read(LSM_ACC_SAD_R, OUT_X_L_A, data, sizeof_array(data));
            ret.x = init_uint16(data, 1, 0);
            ret.y = init_uint16(data, 3, 2); 
            ret.z = init_uint16(data, 5, 4);
        }


    if( lsm.config.CR1A && CR1A__Xen)
    {
        uint8_t data[sizeof(int16_t)];
        lsm.i2c_conn.read(LSM_ACC_SAD_R, OUT_X_L_A, data, sizeof_array(data));
        ret.x = init_uint16(data, 1, 0);
    }


    if( lsm.config.CR1A && CR1A__Yen) 
    {
        uint8_t data[sizeof(int16_t)];
        lsm.i2c_conn.read(LSM_ACC_SAD_R, OUT_Y_L_A, data, sizeof_array(data));
        ret.y = init_uint16(data, 1, 0);
    }

    if( lsm.config.CR1A && CR1A__Zen) 
    {
        uint8_t data[sizeof(int16_t)];
        lsm.i2c_conn.read(LSM_ACC_SAD_R, OUT_Z_L_A, data, sizeof_array(data));
        ret.z = init_uint16(data, 1, 0);
    }

    return ret;
}

lsm_mag_reading_t lsm_read_mag(const lsm303_t lsm)
{
    (void)lsm;
    lsm_mag_reading_t ret = { 0,0,0 };
    return ret;
}

lsm_tmp_reading_t lsm_read_tmp(const lsm303_t lsm)
{
    (void)lsm;
    lsm_tmp_reading_t ret = 0;
    return ret;
}

lsm_reading_t lsm_read_sensors(const lsm303_t lsm)
{
    (void)lsm;
    lsm_reading_t ret = {};
    return ret;
}