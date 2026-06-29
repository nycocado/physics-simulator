#pragma once

#include <gtk/gtk.h>

#include "particles/buttons.h"
#include "particles/force_dialog.h"
#include "particles/particle_dialog.h"
#include "ui/window_main.h"
#include "ui/window_simulation.h"
#include "variables.h"

typedef struct _GtkApp* GtkApp;
typedef struct _Variables* Variables;
typedef struct _Window_Main* Window_Main;
typedef struct _Window_Add_Particle_Normal* Window_Add_Particle_Normal;
typedef struct _Window_Add_Force_Normal* Window_Add_Force_Normal;
typedef struct _Window_Edit_Particle_Normal* Window_Edit_Particle_Normal;
typedef struct _Window_Edit_Force_Normal* Window_Edit_Force_Normal;
typedef struct _Window_Simulation* Window_Simulation;

struct _GtkApp
{
        Window_Main window_main;
        Window_Add_Particle_Normal window_add_particle_normal;
        Window_Add_Force_Normal window_add_force_normal;
        Window_Edit_Particle_Normal window_edit_particle_normal;
        Window_Edit_Force_Normal window_edit_force_normal;
        Window_Simulation window_simulation;
        GListStore* root_store;
        GtkTreeListModel* tree_model;
        GtkSelectionModel* selection_model;
        GtkColumnView* column_view;
        Variables variables;
};

GtkApp gtk_app_new();
void gtk_app_free(GtkApp app);
