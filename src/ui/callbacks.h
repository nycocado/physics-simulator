#pragma once

#include <gtk/gtk.h>

void on_window_destroy(GtkWidget* widget, gpointer data);
void on_check_toggled(GtkCheckButton* button, gpointer data);
void on_window_main_add_particle_button_clicked(
    GtkButton* button,
    gpointer data
);
void on_window_add_particle_normal_add_button_clicked(
    GtkWidget* widget,
    gpointer data
);
void on_window_edit_particle_normal_edit_button_clicked(
    GtkWidget* widget,
    gpointer data
);
void on_window_main_add_force_button_clicked(GtkButton* button, gpointer data);
void on_window_add_force_normal_add_button_clicked(
    GtkWidget* widget,
    gpointer data
);
void on_window_edit_force_normal_edit_button_clicked(
    GtkWidget* widget,
    gpointer data
);
void on_window_main_edit_button_clicked(GtkWidget* widget, gpointer data);
void on_window_main_remove_button_clicked(GtkWidget* widget, gpointer data);
void on_menu_projects_open_activate(
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
);
void on_menu_projects_save_activate(
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
);
void on_menu_projects_new_activate(
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
);
void on_menu_projects_close_activate(
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
);
void on_window_main_cinematic_button_clicked(GtkButton* button, gpointer data);
void on_window_main_dynamic_button_clicked(GtkButton* button, gpointer data);
