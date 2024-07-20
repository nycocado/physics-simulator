#include "../include/gtk_include_all.h"

Buttons_Edit buttons_edit_new() // Função de criação dos botões de edição
{
    Buttons_Edit buttons_edit = g_slice_new(struct _Buttons_Edit); // Aloca a memória dos botões de edição
    // Inicializa os botões de edição
    buttons_edit->edit = NULL;
    buttons_edit->cancel = NULL;
    return buttons_edit;
}

void buttons_edit_free(Buttons_Edit buttons_edit) // Função de liberação dos botões de edição
{
    g_slice_free(struct _Buttons_Edit, buttons_edit);
}