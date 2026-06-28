#include "../include/gtk_include_all.h"

Buttons_Edit buttons_edit_new()
{
    Buttons_Edit buttons_edit = g_new(struct _Buttons_Edit, 1);

    buttons_edit->edit = NULL;
    buttons_edit->cancel = NULL;
    return buttons_edit;
}

void buttons_edit_free(Buttons_Edit buttons_edit) { g_free(buttons_edit); }