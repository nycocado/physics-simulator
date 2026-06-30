#include "dynamic_sim.h"
#include "app.h"
#include "collection.h"
#include "log.h"
#include "particles/particle.h"
#include "physics/kinematics.h"
#include "simulation/simulation.h"
#include "ui/builder.h"
#include "ui/callbacks.h"
#include "variables.h"
#include <cairo.h>
#include <gtk/gtk.h>

void on_draw_dynamic(
    GtkDrawingArea* area,
    cairo_t* cr,
    int width,
    int height,
    gpointer data
)
{
    (void)area;
    GtkApp app = (GtkApp)data;
    app->variables->window_width = width;
    app->variables->window_height = height;
    set_background_color(cr, 0.15, 0.15, 0.18);

    Variables_Simulation sim = &app->variables->simulation;
    Particle_Dynamic_Collection particle_collection =
        sim->particle_dynamic_collection;
    int n = sim->num_particles_use;

    gboolean follow = gtk_check_button_get_active(
        GTK_CHECK_BUTTON(app->window_simulation->follow_check)
    );
    gboolean do_zoom = gtk_check_button_get_active(
        GTK_CHECK_BUTTON(app->window_simulation->zoom_check)
    );
    gboolean show_trail = gtk_check_button_get_active(
        GTK_CHECK_BUTTON(app->window_simulation->trail_check)
    );

    double target_cam_x = 0.0, target_cam_y = 0.0;
    double target_scale = 1.0;

    double bb_min_x = 1e18, bb_max_x = -1e18;
    double bb_min_y = 1e18, bb_max_y = -1e18;
    if (particle_collection)
    {
        for (int i = 0; i < n; i++)
        {
            double px = particle_collection->particles[i]->position.x;
            double py = particle_collection->particles[i]->position.y;
            if (px < bb_min_x)
                bb_min_x = px;
            if (px > bb_max_x)
                bb_max_x = px;
            if (py < bb_min_y)
                bb_min_y = py;
            if (py > bb_max_y)
                bb_max_y = py;
        }
    }

    if (follow && particle_collection && n > 0)
    {
        int follow_idx =
            (int)gtk_spin_button_get_value(
                GTK_SPIN_BUTTON(app->window_simulation->follow_spin)
            ) -
            1;
        if (follow_idx < 0)
            follow_idx = 0;
        if (follow_idx >= n)
            follow_idx = n - 1;
        target_cam_x = particle_collection->particles[follow_idx]->position.x;
        target_cam_y = particle_collection->particles[follow_idx]->position.y;
    }

    if (do_zoom && particle_collection && n > 0 && bb_min_x <= bb_max_x)
    {
        if (!follow)
        {
            target_cam_x = (bb_min_x + bb_max_x) / 2.0;
            target_cam_y = (bb_min_y + bb_max_y) / 2.0;
        }
        double range_x = bb_max_x - bb_min_x;
        double range_y = bb_max_y - bb_min_y;
        if (follow)
        {
            range_x = 2.0 * (fabs(bb_max_x - target_cam_x) >
                                     fabs(bb_min_x - target_cam_x)
                                 ? fabs(bb_max_x - target_cam_x)
                                 : fabs(bb_min_x - target_cam_x));
            range_y = 2.0 * (fabs(bb_max_y - target_cam_y) >
                                     fabs(bb_min_y - target_cam_y)
                                 ? fabs(bb_max_y - target_cam_y)
                                 : fabs(bb_min_y - target_cam_y));
        }
        double sx = (range_x > 0.001) ? (width * 0.80) / range_x : 500.0;
        double sy = (range_y > 0.001) ? (height * 0.80) / range_y : 500.0;
        target_scale = (sx < sy) ? sx : sy;
        if (target_scale < 0.01)
            target_scale = 0.01;
        if (target_scale > 1000.0)
            target_scale = 1000.0;
    }

    if (!sim->camera_initialized)
    {
        sim->cam_x = target_cam_x;
        sim->cam_y = target_cam_y;
        sim->scale = target_scale;
        sim->camera_initialized = TRUE;
    }
    else
    {
        double lerp = 0.08;
        sim->cam_x += (target_cam_x - sim->cam_x) * lerp;
        sim->cam_y += (target_cam_y - sim->cam_y) * lerp;
        sim->scale += (target_scale - sim->scale) * lerp;
    }

    double cam_x = sim->cam_x;
    double cam_y = sim->cam_y;
    double scale = sim->scale;

    double x_center = width / 2.0;
    double y_center = height / 2.0;

    cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 0.6);
    cairo_set_line_width(cr, 1.0);
    double axis_y = y_center + cam_y * scale;
    cairo_move_to(cr, 0, axis_y);
    cairo_line_to(cr, width, axis_y);
    cairo_stroke(cr);
    double axis_x = x_center - cam_x * scale;
    cairo_move_to(cr, axis_x, 0);
    cairo_line_to(cr, axis_x, height);
    cairo_stroke(cr);
    cairo_set_source_rgba(cr, 0.6, 0.6, 0.6, 0.8);
    cairo_move_to(cr, width - 16, axis_y - 6);
    cairo_show_text(cr, "X");
    cairo_move_to(cr, axis_x + 4, 14);
    cairo_show_text(cr, "Y");

    draw_axis_ticks(cr, width, height, x_center, y_center, cam_x, cam_y, scale);

    draw_time(cr, sim->last_time, 10, 20);

    if (!particle_collection)
        return;

    double arrow_length = 10.0;
    double arrow_angle = G_PI / 6.0;

    for (int i = 0; i < n; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];

        double px = (particle->position.x - cam_x) * scale;
        double py = (particle->position.y - cam_y) * scale;

        double start_x = x_center + px;
        double start_y = y_center - py;

        if (show_trail && particle->trail && particle->trail->len > 1)
        {
            guint trail_len = particle->trail->len;
            for (guint t = 1; t < trail_len; t++)
            {
                Vector* tp = &g_array_index(particle->trail, Vector, t);
                Vector* tp_prev =
                    &g_array_index(particle->trail, Vector, t - 1);
                double tx = x_center + (tp->x - cam_x) * scale;
                double ty = y_center - (tp->y - cam_y) * scale;
                double tx0 = x_center + (tp_prev->x - cam_x) * scale;
                double ty0 = y_center - (tp_prev->y - cam_y) * scale;
                double alpha = (double)t / trail_len * 0.6;
                cairo_set_source_rgba(cr, 1.0, 0.6, 0.2, alpha);
                cairo_set_line_width(cr, 1.5);
                cairo_move_to(cr, tx0, ty0);
                cairo_line_to(cr, tx, ty);
                cairo_stroke(cr);
            }
        }

        draw_particle(cr, start_x, start_y, 5);

        double frx = particle->force_resultant.x * scale;
        double fry = particle->force_resultant.y * scale;
        double end_frx = start_x + frx;
        double end_fry = start_y - fry;

        cairo_set_source_rgb(cr, 0, 0.85, 0.4);
        cairo_set_line_width(cr, 2);

        if (frx != 0 || fry != 0)
        {
            draw_arrow(
                cr,
                start_x,
                start_y,
                end_frx,
                end_fry,
                arrow_length,
                arrow_angle
            );
            if (frx != 0 && fry != 0)
                draw_title(cr, "f", end_frx + 5, end_fry);
        }
        if (frx != 0)
        {
            draw_arrow(
                cr,
                start_x,
                start_y,
                end_frx,
                start_y,
                arrow_length,
                arrow_angle
            );
            draw_title(cr, "fx", end_frx + 5, start_y);
        }
        if (fry != 0)
        {
            draw_arrow(
                cr,
                start_x,
                start_y,
                start_x,
                end_fry,
                arrow_length,
                arrow_angle
            );
            draw_title(cr, "fy", start_x + 5, end_fry - 5);
        }
    }
}

