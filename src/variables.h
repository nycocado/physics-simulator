#pragma once

#include "particles/particle.h"
#include <gtk/gtk.h>

typedef struct _Variables* Variables;
typedef struct _Variables_Simulation* Variables_Simulation;
typedef struct _Variables_Project* Variables_Project;


struct _Variables_Simulation
{
        gboolean is_simulation_running;
        int num_particles_use;
        Particle_Cinematic_Collection particle_cinematic_collection;
        Particle_Dynamic_Collection particle_dynamic_collection;
        double gravity;
        double time;
        double time_step;
        double gravity_cache;
        double time_cache;
        double time_step_cache;
        double frames;
        double last_time;
        GTimer* timer;
        guint timeout_id;
        gboolean first_time;
};

struct _Variables_Project
{
        gchar* file_path;
        gboolean is_file_open;
};

struct _Variables
{
        struct _Variables_Simulation simulation;
        struct _Variables_Project project;
        int window_width;
        int window_height;
};

Variables variables_new();
void variables_free(Variables variables);
void variables_simulation_wipe(Variables_Simulation variables_simulation);
void variables_project_wipe(Variables_Project variables_project);