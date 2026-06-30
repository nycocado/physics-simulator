#pragma once

#include <gtk/gtk.h>

typedef struct _Window_Simulation* Window_Simulation;
typedef struct _Spin_Buttons_Simulation* Spin_Buttons_Simulation;
typedef struct _Buttons_Simulation* Buttons_Simulation;

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

struct _Window_Simulation
{
        GtkWidget* window;
        GtkWidget* drawing_area;
        struct _Spin_Buttons_Simulation spin_buttons;
        struct _Buttons_Simulation buttons;
        GtkWidget* follow_check;
        GtkWidget* zoom_check;
        GtkWidget* trail_check;
        GtkWidget* follow_spin;
};

Window_Simulation window_simulation_new();
void window_simulation_free(Window_Simulation window_simulation);