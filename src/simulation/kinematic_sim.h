#pragma once
typedef struct _GtkApp* GtkApp;
#include <cairo.h>
#include <gtk/gtk.h>

void on_draw_cinematic(
    GtkDrawingArea* area,
    cairo_t* cr,
    int width,
    int height,
    gpointer data
);
gboolean on_timeout_cinematic(gpointer user_data);
gboolean on_window_cinematic_destroy(GtkWindow* window, gpointer data);
void on_cinematic_refresh_button_clicked(GtkButton* button, gpointer data);
void on_cinematic_start_button_clicked(GtkButton* button, gpointer data);
void on_cinematic_stop_button_clicked(GtkButton* button, gpointer data);
void run_simulation_cinematic(GtkApp app);
