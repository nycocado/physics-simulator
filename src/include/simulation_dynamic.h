#pragma once

gboolean on_draw_dynamic(GtkWidget* widget, cairo_t* cr);
gboolean on_timeout_dynamic(gpointer user_data);
void on_window_dynamic_destroy(GtkWidget* widget);
void on_dynamic_refresh_button_clicked(GtkButton* button);
void on_dynamic_start_button_clicked(GtkButton* button);
void on_dynamic_stop_button_clicked(GtkButton* button);
void run_simulation_dynamic();