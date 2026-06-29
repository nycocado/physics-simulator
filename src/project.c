#include "project.h"
#include "app.h"
#include "log.h"
#include "phys_item.h"
#include "ui/builder.h"
#include "variables.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

void save_project(GtkApp app)
{
    GKeyFile* key_file = g_key_file_new();
    Variables_Simulation sim = &app->variables->simulation;

    g_key_file_set_double(key_file, "Settings", "Gravity", sim->gravity);
    g_key_file_set_double(key_file, "Settings", "Time", sim->time);
    g_key_file_set_double(key_file, "Settings", "TimeStep", sim->time_step);
    g_key_file_set_double(key_file, "Settings", "Frames", sim->frames);

    guint n_items = g_list_model_get_n_items(G_LIST_MODEL(app->root_store));
    g_key_file_set_integer(key_file, "Settings", "NumParticles", n_items);

    for (guint i = 0; i < n_items; i++)
    {
        g_autoptr(PhysItem) item =
            g_list_model_get_item(G_LIST_MODEL(app->root_store), i);
        char group_name[32];
        g_snprintf(group_name, sizeof(group_name), "Particle_%u", i);

        g_key_file_set_double(key_file, group_name, "X", phys_item_get_x(item));
        g_key_file_set_double(key_file, group_name, "Y", phys_item_get_y(item));
        g_key_file_set_double(
            key_file, group_name, "VX", phys_item_get_vx(item)
        );
        g_key_file_set_double(
            key_file, group_name, "VY", phys_item_get_vy(item)
        );
        g_key_file_set_double(
            key_file, group_name, "AX", phys_item_get_ax(item)
        );
        g_key_file_set_double(
            key_file, group_name, "AY", phys_item_get_ay(item)
        );
        g_key_file_set_double(
            key_file, group_name, "Mass", phys_item_get_mass(item)
        );
        g_key_file_set_boolean(
            key_file, group_name, "Checked", phys_item_get_checked(item)
        );

        GListModel* children = phys_item_get_children(item);
        guint n_children = g_list_model_get_n_items(children);
        g_key_file_set_integer(key_file, group_name, "NumForces", n_children);

        for (guint j = 0; j < n_children; j++)
        {
            g_autoptr(PhysItem) child = g_list_model_get_item(children, j);
            char force_group[64];
            g_snprintf(
                force_group, sizeof(force_group), "Particle_%u_Force_%u", i, j
            );

            g_key_file_set_double(
                key_file, force_group, "FX", phys_item_get_ax(child)
            );
            g_key_file_set_double(
                key_file, force_group, "FY", phys_item_get_ay(child)
            );
        }
    }

    g_autoptr(GError) error = NULL;
    if (!g_key_file_save_to_file(
            key_file, app->variables->project.file_path, &error
        ))
    {
        create_dialog_error_message("Erro ao salvar o projeto", app);
    }

    g_key_file_free(key_file);
}

void open_project(GtkApp app)
{
    GKeyFile* key_file = g_key_file_new();
    g_autoptr(GError) error = NULL;

    if (!g_key_file_load_from_file(
            key_file, app->variables->project.file_path, G_KEY_FILE_NONE, &error
        ))
    {
        create_dialog_error_message("Erro ao abrir o projeto", app);
        g_key_file_free(key_file);
        return;
    }

    g_list_store_remove_all(app->root_store);
    app->variables->simulation.num_particles_use = 0;

    Variables_Simulation sim = &app->variables->simulation;
    sim->gravity = g_key_file_get_double(key_file, "Settings", "Gravity", NULL);
    sim->time = g_key_file_get_double(key_file, "Settings", "Time", NULL);
    sim->time_step =
        g_key_file_get_double(key_file, "Settings", "TimeStep", NULL);
    sim->frames = g_key_file_get_double(key_file, "Settings", "Frames", NULL);

    int num_particles =
        g_key_file_get_integer(key_file, "Settings", "NumParticles", NULL);

    for (int i = 0; i < num_particles; i++)
    {
        char group_name[32];
        g_snprintf(group_name, sizeof(group_name), "Particle_%d", i);

        if (!g_key_file_has_group(key_file, group_name))
            continue;

        double x = g_key_file_get_double(key_file, group_name, "X", NULL);
        double y = g_key_file_get_double(key_file, group_name, "Y", NULL);
        double vx = g_key_file_get_double(key_file, group_name, "VX", NULL);
        double vy = g_key_file_get_double(key_file, group_name, "VY", NULL);
        double ax = g_key_file_get_double(key_file, group_name, "AX", NULL);
        double ay = g_key_file_get_double(key_file, group_name, "AY", NULL);
        double mass = g_key_file_get_double(key_file, group_name, "Mass", NULL);
        gboolean checked =
            g_key_file_get_boolean(key_file, group_name, "Checked", NULL);

        if (mass <= 0)
            continue;

        PhysItem* particle =
            phys_item_new_particle(x, y, vx, vy, ax, ay, mass, checked);
        g_list_store_append(app->root_store, particle);

        if (checked)
        {
            app->variables->simulation.num_particles_use++;
        }

        int num_forces =
            g_key_file_get_integer(key_file, group_name, "NumForces", NULL);
        for (int j = 0; j < num_forces; j++)
        {
            char force_group[64];
            g_snprintf(
                force_group, sizeof(force_group), "Particle_%d_Force_%d", i, j
            );

            if (!g_key_file_has_group(key_file, force_group))
                continue;

            double fx =
                g_key_file_get_double(key_file, force_group, "FX", NULL);
            double fy =
                g_key_file_get_double(key_file, force_group, "FY", NULL);

            PhysItem* force = phys_item_new_force(fx, fy);
            phys_item_add_child(particle, force);
            g_object_unref(force);
        }
        g_object_unref(particle);
    }

    g_key_file_free(key_file);
}

void close_project(GtkApp app)
{
    variables_project_wipe(&app->variables->project);
    app->variables->simulation.num_particles_use = 0;
    g_list_store_remove_all(app->root_store);
}
