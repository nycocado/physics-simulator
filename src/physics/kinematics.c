#include "kinematics.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double phyc_position(double si, double v, double a, double t)
{
    return si + v * t + 0.5 * a * pow(t, 2);
}

double phyc_velocity(double vi, double a, double t) { return (vi + a * t); }

double phyc_medium_velocity(double pi, double pf, double ti, double tf)
{
    return (pf - pi) / (tf - ti);
}

double phyc_medium_acceleration(double vi, double vf, double t)
{
    return (vf - vi) / t;
}



double phyc_degree_to_radian(double degree) { return degree * (M_PI / 180.0); }

double phyc_radian_to_degree(double radian) { return radian * (180.0 / M_PI); }
