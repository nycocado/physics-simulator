#include "../include/gtk_include_all.h"

Window_Add_Particle_Normal window_add_particle_normal_new() // Função de criação da janela de adição de partícula
{
    Window_Add_Particle_Normal window_add_particle_normal = g_slice_new(struct _Window_Add_Particle_Normal); // Aloca memória para a janela de adição de partícula
    // Inicializa os botões de adição de partícula
    window_add_particle_normal->spin_buttons = spin_buttons_add_particle_normal_new();
    window_add_particle_normal->buttons = buttons_add_new();
    window_add_particle_normal->window = NULL;
    return window_add_particle_normal;
}

void window_add_particle_normal_free(Window_Add_Particle_Normal window_add_particle_normal) // Função de liberação da janela de adição de partícula
{
    spin_buttons_add_particle_normal_free(window_add_particle_normal->spin_buttons);
    buttons_add_free(window_add_particle_normal->buttons);
    g_slice_free(struct _Window_Add_Particle_Normal, window_add_particle_normal);
}