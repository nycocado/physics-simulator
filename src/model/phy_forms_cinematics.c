#include "phy_forms_cinematics.h"

#define M_PI 3.14159265358979323846

float phyc_position(float si, float v, float a, float t) // Calcular posição em determinado tempo
{
    return si + v * t + 0.5 * a * pow(t, 2);
}

float phyc_velocity(float vi, float a, float t) // Calcular velocidade em determinado tempo
{
    return (vi + a * t);
}

float phyc_medium_velocity(float pi, float pf, float ti, float tf) // Calcular velocidade média
{
    return (pf - pi) / (tf - ti);
}

float phyc_medium_acceleration(float vi, float vf, float t) // Calcular aceleração média
{
    return (vf - vi) / t;
}

float phyc_magnitude(float bx, float by) // Módulo de um vetor
{
    return sqrt(pow(bx, 2) + pow(by, 2));
}

float phyc_displacement_x_y(float ai, float af, float bi, float bf) // Deslocamento em x e y
{
    return phyc_magnitude(af - ai, bf - bi);
}

float phyc_magnitude_velocity(float vx, float vy) // Módulo da velocidade
{
    return phyc_magnitude(vx, vy);
}

float phyc_magnitude_acceleration(float ax, float ay) // Modulo da aceleração
{
    return phyc_magnitude(ax, ay);
}

float phyc_decompose_x(float b, float angle) // Decomposição em x
{
    return b * cos(angle);
}

float phyc_decompose_y(float b, float angle) // Decomposição em y
{
    return b * sin(angle);
}

float phyc_angle(float fx, float fy) // Ângulo de um vetor
{
    return atan2(fy, fx);
}

float phyc_degree_to_radian(float degree) // Conversão de graus para radianos
{
    return degree * (M_PI / 180.0);
}

float phyc_radian_to_degree(float radian) // Conversão de radianos para graus
{
    return radian * (180.0 / M_PI);
}
