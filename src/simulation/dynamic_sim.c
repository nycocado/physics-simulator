#include "dynamic_sim.h"
#include "app.h"
#include "collection.h"
#include "log.h"
#include "particles/particle.h"
#include "physics/dynamics.h"
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
    set_background_color(cr, 0.2, 0.2, 0.2);

    int x_center = width / 2;
    int y_center = height / 2;

    draw_axes(cr, x_center, y_center, app);

    draw_time(cr, app->variables->simulation.last_time, 10, 20);

    Particle_Dynamic_Collection particle_collection =
        app->variables->simulation.particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];

        double x = particle->position->x;
        double y = particle->position->y;
        double frx = particle->force_resultant->x;
        double fry = particle->force_resultant->y;

        double start_x = (double)x_center + x;
        double start_y = (double)y_center - y;

        double end_frx = start_x + frx;
        double end_fry = start_y - fry;

        draw_particle(cr, start_x, start_y, 5);

        double arrow_length = 10.0;
        double arrow_angle = G_PI / 6.0;

        cairo_set_source_rgb(cr, 0, 1, 0);
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
            {
                draw_title(cr, "f", end_frx + 5, end_fry);
            }
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

        double xi = particle->position_i->x;
        double yi = particle->position_i->y;
        double vxi = particle->velocity_i->x;
        double vyi = particle->velocity_i->y;
        double ax = particle->acceleration->x;
        double ay = particle->acceleration->y;

        particle->position->x = phyc_position(xi, vxi, ax, elapsed);
        particle->position->y = phyc_position(yi, vyi, ay, elapsed);
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

    Particle_Dynamic_Collection collection =
        app->variables->simulation.particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Dynamic particle = collection->particles[i];
        particle->position->x = particle->position_i->x;
        particle->position->y = particle->position_i->y;
        particle->acceleration->x = particle->acceleration_i->x;
        particle->acceleration->y = particle->acceleration_i->y;
    }
    gtk_widget_queue_draw(app->window_simulation->drawing_area);
}

static void forces_dynamic_apply(GtkApp app)
{
    Particle_Dynamic_Collection collection =
        app->variables->simulation.particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation.num_particles_use; i++)
    {
        Particle_Dynamic particle = collection->particles[i];
        GList* forces = particle->forces;

        particle->acceleration->x = particle->acceleration_i->x;
        particle->acceleration->y = particle->acceleration_i->y;
        particle->force_resultant->x = 0;
        particle->force_resultant->y = 0;

        for (GList* l = forces; l != NULL; l = l->next)
        {
            Vector force = l->data;
            particle->force_resultant->x += force->x;
            particle->force_resultant->y += force->y;
        }
        particle->force_resultant->y -=
            phyd_force_p(particle->mass, app->variables->simulation.gravity);
        particle->acceleration->x +=
            phyd_acceleration(particle->force_resultant->x, particle->mass);
        particle->acceleration->y +=
            phyd_acceleration(particle->force_resultant->y, particle->mass);
    }
}

void on_dynamic_start_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (app->variables->simulation.is_simulation_running)
        return;

    Variables_Simulation sim = &app->variables->simulation;
    simulation_read_controls(app);
    forces_dynamic_apply(app);

    if (sim->first_time || sim->gravity != sim->gravity_cache ||
        sim->time_step != sim->time_step_cache || sim->time != sim->time_cache)
    {
        save_simulation_dynamic_log(
            sim->particle_dynamic_collection,
            sim->time,
            sim->time_step,
            sim->gravity,
            app
        );
    }

    sim->first_time = FALSE;
    sim->gravity_cache = sim->gravity;
    sim->time_cache = sim->time;
    sim->time_step_cache = sim->time_step;

    simulation_start_timer(on_timeout_dynamic, app);
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
