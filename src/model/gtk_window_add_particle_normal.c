#include "../include/gtk_include_all.h"

Window_Add_Particle_Normal window_add_particle_normal_new()
{
    Window_Add_Particle_Normal window_add_particle_normal =
        g_slice_new(struct _Window_Add_Particle_Normal);

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
    g_slice_free(
        struct _Window_Add_Particle_Normal, window_add_particle_normal
    );
}