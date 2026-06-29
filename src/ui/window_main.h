#pragma once

#include <gtk/gtk.h>

typedef struct _Window_Main* Window_Main;
typedef struct _Cell_Renderer* Cell_Renderer;
typedef struct _Columns* Columns;
typedef struct _Buttons_Main* Buttons_Main;

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

struct _Window_Main
{
        GtkWidget* window;
        struct _Columns columns;
        struct _Cell_Renderer cell_renderer;
        struct _Buttons_Main buttons;
};

Window_Main window_main_new();
void window_main_free(Window_Main window_main);