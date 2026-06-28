#pragma once

#include <math.h>

float phyd_force_p(float m, float g);
float phyd_force_r(float m, float a);
float phyd_decompose_force_x(float b, float angle);
float phyd_decompose_force_y(float b, float angle);
float phyd_acceleration(float f, float m);