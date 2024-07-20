#include "../include/gtk_include_all.h"

Window_Add_Force_Normal window_add_force_normal_new() // Função de criação da janela de adição de força
{
    Window_Add_Force_Normal window_add_force_normal = g_slice_new(struct _Window_Add_Force_Normal); // Aloca memória para a janela de adição de força
    // Inicializa os botões de adição de força
    window_add_force_normal->buttons = buttons_add_new();
    window_add_force_normal->spin_buttons = spin_buttons_add_force_normal_new();
    window_add_force_normal->window = NULL;
    return window_add_force_normal;
}

void window_add_force_normal_free(Window_Add_Force_Normal window_add_force_normal) // Função de liberação da janela de adição de força
{
    spin_buttons_add_force_normal_free(window_add_force_normal->spin_buttons);
    buttons_add_free(window_add_force_normal->buttons);
    g_slice_free(struct _Window_Add_Force_Normal, window_add_force_normal);
}