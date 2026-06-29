#pragma once

#include <gtk/gtk.h>

typedef struct _Buttons_Add* Buttons_Add;

struct _Buttons_Add
{
        GtkWidget* add;
        GtkWidget* cancel;
};


typedef struct _Buttons_Edit* Buttons_Edit;

struct _Buttons_Edit
{
        GtkWidget* edit;
        GtkWidget* cancel;
};

