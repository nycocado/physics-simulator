#include "../include/gtk_include_all.h"

Window_Simulation window_simulation_new()
{
    Window_Simulation window_simulation =
        g_slice_new(struct _Window_Simulation);
    window_simulation->window = NULL;
    window_simulation->drawing_area = NULL;
    window_simulation->buttons = buttons_simulation_new();
    window_simulation->spin_buttons = spin_buttons_simulation_new();
    return window_simulation;
}

void window_simulation_free(Window_Simulation window_simulation)
{
    buttons_simulation_free(window_simulation->buttons);
    spin_buttons_simulation_free(window_simulation->spin_buttons);
    g_slice_free(struct _Window_Simulation, window_simulation);
}

Spin_Buttons_Simulation spin_buttons_simulation_new()
{
    Spin_Buttons_Simulation spin_buttons =
        g_slice_new(struct _Spin_Buttons_Simulation);

    spin_buttons->gravity = NULL;
    spin_buttons->time = NULL;
    spin_buttons->step = NULL;
    spin_buttons->frames = NULL;
    return spin_buttons;
}

void spin_buttons_simulation_free(Spin_Buttons_Simulation spin_buttons)
{
    g_slice_free(struct _Spin_Buttons_Simulation, spin_buttons);
}

Buttons_Simulation buttons_simulation_new()
{
    Buttons_Simulation buttons = g_slice_new(struct _Buttons_Simulation);

    buttons->start = NULL;
    buttons->stop = NULL;
    buttons->refresh = NULL;
    return buttons;
}

void buttons_simulation_free(Buttons_Simulation buttons)
{
    g_slice_free(struct _Buttons_Simulation, buttons);
}