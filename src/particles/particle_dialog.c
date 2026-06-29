#include "gtk_include_all.h"


Window_Add_Particle_Normal window_add_particle_normal_new()
{
    Window_Add_Particle_Normal window_add_particle_normal =
        g_new0(struct _Window_Add_Particle_Normal, 1);
    return window_add_particle_normal;
}

void window_add_particle_normal_free(
    Window_Add_Particle_Normal window_add_particle_normal
)
{
    g_free(window_add_particle_normal);
}

Window_Edit_Particle_Normal window_edit_particle_normal_new()
{
    Window_Edit_Particle_Normal window_edit_particle_normal =
        g_new0(struct _Window_Edit_Particle_Normal, 1);
    return window_edit_particle_normal;
}

void window_edit_particle_normal_free(
    Window_Edit_Particle_Normal window_edit_particle_normal
)
{
    g_free(window_edit_particle_normal);
}
