#pragma once

#include <gtk/gtk.h>

#include "buttons.h"

typedef struct _Spin_Buttons_Add_Force_Normal* Spin_Buttons_Add_Force_Normal;

struct _Spin_Buttons_Add_Force_Normal
{
        GtkWidget* fx;
        GtkWidget* fy;
};



typedef struct _Window_Add_Force_Normal* Window_Add_Force_Normal;

struct _Window_Add_Force_Normal
{
        GtkWidget* window;
        struct _Spin_Buttons_Add_Force_Normal spin_buttons;
        struct _Buttons_Add buttons;
};

struct _Window_Edit_Force_Normal
{
        GtkWidget* window;
        struct _Spin_Buttons_Add_Force_Normal spin_buttons;
        struct _Buttons_Edit buttons;
};

Window_Add_Force_Normal window_add_force_normal_new();
void window_add_force_normal_free(Window_Add_Force_Normal window_add_force_normal
);

typedef struct _Window_Edit_Force_Normal* Window_Edit_Force_Normal;

Window_Edit_Force_Normal window_edit_force_normal_new();
void window_edit_force_normal_free(
    Window_Edit_Force_Normal window_edit_force_normal
);
