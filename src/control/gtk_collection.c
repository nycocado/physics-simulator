#include "../include/gtk_include_all.h"

void particle_cinematic_collection_start()
{
    Particle_Cinematic_Collection particle_collection =
        particle_cinematic_collection_new(
            app->variables->simulation->num_particles_use
        );
    GtkTreeIter iter;
    gboolean valid =
        gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->tree_store), &iter);
    int i = 0;
    while (valid)
    {
        gboolean checked;
        gtk_tree_model_get(
            GTK_TREE_MODEL(app->tree_store), &iter, COL_CHECKED, &checked, -1
        );
        if (checked)
        {
            gchar *x, *y, *vx, *vy, *ax, *ay;
            gtk_tree_model_get(
                GTK_TREE_MODEL(app->tree_store),
                &iter,
                0,
                &x,
                1,
                &y,
                2,
                &vx,
                3,
                &vy,
                4,
                &ax,
                5,
                &ay,
                -1
            );

            float x_float = atof(x);
            float y_float = atof(y);
            float vx_float = atof(vx);
            float vy_float = atof(vy);
            float ax_float = atof(ax);
            float ay_float = atof(ay);

            Particle_Cinematic particle = particle_cinematic_new(
                x_float, y_float, vx_float, vy_float, ax_float, ay_float
            );
            particle_collection->particles[i] = particle;
            i++;

            g_free(x);
            g_free(y);
            g_free(vx);
            g_free(vy);
            g_free(ax);
            g_free(ay);
        }
        valid =
            gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &iter);
    }
    app->variables->simulation->particle_cinematic_collection =
        particle_collection;
}

void particle_dynamic_collection_start()
{
    Particle_Dynamic_Collection particle_dynamic_collection =
        particle_dynamic_collection_new(
            app->variables->simulation->num_particles_use
        );
    GtkTreeIter iter;
    gboolean valid =
        gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->tree_store), &iter);
    int i = 0;
    while (valid)
    {
        gboolean checked;
        gtk_tree_model_get(
            GTK_TREE_MODEL(app->tree_store), &iter, COL_CHECKED, &checked, -1
        );
        if (checked)
        {
            gchar *x, *y, *vx, *vy, *ax, *ay, *mass;
            gtk_tree_model_get(
                GTK_TREE_MODEL(app->tree_store),
                &iter,
                0,
                &x,
                1,
                &y,
                2,
                &vx,
                3,
                &vy,
                4,
                &ax,
                5,
                &ay,
                6,
                &mass,
                -1
            );

            float x_float = atof(x);
            float y_float = atof(y);
            float vx_float = atof(vx);
            float vy_float = atof(vy);
            float ax_float = atof(ax);
            float ay_float = atof(ay);
            float mass_float = atof(mass);

            Particle_Dynamic particle = particle_dynamic_new(
                x_float,
                y_float,
                vx_float,
                vy_float,
                ax_float,
                ay_float,
                mass_float
            );
            GtkTreeIter child_iter;
            gboolean child_valid = gtk_tree_model_iter_children(
                GTK_TREE_MODEL(app->tree_store), &child_iter, &iter
            );
            while (child_valid)
            {
                gchar *force_x, *force_y;
                gtk_tree_model_get(
                    GTK_TREE_MODEL(app->tree_store),
                    &child_iter,
                    0,
                    &force_x,
                    1,
                    &force_y,
                    -1
                );

                float force_x_float = atof(force_x);
                float force_y_float = atof(force_y);

                Vector force = create_vector(force_x_float, force_y_float);
                particle->forces = g_list_append(particle->forces, force);

                g_free(force_x);
                g_free(force_y);

                child_valid = gtk_tree_model_iter_next(
                    GTK_TREE_MODEL(app->tree_store), &child_iter
                );
            }
            particle_dynamic_collection->particles[i] = particle;
            i++;

            g_free(x);
            g_free(y);
            g_free(vx);
            g_free(vy);
            g_free(ax);
            g_free(ay);
            g_free(mass);
        }
        valid =
            gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &iter);
    }
    app->variables->simulation->particle_dynamic_collection =
        particle_dynamic_collection;
}