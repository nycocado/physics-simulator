#include "dynamics.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float phyd_force_p(float m, float g) { return m * g; }

float phyd_force_r(float m, float a) { return m * a; }

float phyd_decompose_force_x(float b, float angle) { return b * cos(angle); }

float phyd_decompose_force_y(float b, float angle) { return b * sin(angle); }

float phyd_acceleration(float f, float m) { return f / m; }