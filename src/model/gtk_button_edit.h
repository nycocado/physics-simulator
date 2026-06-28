#pragma once

#include <gtk/gtk.h>

typedef struct _Buttons_Edit* Buttons_Edit;

struct _Buttons_Edit
{
        GtkWidget* edit;
        GtkWidget* cancel;
};

Buttons_Edit buttons_edit_new();
void buttons_edit_free(Buttons_Edit buttons_edit);