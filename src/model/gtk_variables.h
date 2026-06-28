#pragma once

#include "particle.h"
#include <gtk/gtk.h>

typedef struct _Variables* Variables;
typedef struct _Variables_Simulation* Variables_Simulation;
typedef struct _Variables_Project* Variables_Project;
typedef struct _Window_Size* Window_Size;

struct _Variables
{
        Variables_Simulation simulation;
        Variables_Project project;
        Window_Size window_size;
};

struct _Variables_Simulation
{
        gboolean is_simulation_running;
        int num_particles_use;
        Particle_Cinematic_Collection particle_cinematic_collection;
        Particle_Dynamic_Collection particle_dynamic_collection;
        float gravity;
        float time;
        float time_step;
        float gravity_cache;
        float time_cache;
        float time_step_cache;
        float frames;
        float last_time;
        GTimer* timer;
        gboolean firts_time;
};

struct _Variables_Project
{
        gchar* file_path;
        gboolean is_file_open;
};

struct _Window_Size
{
        int width;
        int height;
};

Variables variables_new();
void variables_free(Variables variables);
Variables_Simulation variables_simulation_new();
void variables_simulation_wipe(Variables_Simulation variables_simulation);
void variables_simulation_free(Variables_Simulation variables_simulation);
Variables_Project variables_project_new();
void variables_project_wipe(Variables_Project variables_project);
void variables_project_free(Variables_Project variables_project);
Window_Size window_size_new();
void window_size_free(Window_Size window_size);