#include "phy_forms_dynamics.h"

#define M_PI 3.14159265358979323846

float phyd_force_p(float m, float g) // Calcular força peso
{
    return m * g;
}

float phyd_force_r(float m, float a) // Calcular força resultante
{
    return m * a;
}

float phyd_decompose_force_x(float b, float angle) // Decomposição em x
{
    return b * cos(angle);
}

float phyd_decompose_force_y(float b, float angle) // Decomposição em y
{
    return b * sin(angle);
}

float phyd_acceleration(float f, float m) // Calcular aceleração
{
    return f / m;
}