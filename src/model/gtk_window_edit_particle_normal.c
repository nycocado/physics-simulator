#include "../include/gtk_include_all.h"

Window_Edit_Particle_Normal window_edit_particle_normal_new() // Função de criação da janela de edição de partícula
{
    Window_Edit_Particle_Normal window_edit_particle_normal = g_slice_new(struct _Window_Edit_Particle_Normal); // Aloca memória para a janela de edição de partícula
    // Inicializa os botões de edição de partícula
    window_edit_particle_normal->spin_buttons = spin_buttons_add_particle_normal_new();
    window_edit_particle_normal->buttons = buttons_edit_new();
    window_edit_particle_normal->window = NULL;
    return window_edit_particle_normal;
}

void window_edit_particle_normal_free(Window_Edit_Particle_Normal window_edit_particle_normal) // Função de liberação da janela de edição de partícula
{
    spin_buttons_add_particle_normal_free(window_edit_particle_normal->spin_buttons);
    buttons_edit_free(window_edit_particle_normal->buttons);
    g_slice_free(struct _Window_Edit_Particle_Normal, window_edit_particle_normal);
}