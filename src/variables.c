#include "variables.h"
#include "collection.h"
#include "project.h"
#include "simulation/dynamic_sim.h"

Variables variables_new()
{
    Variables variables = g_new0(struct _Variables, 1);
    variables->simulation.first_time = TRUE;
    variables->simulation.gravity = 9.80;
    variables->simulation.time = 10.0;
    variables->simulation.time_step = 0.01;
    variables->simulation.frames = 60.0;
    return variables;
}

void variables_free(Variables variables)
{
    variables_project_wipe(&variables->project);
    variables_simulation_wipe(&variables->simulation);
    g_free(variables);
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
    variables_simulation->gravity = 9.80;
    variables_simulation->time = 10.0;
    variables_simulation->time_step = 0.01;
    variables_simulation->frames = 60.0;
    variables_simulation->camera_initialized = FALSE;
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
