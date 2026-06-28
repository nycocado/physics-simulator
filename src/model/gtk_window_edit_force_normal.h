#pragma once

#include <gtk/gtk.h>

#include "gtk_button_edit.h"
#include "gtk_spin_buttons_add_force_normal.h"

typedef struct _Window_Edit_Force_Normal* Window_Edit_Force_Normal;

struct _Window_Edit_Force_Normal
{
        GtkWidget* window;
        Spin_Buttons_Add_Force_Normal spin_buttons;
        Buttons_Edit buttons;
};

Window_Edit_Force_Normal window_edit_force_normal_new();
void window_edit_force_normal_free(
    Window_Edit_Force_Normal window_edit_force_normal
);