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

Window_Add_Particle_Normal window_add_particle_normal_new()
{
    Window_Add_Particle_Normal window_add_particle_normal =
        g_new(struct _Window_Add_Particle_Normal, 1);

    window_add_particle_normal->spin_buttons =
        spin_buttons_add_particle_normal_new();
    window_add_particle_normal->buttons = buttons_add_new();
    window_add_particle_normal->window = NULL;
    return window_add_particle_normal;
}

void window_add_particle_normal_free(
    Window_Add_Particle_Normal window_add_particle_normal
)
{
    spin_buttons_add_particle_normal_free(
        window_add_particle_normal->spin_buttons
    );
    buttons_add_free(window_add_particle_normal->buttons);
    g_free(window_add_particle_normal);
}

Window_Edit_Particle_Normal window_edit_particle_normal_new()
{
    Window_Edit_Particle_Normal window_edit_particle_normal =
        g_new(struct _Window_Edit_Particle_Normal, 1);

    window_edit_particle_normal->spin_buttons =
        spin_buttons_add_particle_normal_new();
    window_edit_particle_normal->buttons = buttons_edit_new();
    window_edit_particle_normal->window = NULL;
    return window_edit_particle_normal;
}

void window_edit_particle_normal_free(
    Window_Edit_Particle_Normal window_edit_particle_normal
)
{
    spin_buttons_add_particle_normal_free(
        window_edit_particle_normal->spin_buttons
    );
    buttons_edit_free(window_edit_particle_normal->buttons);
    g_free(window_edit_particle_normal);
}
