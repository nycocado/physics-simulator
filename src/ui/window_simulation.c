#include "gtk_include_all.h"

Window_Simulation window_simulation_new()
{
    Window_Simulation window_simulation = g_new0(struct _Window_Simulation, 1);
    return window_simulation;
}

void window_simulation_free(Window_Simulation window_simulation)
{
    g_free(window_simulation);
}