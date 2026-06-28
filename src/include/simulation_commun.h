#pragma once

#include <gtk/gtk.h>

void get_window_size(GtkWidget* widget);
void draw_axes(cairo_t* cr, int x_center, int y_bottom);
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
void draw_particle(cairo_t* cr, float start_x, float start_y, float radius);
void draw_title(cairo_t* cr, const char* title, float x, float y);
void draw_time(cairo_t* cr, float time, float x, float y);
void simulation_window_destroy(void);