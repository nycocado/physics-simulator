#pragma once

#include <gtk/gtk.h>

typedef struct _Buttons_Add* Buttons_Add;

struct _Buttons_Add
{
        GtkWidget* add;
        GtkWidget* cancel;
};

Buttons_Add buttons_add_new();
void buttons_add_free(Buttons_Add buttons_add);