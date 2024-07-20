#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK
// Inclui os objetos da aplicação GTK
#include "gtk_button_edit.h"
#include "gtk_spin_buttons_add_particle_normal.h"

typedef struct _Window_Edit_Particle_Normal *Window_Edit_Particle_Normal; // Declaração do ponteiro da janela de edição de partícula

struct _Window_Edit_Particle_Normal // Estrutura da janela de edição de partícula
{
    GtkWidget *window;
    Spin_Buttons_Add_Particle_Normal spin_buttons;
    Buttons_Edit buttons;
};

Window_Edit_Particle_Normal window_edit_particle_normal_new();                                  // Função de criação da janela de edição de partícula
void window_edit_particle_normal_free(Window_Edit_Particle_Normal window_edit_particle_normal); // Função de liberação da janela de edição de partícula