#pragma once

#include <gtk/gtk.h>

typedef struct _Window_Simulation* Window_Simulation;
typedef struct _Spin_Buttons_Simulation* Spin_Buttons_Simulation;
typedef struct _Buttons_Simulation* Buttons_Simulation;

struct _Window_Simulation
{
        GtkWidget* window;
        GtkWidget* drawing_area;
        Spin_Buttons_Simulation spin_buttons;
        Buttons_Simulation buttons;
};

struct _Spin_Buttons_Simulation
{
        GtkWidget* gravity;
        GtkWidget* time;
        GtkWidget* step;
        GtkWidget* frames;
};

struct _Buttons_Simulation
{
        GtkWidget* start;
        GtkWidget* stop;
        GtkWidget* refresh;
};

Window_Simulation window_simulation_new();
void window_simulation_free(Window_Simulation window_simulation);
Spin_Buttons_Simulation spin_buttons_simulation_new();
void spin_buttons_simulation_free(Spin_Buttons_Simulation spin_buttons);
Buttons_Simulation buttons_simulation_new();
void buttons_simulation_free(Buttons_Simulation buttons);