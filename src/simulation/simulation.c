#include "simulation.h"
#include "app.h"
#include "log.h"
#include "physics/kinematics.h"
#include "simulation/dynamic_sim.h"
#include "simulation/kinematic_sim.h"
#include "ui/callbacks.h"
#include "variables.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>

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

/* Return a "nice" tick step for the given raw spacing */
static double nice_step(double raw)
{
    if (raw <= 0) return 1.0;
    double magnitude = pow(10.0, floor(log10(raw)));
    double n = raw / magnitude;
    double nice = (n < 1.5) ? 1.0 : (n < 3.5) ? 2.0 : (n < 7.5) ? 5.0 : 10.0;
    return nice * magnitude;
}

void draw_axis_ticks(
    cairo_t* cr,
    int width,
    int height,
    double x_center,
    double y_center,
    double cam_x,
    double cam_y,
    double scale
)
{
    /* Target ~70 px between ticks */
    double step = nice_step(70.0 / (scale > 0 ? scale : 1.0));

    const double TICK_LEN  = 5.0;
    const double LABEL_PAD = 4.0;

    cairo_set_font_size(cr, 10.0);

    /* ---- X axis ticks (horizontal) ---- */
    /* Visible physics-X range */
    double x_min = (-x_center) / scale + cam_x;
    double x_max = (width - x_center) / scale + cam_x;

    double first_x = ceil(x_min / step) * step;
    for (double xv = first_x; xv <= x_max + step * 0.5; xv += step)
    {
        double cx = x_center + (xv - cam_x) * scale;
        if (cx < 0 || cx > width) continue;

        /* Axis Y position in canvas */
        double axis_y = y_center + cam_y * scale;
        if (axis_y < 0) axis_y = 0;
        if (axis_y > height) axis_y = height - 1;

        /* Tick mark */
        cairo_set_source_rgba(cr, 0.6, 0.6, 0.6, 0.9);
        cairo_set_line_width(cr, 1.0);
        cairo_move_to(cr, cx, axis_y - TICK_LEN);
        cairo_line_to(cr, cx, axis_y + TICK_LEN);
        cairo_stroke(cr);

        /* Label — skip very small values near origin */
        if (fabs(xv) < step * 0.01) continue;
        char buf[32];
        if (fabs(xv) >= 100.0)
            g_snprintf(buf, sizeof(buf), "%.0f", xv);
        else if (fabs(xv) >= 10.0)
            g_snprintf(buf, sizeof(buf), "%.1f", xv);
        else
            g_snprintf(buf, sizeof(buf), "%.2f", xv);

        cairo_set_source_rgba(cr, 0.75, 0.75, 0.75, 0.9);
        double label_y = axis_y + TICK_LEN + LABEL_PAD + 10.0;
        if (label_y > height - 2) label_y = axis_y - TICK_LEN - LABEL_PAD;
        cairo_move_to(cr, cx - 12, label_y);
        cairo_show_text(cr, buf);
    }

    /* ---- Y axis ticks (vertical) ---- */
    /* Visible physics-Y range (canvas Y is inverted) */
    double y_min = -(height - y_center) / scale + cam_y;
    double y_max = y_center / scale + cam_y;

    double first_y = ceil(y_min / step) * step;
    for (double yv = first_y; yv <= y_max + step * 0.5; yv += step)
    {
        double cy = y_center - (yv - cam_y) * scale;
        if (cy < 0 || cy > height) continue;

        double axis_x = x_center - cam_x * scale;
        if (axis_x < 0) axis_x = 0;
        if (axis_x > width) axis_x = width - 1;

        cairo_set_source_rgba(cr, 0.6, 0.6, 0.6, 0.9);
        cairo_set_line_width(cr, 1.0);
        cairo_move_to(cr, axis_x - TICK_LEN, cy);
        cairo_line_to(cr, axis_x + TICK_LEN, cy);
        cairo_stroke(cr);

        if (fabs(yv) < step * 0.01) continue;
        char buf[32];
        if (fabs(yv) >= 100.0)
            g_snprintf(buf, sizeof(buf), "%.0f", yv);
        else if (fabs(yv) >= 10.0)
            g_snprintf(buf, sizeof(buf), "%.1f", yv);
        else
            g_snprintf(buf, sizeof(buf), "%.2f", yv);

        cairo_set_source_rgba(cr, 0.75, 0.75, 0.75, 0.9);
        double label_x = axis_x + TICK_LEN + LABEL_PAD;
        if (label_x > width - 40) label_x = axis_x - TICK_LEN - LABEL_PAD - 35;
        cairo_move_to(cr, label_x, cy + 4);
        cairo_show_text(cr, buf);
    }
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
    double angle = atan2(end_y - start_y, end_x - start_x);

    double x1 = end_x - ((arrow_length)*cos(angle - arrow_angle));
    double y1 = end_y - ((arrow_length)*sin(angle - arrow_angle));
    double x2 = end_x - ((arrow_length)*cos(angle + arrow_angle));
    double y2 = end_y - ((arrow_length)*sin(angle + arrow_angle));

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

void on_simulation_start_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    Variables_Simulation sim = &app->variables->simulation;

    if (sim->is_simulation_running)
        return;

    simulation_read_controls(app);

    if (sim->type == SIMULATION_DYNAMIC)
    {
        forces_dynamic_apply(app);
    }

    if (sim->first_time || sim->gravity != sim->gravity_cache ||
        sim->time_step != sim->time_step_cache || sim->time != sim->time_cache)
    {
        if (sim->type == SIMULATION_CINEMATIC)
        {
            save_simulation_cinematic_log(
                sim->particle_cinematic_collection,
                sim->time,
                sim->time_step,
                sim->gravity,
                app
            );
        }
        else if (sim->type == SIMULATION_DYNAMIC)
        {
            save_simulation_dynamic_log(
                sim->particle_dynamic_collection,
                sim->time,
                sim->time_step,
                sim->gravity,
                app
            );
        }
    }

    sim->first_time = FALSE;
    sim->gravity_cache = sim->gravity;
    sim->time_cache = sim->time;
    sim->time_step_cache = sim->time_step;

    if (sim->type == SIMULATION_CINEMATIC)
    {
        simulation_start_timer(on_timeout_cinematic, app);
    }
    else if (sim->type == SIMULATION_DYNAMIC)
    {
        simulation_start_timer(on_timeout_dynamic, app);
    }
}
