#pragma once

#include <math.h>

double phyd_force_p(double m, double g);
double phyd_force_r(double m, double a);
double phyd_decompose_force_x(double b, double angle);
double phyd_decompose_force_y(double b, double angle);
double phyd_acceleration(double f, double m);