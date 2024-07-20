#include "../include/gtk_include_all.h"

Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal_new() // Função de criação dos botões de adição
{
    Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal = g_slice_new(struct _Spin_Buttons_Add_Force_Normal); // Aloca a memória dos botões de adição
    // Inicializa os botões de adição
    spin_buttons_add_force_normal->fx = NULL;
    spin_buttons_add_force_normal->fy = NULL;
    return spin_buttons_add_force_normal;
}

void spin_buttons_add_force_normal_free(Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal) // Função de liberação dos botões de adição
{
    g_slice_free(struct _Spin_Buttons_Add_Force_Normal, spin_buttons_add_force_normal);
}