#pragma once

#include "gtk_include_all.h"

void create_window_main_widgets();                      // Cria os widgets da janela principal
void create_window_add_particle_normal_widgets();       // Cria os widgets da janela de adição de partícula
void create_window_add_force_normal_widgets();          // Cria os widgets da janela de adição de força
void create_window_edit_particle_normal_widgets();      // Cria os widgets da janela de edição de partícula
void create_window_edit_force_normal_widgets();         // Cria os widgets da janela de edição de força
void create_window_simulation_widgets(int i);           // Cria os widgets da janela de simulação
void create_dialog_error_message(const gchar *message); // Cria uma janela de erro