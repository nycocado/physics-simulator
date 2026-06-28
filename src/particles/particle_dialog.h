#pragma once

#include <gtk/gtk.h>

#include "buttons.h"

typedef struct _Spin_Buttons_Add_Particle_Normal*
    Spin_Buttons_Add_Particle_Normal;

struct _Spin_Buttons_Add_Particle_Normal
{
        GtkWidget* x;
        GtkWidget* y;
        GtkWidget* vx;
        GtkWidget* vy;
        GtkWidget* ax;
        GtkWidget* ay;
        GtkWidget* mass;
};

Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal_new();
void spin_buttons_add_particle_normal_free(
    Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal
);

typedef struct _Window_Add_Particle_Normal* Window_Add_Particle_Normal;

struct _Window_Add_Particle_Normal
{
        GtkWidget* window;
        Spin_Buttons_Add_Particle_Normal spin_buttons;
        Buttons_Add buttons;
};

Window_Add_Particle_Normal window_add_particle_normal_new();
void window_add_particle_normal_free(
    Window_Add_Particle_Normal window_add_particle_normal
);

typedef struct _Window_Edit_Particle_Normal* Window_Edit_Particle_Normal;

struct _Window_Edit_Particle_Normal
{
        GtkWidget* window;
        Spin_Buttons_Add_Particle_Normal spin_buttons;
        Buttons_Edit buttons;
};

Window_Edit_Particle_Normal window_edit_particle_normal_new();
void window_edit_particle_normal_free(
    Window_Edit_Particle_Normal window_edit_particle_normal
);
