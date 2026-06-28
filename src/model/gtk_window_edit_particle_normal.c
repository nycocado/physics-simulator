#include "../include/gtk_include_all.h"

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