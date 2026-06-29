#include "gtk_include_all.h"

void draw_axes(cairo_t* cr, int x_center, int y_bottom, GtkApp app)
{
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_set_line_width(cr, 2);

    cairo_move_to(cr, 0, y_bottom);
    cairo_line_to(cr, app->variables->window_width, y_bottom);
    cairo_stroke(cr);

    cairo_move_to(cr, x_center, 0);
    cairo_line_to(cr, x_center, app->variables->window_height);
    cairo_stroke(cr);
}

void draw_arrow(
    cairo_t* cr,
    double start_x,
    double start_y,
    double end_x,
    double end_y,
    double arrow_length,
    double arrow_angle
)
{
    double angle = phyc_angle(end_x - start_x, end_y - start_y);

    double x1 = end_x - phyc_decompose_x(arrow_length, angle - arrow_angle);
    double y1 = end_y - phyc_decompose_y(arrow_length, angle - arrow_angle);
    double x2 = end_x - phyc_decompose_x(arrow_length, angle + arrow_angle);
    double y2 = end_y - phyc_decompose_y(arrow_length, angle + arrow_angle);

    cairo_move_to(cr, start_x, start_y);
    cairo_line_to(cr, end_x, end_y);
    cairo_stroke(cr);

    cairo_move_to(cr, end_x, end_y);
    cairo_line_to(cr, x1, y1);
    cairo_stroke(cr);

    cairo_move_to(cr, end_x, end_y);
    cairo_line_to(cr, x2, y2);
    cairo_stroke(cr);
}

void set_background_color(cairo_t* cr, double r, double g, double b)
{
    cairo_set_source_rgb(cr, r, g, b);
    cairo_paint(cr);
}

void draw_particle(cairo_t* cr, double start_x, double start_y, double radius)
{
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_arc(cr, start_x, start_y, radius, 0, 2 * G_PI);
    cairo_fill(cr);
}

void draw_title(cairo_t* cr, const char* text, double x, double y)
{
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, x, y);
    cairo_show_text(cr, text);
}

void draw_time(cairo_t* cr, double time, double x, double y)
{
    char* str = g_strdup_printf("Tempo: %.2f s", time);
    draw_title(cr, str, x, y);
    g_free(str);
}

void simulation_window_destroy(GtkApp app)
{
    if (app->variables->simulation.timeout_id != 0)
    {
        g_source_remove(app->variables->simulation.timeout_id);
        app->variables->simulation.timeout_id = 0;
    }
    variables_simulation_wipe(&app->variables->simulation);
    gtk_window_destroy(GTK_WINDOW(app->window_simulation->window));
    app->window_simulation->window = NULL;
}

void simulation_read_controls(GtkApp app)
{
    Variables_Simulation sim = &app->variables->simulation;
    sim->gravity = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.gravity)
    );
    sim->time_step = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.step)
    );
    sim->time = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.time)
    );
    sim->frames = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.frames)
    );
}

void simulation_stop(GtkApp app)
{
    Variables_Simulation sim = &app->variables->simulation;
    if (!sim->is_simulation_running)
        return;
    sim->is_simulation_running = FALSE;
    g_timer_stop(sim->timer);
    if (sim->timeout_id != 0)
    {
        g_source_remove(sim->timeout_id);
        sim->timeout_id = 0;
    }
}

void simulation_start_timer(GSourceFunc timeout_fn, GtkApp app)
{
    Variables_Simulation sim = &app->variables->simulation;
    if (sim->timer == NULL)
        sim->timer = g_timer_new();
    if (sim->last_time == 0)
        g_timer_start(sim->timer);
    else
        g_timer_continue(sim->timer);
    sim->is_simulation_running = TRUE;
    int interval = (int)(1000 / sim->frames);
    sim->timeout_id = g_timeout_add(interval, timeout_fn, app);
}
