#pragma once

#include <math.h>

float phyd_force_p(float m, float g);               // Calcular força peso
float phyd_force_r(float m, float a);               // Calcular força resultante
float phyd_decompose_force_x(float b, float angle); // Decomposição em x
float phyd_decompose_force_y(float b, float angle); // Decomposição em y
float phyd_acceleration(float f, float m);          // Calcular aceleração