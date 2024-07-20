#pragma once

#include "gtk_include_all.h"

void on_window_destroy(GtkWidget *widget);                                        // Função chamada quando a janela é fechada
void on_renderer_check_toggled(GtkCellRendererToggle *renderer, gchar *path_str); // Função chamada quando o botão de seleção de uma linha é clicado
void on_window_main_add_particle_button_clicked(GtkButton *button);               // Função chamada quando o botão de adicionar partícula é clicado
void on_window_add_particle_normal_add_button_clicked(GtkWidget *widget);         // Função chamada quando o botão de adicionar partícula é clicado
void on_window_edit_particle_normal_edit_button_clicked();                        // Função chamada quando o botão de editar partícula é clicado
void on_window_main_add_force_button_clicked(GtkButton *button);                  // Função chamada quando o botão de adicionar força é clicado
void on_window_add_force_normal_add_button_clicked(GtkWidget *widget);            // Função chamada quando o botão de adicionar força é clicado
void on_window_edit_force_normal_edit_button_clicked();                           // Função chamada quando o botão de editar força é clicado
void on_window_main_edit_button_clicked(GtkWidget *widget);                       // Função chamada quando o botão de editar é clicado
void on_window_main_remove_button_clicked(GtkWidget *widget);                     // Função chamada quando o botão de remover é clicado
void on_selection_change_abrir(GtkFileChooser *chooser);                          // Função chamada quando o arquivo é selecionado
void on_menu_projetos_abrir_activate();                                           // Função chamada quando o menu de abrir projeto é clicado
void on_menu_projetos_salvar_activate();                                          // Função chamada quando o menu de salvar projeto é clicado
void on_menu_projetos_novo_activate();                                            // Função chamada quando o menu de novo projeto é clicado
void on_menu_projetos_fechar_activate();                                          // Função chamada quando o menu de fechar projeto é clicado
void on_window_main_cinematic_button_clicked(GtkButton *button);                  // Função chamada quando o botão de cinemática é clicado
void on_window_main_dynamic_button_clicked(GtkButton *button);                    // Função chamada quando o botão de dinâmica é clicado