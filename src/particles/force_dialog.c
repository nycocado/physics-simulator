#include "gtk_include_all.h"

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

Window_Add_Force_Normal window_add_force_normal_new()
{
    Window_Add_Force_Normal window_add_force_normal =
        g_new(struct _Window_Add_Force_Normal, 1);

    window_add_force_normal->buttons = buttons_add_new();
    window_add_force_normal->spin_buttons = spin_buttons_add_force_normal_new();
    window_add_force_normal->window = NULL;
    return window_add_force_normal;
}

void window_add_force_normal_free(Window_Add_Force_Normal window_add_force_normal
)
{
    spin_buttons_add_force_normal_free(window_add_force_normal->spin_buttons);
    buttons_add_free(window_add_force_normal->buttons);
    g_free(window_add_force_normal);
}

Window_Edit_Force_Normal window_edit_force_normal_new()
{
    Window_Edit_Force_Normal window_edit_force_normal =
        g_new(struct _Window_Edit_Force_Normal, 1);

    window_edit_force_normal->spin_buttons =
        spin_buttons_add_force_normal_new();
    window_edit_force_normal->buttons = buttons_edit_new();
    window_edit_force_normal->window = NULL;
    return window_edit_force_normal;
}

void window_edit_force_normal_free(
    Window_Edit_Force_Normal window_edit_force_normal
)
{
    spin_buttons_add_force_normal_free(window_edit_force_normal->spin_buttons);
    buttons_edit_free(window_edit_force_normal->buttons);
    g_free(window_edit_force_normal);
}
