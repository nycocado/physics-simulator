#pragma once

#include "variables.h"
#include <gtk/gtk.h>

char* generate_log_name_for_simulation(const char* base_name);
void replace_dot_with_comma(char* str);
void save_simulation_cinematic_log(
    Particle_Cinematic_Collection particle_collection,
    float time,
    float time_step,
    float gravity
);
int calc_num_forces_max(Particle_Dynamic_Collection particle_collection);
void save_simulation_dynamic_log(
    Particle_Dynamic_Collection particle_collection,
    float time,
    float time_step,
    float gravity
);