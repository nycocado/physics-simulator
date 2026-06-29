#pragma once

#include <gtk/gtk.h>

typedef struct _Window_Main* Window_Main;
typedef struct _Factories* Factories;

struct _Factories
{
        GtkListItemFactory* type;
        GtkListItemFactory* x;
        GtkListItemFactory* y;
        GtkListItemFactory* vx;
        GtkListItemFactory* vy;
        GtkListItemFactory* ax;
        GtkListItemFactory* ay;
        GtkListItemFactory* mass;
        GtkListItemFactory* check;
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
        struct _Factories factories;
        struct _Buttons_Main buttons;
};

Window_Main window_main_new();
void window_main_free(Window_Main window_main);