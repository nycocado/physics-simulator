#include "window_main.h"

Window_Main window_main_new()
{
    Window_Main window_main = g_new0(struct _Window_Main, 1);
    return window_main;
}

void window_main_free(Window_Main window_main) { g_free(window_main); }