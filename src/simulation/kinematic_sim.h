#pragma once

#include "gtk_include_all.h"

gboolean on_draw_cinematic(GtkWidget* widget, cairo_t* cr, gpointer data);
gboolean on_timeout_cinematic(gpointer user_data);
void on_window_cinematic_destroy(GtkWidget* widget, gpointer data);
void on_cinematic_refresh_button_clicked(GtkButton* button, gpointer data);
void on_cinematic_start_button_clicked(GtkButton* button, gpointer data);
void on_cinematic_stop_button_clicked(GtkButton* button, gpointer data);
void run_simulation_cinematic(GtkApp app);
