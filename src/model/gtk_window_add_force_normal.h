#pragma once

#include <gtk/gtk.h>

#include "gtk_button_add.h"
#include "gtk_spin_buttons_add_force_normal.h"

typedef struct _Window_Add_Force_Normal* Window_Add_Force_Normal;

struct _Window_Add_Force_Normal
{
        GtkWidget* window;
        Spin_Buttons_Add_Force_Normal spin_buttons;
        Buttons_Add buttons;
};

Window_Add_Force_Normal window_add_force_normal_new();
void window_add_force_normal_free(
    Window_Add_Force_Normal window_add_force_normal
);