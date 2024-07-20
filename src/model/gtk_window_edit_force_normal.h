#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK
// Inclui os objetos da aplicação GTK
#include "gtk_spin_buttons_add_force_normal.h"
#include "gtk_button_edit.h"

typedef struct _Window_Edit_Force_Normal *Window_Edit_Force_Normal; // Declaração do ponteiro da janela de edição de força

struct _Window_Edit_Force_Normal // Estrutura da janela de edição de força
{
    GtkWidget *window;
    Spin_Buttons_Add_Force_Normal spin_buttons;
    Buttons_Edit buttons;
};

Window_Edit_Force_Normal window_edit_force_normal_new();                               // Função de criação da janela de edição de força
void window_edit_force_normal_free(Window_Edit_Force_Normal window_edit_force_normal); // Função de liberação da janela de edição de força