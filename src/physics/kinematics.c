#include "kinematics.h"
#include "simulation/kinematic_sim.h"
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

double phyc_magnitude(double bx, double by)
{
    return sqrt(pow(bx, 2) + pow(by, 2));
}

double phyc_displacement_x_y(double ai, double af, double bi, double bf)
{
    return phyc_magnitude(af - ai, bf - bi);
}

double phyc_magnitude_velocity(double vx, double vy)
{
    return phyc_magnitude(vx, vy);
}

double phyc_magnitude_acceleration(double ax, double ay)
{
    return phyc_magnitude(ax, ay);
}

double phyc_decompose_x(double b, double angle) { return b * cos(angle); }

double phyc_decompose_y(double b, double angle) { return b * sin(angle); }

double phyc_angle(double fx, double fy) { return atan2(fy, fx); }

double phyc_degree_to_radian(double degree) { return degree * (M_PI / 180.0); }

double phyc_radian_to_degree(double radian) { return radian * (180.0 / M_PI); }
