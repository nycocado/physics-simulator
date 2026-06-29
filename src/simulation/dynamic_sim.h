#pragma once
typedef struct _GtkApp* GtkApp;
#include <cairo.h>
#include <gtk/gtk.h>

void on_draw_dynamic(
    GtkDrawingArea* area,
    cairo_t* cr,
    int width,
    int height,
    gpointer data
);
gboolean on_timeout_dynamic(gpointer user_data);
gboolean on_window_dynamic_destroy(GtkWindow* window, gpointer data);
void on_dynamic_refresh_button_clicked(GtkButton* button, gpointer data);

void on_dynamic_stop_button_clicked(GtkButton* button, gpointer data);
void run_simulation_dynamic(GtkApp app);
void forces_dynamic_apply(GtkApp app);
