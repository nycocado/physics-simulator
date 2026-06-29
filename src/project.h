#pragma once
typedef struct _GtkApp* GtkApp;
#include <gtk/gtk.h>

void save_project(GtkApp app);
void open_project(GtkApp app);
void close_project(GtkApp app);
