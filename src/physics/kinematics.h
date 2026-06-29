#pragma once

#include <math.h>

double phyc_position(double si, double v, double a, double t);
double phyc_velocity(double vi, double a, double t);
double phyc_medium_velocity(double pi, double pf, double ti, double tf);
double phyc_medium_acceleration(double vi, double vf, double t);
double phyc_magnitude(double bx, double by);
double phyc_displacement_x_y(double ai, double af, double bi, double bf);
double phyc_magnitude_velocity(double vx, double vy);
double phyc_magnitude_acceleration(double ax, double ay);
double phyc_decompose_x(double b, double angle);
double phyc_decompose_y(double b, double angle);
double phyc_angle(double fx, double fy);
double phyc_degree_to_radian(double degree);
double phyc_radian_to_degree(double radian);