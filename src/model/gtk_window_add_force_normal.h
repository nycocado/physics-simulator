#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK
// Inclui os objetos da aplicação GTK
#include "gtk_button_add.h"
#include "gtk_spin_buttons_add_force_normal.h"

typedef struct _Window_Add_Force_Normal *Window_Add_Force_Normal; // Declaração do ponteiro da janela de adição de força

struct _Window_Add_Force_Normal // Estrutura da janela de adição de força
{
    GtkWidget *window;
    Spin_Buttons_Add_Force_Normal spin_buttons;
    Buttons_Add buttons;
};

Window_Add_Force_Normal window_add_force_normal_new();                              // Função de criação da janela de adição de força
void window_add_force_normal_free(Window_Add_Force_Normal window_add_force_normal); // Função de liberação da janela de adição de força