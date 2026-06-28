#include "../include/gtk_include_all.h"

Buttons_Add buttons_add_new()
{
    Buttons_Add buttons_add = g_slice_new(struct _Buttons_Add);

    buttons_add->add = NULL;
    buttons_add->cancel = NULL;
    return buttons_add;
}

void buttons_add_free(Buttons_Add buttons_add)
{
    g_slice_free(struct _Buttons_Add, buttons_add);
}