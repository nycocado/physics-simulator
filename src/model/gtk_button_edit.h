#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK

typedef struct _Buttons_Edit *Buttons_Edit; // Declaração do ponteiro dos botões de edição

struct _Buttons_Edit // Estrutura dos botões de edição
{
    GtkWidget *edit;
    GtkWidget *cancel;
};

Buttons_Edit buttons_edit_new();                   // Função de criação dos botões de edição
void buttons_edit_free(Buttons_Edit buttons_edit); // Função de liberação dos botões de edição