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

#include "ui/callbacks.h"
#include "ui/builder.h"
#include "ui/main_window.h"
#include "simulation/kinematic_sim.h"
#include "simulation/simulation.h"
#include "simulation/dynamic_sim.h"

#include "app.h"
#include "particles/buttons.h"
#include "particles/force_dialog.h"
#include "particles/particle_dialog.h"
#include "variables.h"
#include "ui/window_main.h"
#include "ui/window_simulation.h"
#include "particles/particle.h"
#include "physics/kinematics.h"
#include "physics/dynamics.h"

#include "collection.h"
#include "log.h"
#include "project.h"
