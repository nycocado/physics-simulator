#pragma once

gboolean on_draw_dynamic(GtkWidget *widget, cairo_t *cr);  // Função de desenho
gboolean on_timeout_dynamic(gpointer user_data);           // Função para atualizar a posição das partículas
void on_window_dynamic_destroy(GtkWidget *widget);         // Função de destruição da janela
void on_dynamic_refresh_button_clicked(GtkButton *button); // Função de reinício da simulação
void on_dynamic_start_button_clicked(GtkButton *button);   // Função de início da simulação
void on_dynamic_stop_button_clicked(GtkButton *button);    // Função de parada da simulação
void run_simulation_dynamic();                             // Função para rodar a simulação