#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK

typedef struct _Spin_Buttons_Add_Force_Normal *Spin_Buttons_Add_Force_Normal; // Declaração do ponteiro dos botões de adição

struct _Spin_Buttons_Add_Force_Normal // Estrutura dos botões de adição
{
    GtkWidget *fx;
    GtkWidget *fy;
};

Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal_new();                                    // Função de criação dos botões de adição
void spin_buttons_add_force_normal_free(Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal); // Função de liberação dos botões de adição