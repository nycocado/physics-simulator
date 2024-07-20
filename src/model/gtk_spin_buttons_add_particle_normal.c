#include "../include/gtk_include_all.h"

Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal_new() // Função de criação dos botões de adição
{
    Spin_Buttons_Add_Particle_Normal spin_buttons_add_normal = g_slice_new(struct _Spin_Buttons_Add_Particle_Normal); // Aloca a memória dos botões de adição
    // Inicializa os botões de adição
    spin_buttons_add_normal->x = NULL;
    spin_buttons_add_normal->y = NULL;
    spin_buttons_add_normal->vx = NULL;
    spin_buttons_add_normal->vy = NULL;
    spin_buttons_add_normal->ax = NULL;
    spin_buttons_add_normal->ay = NULL;
    spin_buttons_add_normal->mass = NULL;
    return spin_buttons_add_normal;
}

void spin_buttons_add_particle_normal_free(Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal) // Função de liberação dos botões de adição
{
    g_slice_free(struct _Spin_Buttons_Add_Particle_Normal, spin_buttons_add_particle_normal);
}