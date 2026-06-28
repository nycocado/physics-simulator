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

#include "callbacks.h"
#include "builder.h"
#include "main_window.h"
#include "simulation_cinematic.h"
#include "simulation_commun.h"
#include "simulation_dynamic.h"

#include "../model/app.h"
#include "../model/buttons.h"
#include "../model/force_dialog.h"
#include "../model/particle_dialog.h"
#include "../model/variables.h"
#include "../model/window_main.h"
#include "../model/window_simulation.h"
#include "../model/particle.h"
#include "../model/phy_forms_cinematics.h"
#include "../model/phy_forms_dynamics.h"

#include "../control/collection.h"
#include "../control/log.h"
#include "../control/project.h"