#pragma once

#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>

typedef enum
{
    SIMULATION_CINEMATIC = 1,
    SIMULATION_DYNAMIC = 2,
} SimulationMode;

typedef enum
{
    COL_X = 0,
    COL_Y = 1,
    COL_VX = 2,
    COL_VY = 3,
    COL_AX = 4,
    COL_AY = 5,
    COL_MASS = 6,
    COL_CHECKED = 7,
    COL_VISIBLE = 8,
    COL_TYPE = 9,
} ParticleColumn;

#include "gtk_callbacks.h"
#include "gtk_create_window.h"
#include "gtk_main.h"
#include "simulation_cinematic.h"
#include "simulation_commun.h"
#include "simulation_dynamic.h"

#include "../model/gtk_app.h"
#include "../model/gtk_button_add.h"
#include "../model/gtk_button_edit.h"
#include "../model/gtk_spin_buttons_add_force_normal.h"
#include "../model/gtk_spin_buttons_add_particle_normal.h"
#include "../model/gtk_variables.h"
#include "../model/gtk_window_add_force_normal.h"
#include "../model/gtk_window_add_particle_normal.h"
#include "../model/gtk_window_edit_force_normal.h"
#include "../model/gtk_window_edit_particle_normal.h"
#include "../model/gtk_window_main.h"
#include "../model/gtk_window_simulation.h"
#include "../model/particle.h"
#include "../model/phy_forms_cinematics.h"
#include "../model/phy_forms_dynamics.h"

#include "../control/gtk_collection.h"
#include "../control/gtk_log.h"
#include "../control/gtk_project.h"