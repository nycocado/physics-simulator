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

typedef struct _Window_Add_Particle_Normal* Window_Add_Particle_Normal;

struct _Window_Add_Particle_Normal
{
        GtkWidget* window;
        struct _Spin_Buttons_Add_Particle_Normal spin_buttons;
        struct _Buttons_Add buttons;
};

struct _Window_Edit_Particle_Normal
{
        GtkWidget* window;
        struct _Spin_Buttons_Add_Particle_Normal spin_buttons;
        struct _Buttons_Edit buttons;
};

Window_Add_Particle_Normal window_add_particle_normal_new();
void window_add_particle_normal_free(
    Window_Add_Particle_Normal window_add_particle_normal
);

typedef struct _Window_Edit_Particle_Normal* Window_Edit_Particle_Normal;

Window_Edit_Particle_Normal window_edit_particle_normal_new();
void window_edit_particle_normal_free(
    Window_Edit_Particle_Normal window_edit_particle_normal
);
