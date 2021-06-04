#pragma once

#include <math.h>

// Amount of g's of acceleration tolerance before
#define ACCELERATION_TOLERANCE 0.1

/**
 * @brief a struct describing attitude where:
 *  r is the rotation around the Z axis in radians
 *  p is the rotation around the X axis in radians
 *  y is the rotation around the Y axis in radians
 */
typedef struct attitude_t 
{
    float r;
    float p;
    float y;
}attitude_t;

/**
 * @brief 
 * 
 * @param x acceleration in factor of gravitation 
 * @param y acceleration in factor of gravitation 
 * @param z acceleration in factor of gravitation 
 * @return attitude_t 
 */
attitude_t estimate_attitude(float x, float y, float z)
{
    attitude_t ret = { 0.0,0.0,0.0};

    // If the sensor is under external acceleration:
    float total = fabsf(x) + fabsf(y) + fabsf(z);
    if( total > ( 1.0 + ACCELERATION_TOLERANCE) )
    {
        return ret;
    }


    ret.r = atan2(y, x);
    ret.p = atan2(y, z);
    ret.y = atan2(z, x);

    return ret;
}