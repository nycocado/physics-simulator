#include "../include/gtk_include_all.h"

Window_Edit_Force_Normal window_edit_force_normal_new() // Função de criação da janela de edição de força
{
    Window_Edit_Force_Normal window_edit_force_normal = g_slice_new(struct _Window_Edit_Force_Normal); // Aloca memória para a janela de edição de força
    // Inicializa os botões de edição de força
    window_edit_force_normal->spin_buttons = spin_buttons_add_force_normal_new();
    window_edit_force_normal->buttons = buttons_edit_new();
    window_edit_force_normal->window = NULL;
    return window_edit_force_normal;
}

void window_edit_force_normal_free(Window_Edit_Force_Normal window_edit_force_normal) // Função de liberação da janela de edição de força
{
    spin_buttons_add_force_normal_free(window_edit_force_normal->spin_buttons);
    buttons_edit_free(window_edit_force_normal->buttons);
    g_slice_free(struct _Window_Edit_Force_Normal, window_edit_force_normal);
}