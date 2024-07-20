#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK

typedef struct _Buttons_Add *Buttons_Add; // Declaração do ponteiro dos botões de adição

struct _Buttons_Add // Estrutura dos botões de adição
{
    GtkWidget *add;
    GtkWidget *cancel;
};

Buttons_Add buttons_add_new();                  // Função de criação dos botões de adição
void buttons_add_free(Buttons_Add buttons_add); // Função de liberação dos botões de adição