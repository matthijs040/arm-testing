#pragma once


#define MAXFLOAT	3.40282347e+38F

#define M_E		    2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		_M_LN2
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440

#define M_TWOPI     (M_PI * 2.0)
#define M_3PI_4		2.3561944901923448370E0
#define M_SQRTPI    1.77245385090551602792981
#define M_LN2LO     1.9082149292705877000E-10
#define M_LN2HI     6.9314718036912381649E-1
#define M_SQRT3	    1.73205080756887719000
#define M_IVLN10    0.43429448190325182765 /* 1 / log(10) */
#define M_LOG2_E    _M_LN2
#define M_INVLN2    1.4426950408889633870E0  /* 1 / log(2) */


#include <math.h>

// Amount of g's of acceleration tolerance before returning 0.
// Taking into account Z axis bias.
#define ACCELERATION_TOLERANCE 2.2

/**
 * @brief a struct describing attitude where:
 *  r is the rotation around the Z axis in degrees
 *  p is the rotation around the X axis in degrees
 *  y is the rotation around the Y axis in degrees
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
    float total = fabs(x) + fabs(y) + fabs(z);
    if( total > ACCELERATION_TOLERANCE )
    {
        return ret;
    }

    ret.r = ( atan2(y, x) / M_TWOPI ) * 360;
    ret.p = ( atan2(y, z) / M_TWOPI ) * 360;
    ret.y = ( atan2(z, x) / M_TWOPI ) * 360;

    return ret;
}