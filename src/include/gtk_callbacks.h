#pragma once

#include "gtk_include_all.h"

void on_window_destroy(GtkWidget* widget);
void on_renderer_check_toggled(
    GtkCellRendererToggle* renderer,
    gchar* path_str
);
void on_window_main_add_particle_button_clicked(GtkButton* button);
void on_window_add_particle_normal_add_button_clicked(GtkWidget* widget);
void on_window_edit_particle_normal_edit_button_clicked();
void on_window_main_add_force_button_clicked(GtkButton* button);
void on_window_add_force_normal_add_button_clicked(GtkWidget* widget);
void on_window_edit_force_normal_edit_button_clicked();
void on_window_main_edit_button_clicked(GtkWidget* widget);
void on_window_main_remove_button_clicked(GtkWidget* widget);
void on_selection_change_abrir(GtkFileChooser* chooser);
void on_menu_projetos_abrir_activate();
void on_menu_projetos_salvar_activate();
void on_menu_projetos_novo_activate();
void on_menu_projetos_fechar_activate();
void on_window_main_cinematic_button_clicked(GtkButton* button);
void on_window_main_dynamic_button_clicked(GtkButton* button);