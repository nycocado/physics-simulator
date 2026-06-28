#include "../include/gtk_include_all.h"

gboolean on_draw_dynamic(GtkWidget* widget, cairo_t* cr)
{
    get_window_size(widget);
    set_background_color(cr, 0.2, 0.2, 0.2);

    int x_center = app->variables->window_size->width / 2;
    int y_center = app->variables->window_size->height / 2;

    draw_axes(cr, x_center, y_center);

    draw_time(cr, app->variables->simulation->last_time, 10, 20);

    Particle_Dynamic_Collection particle_collection =
        app->variables->simulation->particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];

        float x = particle->position->x;
        float y = particle->position->y;

        float frx = particle->force_resultant->x;
        float fry = particle->force_resultant->y;

        float start_x = x_center + x;
        float start_y = y_center - y;

        float end_frx = start_x + frx;
        float end_fry = start_y - fry;

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
    return FALSE;
}

gboolean on_timeout_dynamic(gpointer user_data)
{

    if (!GTK_IS_WIDGET(user_data))
    {
        if (app->variables->simulation->timer != NULL)
        {
            g_timer_stop(app->variables->simulation->timer);
        }
        return FALSE;
    }

    if (!app->variables->simulation->is_simulation_running)
    {
        return FALSE;
    }

    GtkWidget* drawing_area = app->window_simulation->drawing_area;
    app->variables->simulation->last_time =
        g_timer_elapsed(app->variables->simulation->timer, NULL);
    double elapsed_time = app->variables->simulation->last_time;
    float total_time = app->variables->simulation->time;

    Particle_Dynamic_Collection particle_collection =
        app->variables->simulation->particle_dynamic_collection;

    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];

        float xi = particle->position_i->x;
        float yi = particle->position_i->y;
        float vxi = particle->velocity_i->x;
        float vyi = particle->velocity_i->y;
        float ax = particle->acceleration->x;
        float ay = particle->acceleration->y;

        particle->position->x = phyc_position(xi, vxi, ax, elapsed_time);
        particle->position->y = phyc_position(yi, vyi, ay, elapsed_time);
    }

    if (elapsed_time >= total_time)
    {
        app->variables->simulation->is_simulation_running = FALSE;
        g_timer_stop(app->variables->simulation->timer);
        app->variables->simulation->last_time =
            app->variables->simulation->time;
    }

    gtk_widget_queue_draw(drawing_area);

    return TRUE;
}

void on_window_dynamic_destroy(GtkWidget* widget)
{
    simulation_window_destroy();
}

void on_dynamic_refresh_button_clicked(GtkButton* button)
{
    app->variables->simulation->is_simulation_running = FALSE;
    if (app->variables->simulation->timer != NULL)
    {
        g_timer_stop(app->variables->simulation->timer);
    }
    app->variables->simulation->last_time = 0;
    Particle_Dynamic_Collection particle_collection =
        app->variables->simulation->particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];

        particle->position->x = particle->position_i->x;
        particle->position->y = particle->position_i->y;
        particle->acceleration->x = particle->acceleration_i->x;
        particle->acceleration->y = particle->acceleration_i->y;
    }
    gtk_widget_queue_draw(app->window_simulation->drawing_area);
}

void forces_dynamic_apply()
{
    Particle_Dynamic_Collection particle_collection =
        app->variables->simulation->particle_dynamic_collection;
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Dynamic particle = particle_collection->particles[i];
        GList* forces = particle->forces;

        particle->acceleration->x = 0;
        particle->acceleration->y = 0;
        particle->force_resultant->x = 0;
        particle->force_resultant->y = 0;

        particle->acceleration->x += particle->acceleration_i->x;
        particle->acceleration->y += particle->acceleration_i->y;

        for (GList* l = forces; l != NULL; l = l->next)
        {
            Vector force = l->data;
            particle->force_resultant->x += force->x;
            particle->force_resultant->y += force->y;
        }
        particle->force_resultant->y -=
            phyd_force_p(particle->mass, app->variables->simulation->gravity);
        particle->acceleration->x +=
            phyd_acceleration(particle->force_resultant->x, particle->mass);
        particle->acceleration->y +=
            phyd_acceleration(particle->force_resultant->y, particle->mass);
    }
}

void on_dynamic_start_button_clicked(GtkButton* button)
{
    if (!app->variables->simulation->is_simulation_running)
    {

        app->variables->simulation->gravity = gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->gravity)
        );
        app->variables->simulation->time_step = gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->step)
        );
        app->variables->simulation->time = gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->time)
        );
        app->variables->simulation->frames = gtk_spin_button_get_value(
            GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->frames)
        );
        forces_dynamic_apply();

        if (app->variables->simulation->first_time ||
            app->variables->simulation->gravity !=
                app->variables->simulation->gravity_cache ||
            app->variables->simulation->time_step !=
                app->variables->simulation->time_step_cache ||
            app->variables->simulation->time !=
                app->variables->simulation->time_cache)
        {
            save_simulation_dynamic_log(
                app->variables->simulation->particle_dynamic_collection,
                app->variables->simulation->time,
                app->variables->simulation->time_step,
                app->variables->simulation->gravity
            );
        }

        app->variables->simulation->first_time = FALSE;
        app->variables->simulation->gravity_cache =
            app->variables->simulation->gravity;
        app->variables->simulation->time_cache =
            app->variables->simulation->time;
        app->variables->simulation->time_step_cache =
            app->variables->simulation->time_step;

        if (app->variables->simulation->timer == NULL)
        {
            app->variables->simulation->timer = g_timer_new();
        }

        if (app->variables->simulation->last_time == 0)
        {
            g_timer_start(app->variables->simulation->timer);
        }
        else
        {
            g_timer_continue(app->variables->simulation->timer);
        }

        app->variables->simulation->is_simulation_running = TRUE;

        int timeout_interval = (int)(1000 / app->variables->simulation->frames);
        g_timeout_add(
            timeout_interval,
            on_timeout_dynamic,
            app->window_simulation->drawing_area
        );
    }
}

void on_dynamic_stop_button_clicked(GtkButton* button)
{
    if (app->variables->simulation->is_simulation_running)
    {
        app->variables->simulation->is_simulation_running = FALSE;
        g_timer_stop(app->variables->simulation->timer);
    }
}

void run_simulation_dynamic()
{
    particle_dynamic_collection_start();
    create_window_simulation_widgets(DYNAMIC);
    gtk_widget_show_all(app->window_simulation->window);
}