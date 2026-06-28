#include "../include/gtk_include_all.h"

Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal_new()
{
    Spin_Buttons_Add_Particle_Normal spin_buttons_add_normal =
        g_new(struct _Spin_Buttons_Add_Particle_Normal, 1);

    spin_buttons_add_normal->x = NULL;
    spin_buttons_add_normal->y = NULL;
    spin_buttons_add_normal->vx = NULL;
    spin_buttons_add_normal->vy = NULL;
    spin_buttons_add_normal->ax = NULL;
    spin_buttons_add_normal->ay = NULL;
    spin_buttons_add_normal->mass = NULL;
    return spin_buttons_add_normal;
}

void spin_buttons_add_particle_normal_free(
    Spin_Buttons_Add_Particle_Normal spin_buttons_add_particle_normal
)
{
    g_free(spin_buttons_add_particle_normal);
}