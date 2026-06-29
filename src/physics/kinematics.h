#pragma once

#include <math.h>

double phyc_position(double si, double v, double a, double t);
double phyc_velocity(double vi, double a, double t);
double phyc_medium_velocity(double pi, double pf, double ti, double tf);
double phyc_medium_acceleration(double vi, double vf, double t);

double phyc_degree_to_radian(double degree);
double phyc_radian_to_degree(double radian);