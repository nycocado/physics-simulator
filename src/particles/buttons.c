#include "gtk_include_all.h"

Buttons_Add buttons_add_new()
{
    Buttons_Add buttons_add = g_new(struct _Buttons_Add, 1);

    buttons_add->add = NULL;
    buttons_add->cancel = NULL;
    return buttons_add;
}

void buttons_add_free(Buttons_Add buttons_add) { g_free(buttons_add); }

Buttons_Edit buttons_edit_new()
{
    Buttons_Edit buttons_edit = g_new(struct _Buttons_Edit, 1);

    buttons_edit->edit = NULL;
    buttons_edit->cancel = NULL;
    return buttons_edit;
}

void buttons_edit_free(Buttons_Edit buttons_edit) { g_free(buttons_edit); }
