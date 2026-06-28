#include "../include/gtk_include_all.h"

Variables variables_new()
{
    Variables variables = g_new(struct _Variables, 1);

    variables->project = variables_project_new();
    variables->simulation = variables_simulation_new();
    variables->window_size = window_size_new();
    return variables;
}

void variables_free(Variables variables)
{
    variables_project_free(variables->project);
    variables_simulation_free(variables->simulation);
    window_size_free(variables->window_size);
    g_free(variables);
}

Variables_Simulation variables_simulation_new()
{
    Variables_Simulation variables_simulation =
        g_new(struct _Variables_Simulation, 1);

    variables_simulation->is_simulation_running = FALSE;
    variables_simulation->num_particles_use = 0;
    variables_simulation->particle_cinematic_collection = NULL;
    variables_simulation->particle_dynamic_collection = NULL;
    variables_simulation->gravity = 0;
    variables_simulation->time = 0;
    variables_simulation->time_step = 0;
    variables_simulation->gravity_cache = 0;
    variables_simulation->time_cache = 0;
    variables_simulation->time_step_cache = 0;
    variables_simulation->frames = 0;
    variables_simulation->timer = NULL;
    variables_simulation->last_time = 0;
    variables_simulation->first_time = TRUE;
    return variables_simulation;
}

void variables_simulation_wipe(Variables_Simulation variables_simulation)
{
    if (variables_simulation->particle_cinematic_collection != NULL)
    {
        particle_cinematic_collection_free(
            variables_simulation->particle_cinematic_collection
        );
    }
    if (variables_simulation->particle_dynamic_collection != NULL)
    {
        particle_dynamic_collection_free(
            variables_simulation->particle_dynamic_collection
        );
    }
    if (variables_simulation->timer != NULL)
    {
        g_timer_stop(variables_simulation->timer);
        g_timer_destroy(variables_simulation->timer);
        variables_simulation->timer = NULL;
    }

    variables_simulation->last_time = 0;
    variables_simulation->gravity_cache = 0;
    variables_simulation->time_cache = 0;
    variables_simulation->time_step_cache = 0;
    variables_simulation->is_simulation_running = FALSE;
    variables_simulation->particle_cinematic_collection = NULL;
    variables_simulation->particle_dynamic_collection = NULL;
    variables_simulation->first_time = TRUE;
}

void variables_simulation_free(Variables_Simulation variables_simulation)
{
    variables_simulation_wipe(variables_simulation);
    g_free(variables_simulation);
}

Variables_Project variables_project_new()
{
    Variables_Project variables_project = g_new(struct _Variables_Project, 1);

    variables_project->file_path = NULL;
    variables_project->is_file_open = FALSE;
    return variables_project;
}

void variables_project_wipe(Variables_Project variables_project)
{
    if (variables_project->file_path != NULL)
    {
        g_free(variables_project->file_path);
    }

    variables_project->file_path = NULL;
    variables_project->is_file_open = FALSE;
}

void variables_project_free(Variables_Project variables_project)
{
    variables_project_wipe(variables_project);
    g_free(variables_project);
}

Window_Size window_size_new()
{
    Window_Size window_size = g_new(struct _Window_Size, 1);

    window_size->width = 0;
    window_size->height = 0;
    return window_size;
}

void window_size_free(Window_Size window_size) { g_free(window_size); }