#include "../include/gtk_include_all.h"

Window_Main window_main_new()
{
    Window_Main window_main = g_slice_new(struct _Window_Main);

    window_main->buttons = buttons_main_new();
    window_main->cell_renderer = cell_renderers_new();
    window_main->columns = columns_new();
    window_main->window = NULL;
    return window_main;
}

void window_main_free(Window_Main window_main)
{
    columns_free(window_main->columns);
    buttons_main_free(window_main->buttons);
    cell_renderers_free(window_main->cell_renderer);
    g_slice_free(struct _Window_Main, window_main);
}

Cell_Renderer cell_renderers_new()
{
    Cell_Renderer cell_renderer = g_slice_new(struct _Cell_Renderer);

    cell_renderer->type = NULL;
    cell_renderer->x = NULL;
    cell_renderer->y = NULL;
    cell_renderer->vx = NULL;
    cell_renderer->vy = NULL;
    cell_renderer->ax = NULL;
    cell_renderer->ay = NULL;
    cell_renderer->mass = NULL;
    cell_renderer->check = NULL;
    return cell_renderer;
}

void cell_renderers_free(Cell_Renderer cell_renderer)
{
    g_slice_free(struct _Cell_Renderer, cell_renderer);
}

Columns columns_new()
{
    Columns columns = g_slice_new(struct _Columns);

    columns->type = NULL;
    columns->x = NULL;
    columns->y = NULL;
    columns->vx = NULL;
    columns->vy = NULL;
    columns->ax = NULL;
    columns->ay = NULL;
    columns->mass = NULL;
    columns->check = NULL;
    return columns;
}

void columns_free(Columns columns) { g_slice_free(struct _Columns, columns); }

Buttons_Main buttons_main_new()
{
    Buttons_Main buttons_main = g_slice_new(struct _Buttons_Main);

    buttons_main->add_particle = NULL;
    buttons_main->add_force = NULL;
    buttons_main->edit = NULL;
    buttons_main->remove = NULL;
    buttons_main->cinematic = NULL;
    buttons_main->dynamic = NULL;
    return buttons_main;
}

void buttons_main_free(Buttons_Main buttons_main)
{
    g_slice_free(struct _Buttons_Main, buttons_main);
}