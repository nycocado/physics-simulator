#pragma once

#include <gtk/gtk.h>

typedef struct _Spin_Buttons_Add_Force_Normal* Spin_Buttons_Add_Force_Normal;

struct _Spin_Buttons_Add_Force_Normal
{
        GtkWidget* fx;
        GtkWidget* fy;
};

Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal_new();
void spin_buttons_add_force_normal_free(
    Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal
);