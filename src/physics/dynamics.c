#include "dynamics.h"
#include "simulation/dynamic_sim.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double phyd_force_p(double m, double g) { return m * g; }

double phyd_force_r(double m, double a) { return m * a; }

double phyd_decompose_force_x(double b, double angle) { return b * cos(angle); }

double phyd_decompose_force_y(double b, double angle) { return b * sin(angle); }

double phyd_acceleration(double f, double m) { return f / m; }