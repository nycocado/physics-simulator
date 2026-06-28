#include "../include/gtk_include_all.h"

gboolean on_draw_cinematic(GtkWidget* widget, cairo_t* cr)
{
    get_window_size(widget);
    set_background_color(cr, 0.2, 0.2, 0.2);

    int x_center = app->variables->window_size->width / 2;
    int y_center = app->variables->window_size->height / 2;

    draw_axes(cr, x_center, y_center);

    draw_time(cr, app->variables->simulation->last_time, 10, 20);

    Particle_Cinematic_Collection particle_collection =
        app->variables->simulation->particle_cinematic_collection;
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Cinematic particle = particle_collection->particles[i];

        float x = particle->position->x;
        float y = particle->position->y;
        float vx = particle->velocity->x;
        float vy = particle->velocity->y;

        float start_x = x_center + x;
        float start_y = y_center - y;

        float end_vx = start_x + vx;
        float end_vy = start_y - vy;

        draw_particle(cr, start_x, start_y, 5);

        double arrow_length = 10.0;
        double arrow_angle = G_PI / 6.0;

        cairo_set_source_rgb(cr, 0, 1, 0);
        cairo_set_line_width(cr, 2);

        if (vx != 0 || vy != 0)
        {
            draw_arrow(
                cr, start_x, start_y, end_vx, end_vy, arrow_length, arrow_angle
            );
            if (vx != 0 && vy != 0)
            {
                draw_title(cr, "v", end_vx + 5, end_vy);
            }
        }

        if (vx != 0)
        {
            draw_arrow(
                cr, start_x, start_y, end_vx, start_y, arrow_length, arrow_angle
            );
            draw_title(cr, "vx", end_vx + 5, start_y);
        }

        if (vy != 0)
        {
            draw_arrow(
                cr, start_x, start_y, start_x, end_vy, arrow_length, arrow_angle
            );
            draw_title(cr, "vy", start_x + 5, end_vy - 5);
        }
    }
    return FALSE;
}

gboolean on_timeout_cinematic(gpointer user_data)
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

    Particle_Cinematic_Collection particle_collection =
        app->variables->simulation->particle_cinematic_collection;

    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Cinematic particle = particle_collection->particles[i];

        float xi = particle->position_i->x;
        float yi = particle->position_i->y;
        float vxi = particle->velocity_i->x;
        float vyi = particle->velocity_i->y;
        float ax = particle->acceleration->x;
        float ay = particle->acceleration->y;
        float g = app->variables->simulation->gravity;

        particle->velocity->x = phyc_velocity(vxi, ax, elapsed_time);
        particle->velocity->y = phyc_velocity(vyi, ay - g, elapsed_time);

        particle->position->x = phyc_position(xi, vxi, ax, elapsed_time);
        particle->position->y = phyc_position(yi, vyi, ay - g, elapsed_time);
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

void on_window_cinematic_destroy(GtkWidget* widget)
{
    simulation_window_destroy();
}

void on_cinematic_refresh_button_clicked(GtkButton* button)
{
    app->variables->simulation->is_simulation_running = FALSE;
    if (app->variables->simulation->timer != NULL)
    {
        g_timer_stop(app->variables->simulation->timer);
    }
    app->variables->simulation->last_time = 0;
    Particle_Cinematic_Collection particle_collection =
        app->variables->simulation->particle_cinematic_collection;
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)
    {
        Particle_Cinematic particle = particle_collection->particles[i];

        particle->position->x = particle->position_i->x;
        particle->position->y = particle->position_i->y;
        particle->velocity->x = particle->velocity_i->x;
        particle->velocity->y = particle->velocity_i->y;
    }
    gtk_widget_queue_draw(app->window_simulation->drawing_area);
}

void on_cinematic_start_button_clicked(GtkButton* button)
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

        if (app->variables->simulation->first_time ||
            app->variables->simulation->gravity !=
                app->variables->simulation->gravity_cache ||
            app->variables->simulation->time_step !=
                app->variables->simulation->time_step_cache ||
            app->variables->simulation->time !=
                app->variables->simulation->time_cache)
        {
            save_simulation_cinematic_log(
                app->variables->simulation->particle_cinematic_collection,
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
            on_timeout_cinematic,
            app->window_simulation->drawing_area
        );
    }
}

void on_cinematic_stop_button_clicked(GtkButton* button)
{
    if (app->variables->simulation->is_simulation_running)
    {
        app->variables->simulation->is_simulation_running = FALSE;
        g_timer_stop(app->variables->simulation->timer);
    }
}

void run_simulation_cinematic()
{
    particle_cinematic_collection_start();
    create_window_simulation_widgets(CINEMATIC);
    gtk_widget_show_all(app->window_simulation->window);
}