gboolean on_timeout_dynamic(gpointer user_data)
{
    GtkApp app = (GtkApp)user_data;
    if (app->window_simulation->window == NULL)
    {
        if (app->variables->simulation.timer != NULL)
            g_timer_stop(app->variables->simulation.timer);
        return FALSE;
    }

    if (!app->variables->simulation.is_simulation_running)
        return FALSE;

    Variables_Simulation sim = &app->variables->simulation;
    GtkWidget* drawing_area = app->window_simulation->drawing_area;

    sim->last_time = g_timer_elapsed(sim->timer, NULL);
    double elapsed = sim->last_time;
    double total_time = sim->time;

    Particle_Dynamic_Collection collection = sim->particle_dynamic_collection;
    for (int i = 0; i < sim->num_particles_use; i++)
    {
        Particle_Dynamic particle = collection->particles[i];

        double xi = particle->position_i.x;
        double yi = particle->position_i.y;
        double vxi = particle->velocity_i.x;
        double vyi = particle->velocity_i.y;
        double ax = particle->acceleration.x;
        double ay = particle->acceleration.y;

        particle->position.x = phyc_position(xi, vxi, ax, elapsed);
        particle->position.y = phyc_position(yi, vyi, ay, elapsed);

        if (particle->trail)
        {
            Vector pt = {particle->position.x, particle->position.y};
            g_array_append_val(particle->trail, pt);
            if (particle->trail->len > 500)
                g_array_remove_index(particle->trail, 0);
        }
    }

    if (elapsed >= total_time)
    {
        sim->is_simulation_running = FALSE;
        g_timer_stop(sim->timer);
        sim->last_time = sim->time;
        sim->timeout_id = 0;
        gtk_widget_queue_draw(drawing_area);
        return FALSE;
    }

    gtk_widget_queue_draw(drawing_area);
    return TRUE;
}

