#include "phy_forms_cinematics.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float phyc_position(float si, float v, float a, float t)
{
    return si + v * t + 0.5f * a * (t * t);
}

float phyc_velocity(float vi, float a, float t) { return (vi + a * t); }

float phyc_medium_velocity(float pi, float pf, float ti, float tf)
{
    return (pf - pi) / (tf - ti);
}

float phyc_medium_acceleration(float vi, float vf, float t)
{
    return (vf - vi) / t;
}

float phyc_magnitude(float bx, float by)
{
    return sqrt(bx * bx + by * by);
}

float phyc_displacement_x_y(float ai, float af, float bi, float bf)
{
    return phyc_magnitude(af - ai, bf - bi);
}

float phyc_magnitude_velocity(float vx, float vy)
{
    return phyc_magnitude(vx, vy);
}

float phyc_magnitude_acceleration(float ax, float ay)
{
    return phyc_magnitude(ax, ay);
}

float phyc_decompose_x(float b, float angle) { return b * cos(angle); }

float phyc_decompose_y(float b, float angle) { return b * sin(angle); }

float phyc_angle(float fx, float fy) { return atan2(fy, fx); }

float phyc_degree_to_radian(float degree) { return degree * (M_PI / 180.0); }

float phyc_radian_to_degree(float radian) { return radian * (180.0 / M_PI); }
