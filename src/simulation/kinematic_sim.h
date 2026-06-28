#pragma once

#include "gtk_include_all.h"

gboolean on_draw_cinematic(GtkWidget* widget, cairo_t* cr);
gboolean on_timeout_cinematic(gpointer user_data);
void on_window_cinematic_destroy(GtkWidget* widget);
void on_refresh_button_clicked(GtkButton* button);
void on_start_button_clicked(GtkButton* button);
void on_stop_button_clicked(GtkButton* button);
void run_simulation_cinematic();