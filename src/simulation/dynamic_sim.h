#pragma once

#include "gtk_include_all.h"

gboolean on_draw_dynamic(GtkWidget* widget, cairo_t* cr, gpointer data);
gboolean on_timeout_dynamic(gpointer user_data);
void on_window_dynamic_destroy(GtkWidget* widget, gpointer data);
void on_dynamic_refresh_button_clicked(GtkButton* button, gpointer data);
void on_dynamic_start_button_clicked(GtkButton* button, gpointer data);
void on_dynamic_stop_button_clicked(GtkButton* button, gpointer data);
void run_simulation_dynamic(GtkApp app);
