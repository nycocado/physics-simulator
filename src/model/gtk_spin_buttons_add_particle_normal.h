#pragma once

#include <gtk/gtk.h>

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