gboolean on_window_dynamic_destroy(GtkWindow* window, gpointer data)
{
    (void)window;
    GtkApp app = (GtkApp)data;
    simulation_window_destroy(app);
    return TRUE;
}

void on_dynamic_refresh_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    simulation_stop(app);
    app->variables->simulation.last_time = 0;
    app->variables->simulation.camera_initialized = FALSE;

    Particle_Dynamic_Collection collection =
        app->variables->simulation.particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Dynamic particle = collection->particles[i];
        particle->position.x = particle->position_i.x;
        particle->position.y = particle->position_i.y;
        particle->acceleration.x = particle->acceleration_i.x;
        particle->acceleration.y = particle->acceleration_i.y;
        if (particle->trail)
            g_array_set_size(particle->trail, 0);
    }
    gtk_widget_queue_draw(app->window_simulation->drawing_area);
}

void forces_dynamic_apply(GtkApp app)
{
    Particle_Dynamic_Collection collection =
        app->variables->simulation.particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Dynamic particle = collection->particles[i];
        GList* forces = particle->forces;

        particle->acceleration.x = particle->acceleration_i.x;
        particle->acceleration.y = particle->acceleration_i.y;
        particle->force_resultant.x = 0;
        particle->force_resultant.y = 0;

        for (GList* l = forces; l != NULL; l = l->next)
        {
            Vector* force = l->data;
            particle->force_resultant.x += force->x;
            particle->force_resultant.y += force->y;
        }
        particle->force_resultant.y -=
            ((particle->mass) * (app->variables->simulation.gravity));
        particle->acceleration.x +=
            ((particle->force_resultant.x) / (particle->mass));
        particle->acceleration.y +=
            ((particle->force_resultant.y) / (particle->mass));
    }
}

void on_dynamic_stop_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    simulation_stop(app);
}

void run_simulation_dynamic(GtkApp app)
{
    if (app->window_simulation->window != NULL)
        simulation_window_destroy(app);
    particle_dynamic_collection_start(app);
    create_window_simulation_widgets(SIMULATION_DYNAMIC, app);
    gtk_window_present(GTK_WINDOW(app->window_simulation->window));
}
