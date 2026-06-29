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

/* Foundational structs — no project-header dependencies */
#include "particles/buttons.h"
#include "particles/force_dialog.h"
#include "particles/particle.h"
#include "particles/particle_dialog.h"
#include "phys_item.h"
#include "physics/dynamics.h"
#include "physics/kinematics.h"
#include "ui/window_main.h"
#include "ui/window_simulation.h"
#include "variables.h"

/* GtkApp struct — depends on the foundational structs above */
#include "app.h"

/* Everything that references GtkApp */
#include "collection.h"
#include "log.h"
#include "project.h"
#include "simulation/dynamic_sim.h"
#include "simulation/kinematic_sim.h"
#include "simulation/simulation.h"
#include "ui/builder.h"
#include "ui/callbacks.h"
#include "ui/main_window.h"
typedef struct _GtkApp* GtkApp;
