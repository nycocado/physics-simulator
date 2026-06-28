#pragma once

#include <gtk/gtk.h>

typedef struct _Window_Main* Window_Main;
typedef struct _Cell_Renderer* Cell_Renderer;
typedef struct _Columns* Columns;
typedef struct _Buttons_Main* Buttons_Main;

struct _Window_Main
{
        GtkWidget* window;
        Columns columns;
        Cell_Renderer cell_renderer;
        Buttons_Main buttons;
};

struct _Cell_Renderer
{
        GtkCellRenderer* type;
        GtkCellRenderer* x;
        GtkCellRenderer* y;
        GtkCellRenderer* vx;
        GtkCellRenderer* vy;
        GtkCellRenderer* ax;
        GtkCellRenderer* ay;
        GtkCellRenderer* mass;
        GtkCellRenderer* check;
};

struct _Columns
{
        GtkTreeViewColumn* type;
        GtkTreeViewColumn* x;
        GtkTreeViewColumn* y;
        GtkTreeViewColumn* vx;
        GtkTreeViewColumn* vy;
        GtkTreeViewColumn* ax;
        GtkTreeViewColumn* ay;
        GtkTreeViewColumn* mass;
        GtkTreeViewColumn* check;
};

struct _Buttons_Main
{
        GtkWidget* add_particle;
        GtkWidget* add_force;
        GtkWidget* edit;
        GtkWidget* remove;
        GtkWidget* cinematic;
        GtkWidget* dynamic;
};

Window_Main window_main_new();
void window_main_free(Window_Main window_main);
Cell_Renderer cell_renderers_new();
void cell_renderers_free(Cell_Renderer cell_renderer);
Columns columns_new();
void columns_free(Columns columns);
Buttons_Main buttons_main_new();
void buttons_main_free(Buttons_Main buttons_main);