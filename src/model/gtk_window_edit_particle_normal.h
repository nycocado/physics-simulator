#pragma once

#include <gtk/gtk.h>

#include "gtk_button_edit.h"
#include "gtk_spin_buttons_add_particle_normal.h"

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