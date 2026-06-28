#pragma once

#include <math.h>

float phyc_position(float si, float v, float a, float t);
float phyc_velocity(float vi, float a, float t);
float phyc_medium_velocity(float pi, float pf, float ti, float tf);
float phyc_medium_acceleration(float vi, float vf, float t);
float phyc_magnitude(float bx, float by);
float phyc_displacement_x_y(float ai, float af, float bi, float bf);
float phyc_magnitude_velocity(float vx, float vy);
float phyc_magnitude_acceleration(float ax, float ay);
float phyc_decompose_x(float b, float angle);
float phyc_decompose_y(float b, float angle);
float phyc_angle(float fx, float fy);
float phyc_degree_to_radian(float degree);
float phyc_radian_to_degree(float radian);