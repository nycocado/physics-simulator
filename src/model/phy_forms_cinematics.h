#pragma once

#include <math.h>

float phyc_position(float si, float v, float a, float t);            // Calcular posição em determinado tempo
float phyc_velocity(float vi, float a, float t);                     // Calcular velocidade em determinado tempo
float phyc_medium_velocity(float pi, float pf, float ti, float tf);  // Calcular velocidade média
float phyc_medium_acceleration(float vi, float vf, float t);         // Calcular aceleração média
float phyc_magnitude(float bx, float by);                            // Módulo de um vetor
float phyc_displacement_x_y(float ai, float af, float bi, float bf); // Deslocamento em x e y
float phyc_magnitude_velocity(float vx, float vy);                   // Módulo da velocidade
float phyc_magnitude_acceleration(float ax, float ay);               // Modulo da aceleração
float phyc_decompose_x(float b, float angle);                        // Decomposição em x
float phyc_decompose_y(float b, float angle);                        // Decomposição em y
float phyc_angle(float fx, float fy);                                // Ângulo de um vetor
float phyc_degree_to_radian(float degree);                           // Conversão de graus para radianos
float phyc_radian_to_degree(float radian);                           // Conversão de radianos para graus