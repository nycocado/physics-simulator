#pragma once

#include <gtk/gtk.h>

#include "gtk_variables.h"
#include "gtk_window_add_force_normal.h"
#include "gtk_window_add_particle_normal.h"
#include "gtk_window_edit_force_normal.h"
#include "gtk_window_edit_particle_normal.h"
#include "gtk_window_main.h"
#include "gtk_window_simulation.h"

typedef struct _GtkApp* GtkApp;

struct _GtkApp
{
        Window_Main window_main;
        Window_Add_Particle_Normal window_add_particle_normal;
        Window_Add_Force_Normal window_add_force_normal;
        Window_Edit_Particle_Normal window_edit_particle_normal;
        Window_Edit_Force_Normal window_edit_force_normal;
        Window_Simulation window_simulation;
        GtkTreeStore* tree_store;
        GtkTreeView* tree_view;
        GtkTreeSelection* selection;
        Variables variables;
};

extern GtkApp app;

void gtk_app_new();
void gtk_app_free();