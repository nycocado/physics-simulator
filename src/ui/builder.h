#pragma once
typedef struct _GtkApp* GtkApp;
#include <gtk/gtk.h>

void create_window_main_widgets(GtkApp app);
void create_window_add_particle_normal_widgets(GtkApp app);
void create_window_add_force_normal_widgets(GtkApp app);
void create_window_edit_particle_normal_widgets(GtkApp app);
void create_window_edit_force_normal_widgets(GtkApp app);
void create_window_simulation_widgets(int i, GtkApp app);
void create_dialog_error_message(const gchar* message, GtkApp app);
