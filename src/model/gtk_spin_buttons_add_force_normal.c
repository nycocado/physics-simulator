#include "../include/gtk_include_all.h"

Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal_new()
{
    Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal =
        g_new(struct _Spin_Buttons_Add_Force_Normal, 1);

    spin_buttons_add_force_normal->fx = NULL;
    spin_buttons_add_force_normal->fy = NULL;
    return spin_buttons_add_force_normal;
}

void spin_buttons_add_force_normal_free(
    Spin_Buttons_Add_Force_Normal spin_buttons_add_force_normal
)
{
    g_free(spin_buttons_add_force_normal);
}