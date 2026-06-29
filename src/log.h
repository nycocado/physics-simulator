#pragma once
typedef struct _GtkApp* GtkApp;
typedef struct _Particle_Cinematic_Collection* Particle_Cinematic_Collection;
typedef struct _Particle_Dynamic_Collection* Particle_Dynamic_Collection;
#include <gtk/gtk.h>

char* generate_log_name_for_simulation(const char* base_name, GtkApp app);
void replace_dot_with_comma(char* str);
void save_simulation_cinematic_log(
    Particle_Cinematic_Collection particle_collection,
    double time,
    double time_step,
    double gravity,
    GtkApp app
);
void save_simulation_dynamic_log(
    Particle_Dynamic_Collection particle_collection,
    double time,
    double time_step,
    double gravity,
    GtkApp app
);
