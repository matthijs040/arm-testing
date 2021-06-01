#include "../inc/lsm303DLHC.h"

lsm303_t lsm_init(const i2c_link_t i2c, const lsm_config_t configuration)
{
    i2c.write(LSM_ACC_SAD_W, CTRL_REG1_A, configuration.ctrl_registers, sizeof(configuration.ctrl_registers) );
    lsm303_t ret = {};
    return ret;
}

lsm_acc_reading_t lsm_read_acc(const lsm303_t lsm)
{
    (void)lsm;
    lsm_acc_reading_t ret = { 0,0,0 };
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