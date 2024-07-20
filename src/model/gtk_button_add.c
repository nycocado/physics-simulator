#include "../include/gtk_include_all.h"

Buttons_Add buttons_add_new() // Função de criação dos botões de adição
{
    Buttons_Add buttons_add = g_slice_new(struct _Buttons_Add); // Aloca a memória dos botões de adição
    // Inicializa os botões de adição
    buttons_add->add = NULL;
    buttons_add->cancel = NULL;
    return buttons_add;
}

void buttons_add_free(Buttons_Add buttons_add) // Função de liberação dos botões de adição
{
    g_slice_free(struct _Buttons_Add, buttons_add);
}