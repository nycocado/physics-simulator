#pragma once

#include "../include/gtk_include_all.h"

gboolean on_draw_cinematic(GtkWidget *widget, cairo_t *cr); // Função de desenho
gboolean on_timeout_cinematic(gpointer user_data);          // Função para atualizar a posição das partículas
void on_window_cinematic_destroy(GtkWidget *widget);        // Função de destruição da janela
void on_refresh_button_clicked(GtkButton *button);          // Função de reinício da simulação
void on_start_button_clicked(GtkButton *button);            // Função de início da simulação
void on_stop_button_clicked(GtkButton *button);             // Função de parada da simulação
void run_simulation_cinematic();                            // Função para rodar a simulação