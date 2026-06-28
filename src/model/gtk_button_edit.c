#include "../include/gtk_include_all.h"

Buttons_Edit buttons_edit_new()
{
    Buttons_Edit buttons_edit = g_slice_new(struct _Buttons_Edit);

    buttons_edit->edit = NULL;
    buttons_edit->cancel = NULL;
    return buttons_edit;
}

void buttons_edit_free(Buttons_Edit buttons_edit)
{
    g_slice_free(struct _Buttons_Edit, buttons_edit);
}