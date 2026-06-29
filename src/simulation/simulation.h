#pragma once

#include <cairo.h>
#include <gtk/gtk.h>

typedef struct _GtkApp* GtkApp;

typedef enum
{
    SIMULATION_CINEMATIC = 1,
    SIMULATION_DYNAMIC = 2,
} SimulationMode;

void draw_axes(cairo_t* cr, int x_center, int y_bottom, GtkApp app);
void draw_arrow(
    cairo_t* cr,
    double start_x,
    double start_y,
    double end_x,
    double end_y,
    double arrow_length,
    double arrow_angle
);
void set_background_color(cairo_t* cr, double r, double g, double b);
void draw_particle(cairo_t* cr, double start_x, double start_y, double radius);
void draw_title(cairo_t* cr, const char* title, double x, double y);
void draw_time(cairo_t* cr, double time, double x, double y);
void simulation_window_destroy(GtkApp app);
void simulation_read_controls(GtkApp app);
void simulation_stop(GtkApp app);
void simulation_start_timer(GSourceFunc timeout_fn, GtkApp app);
