#include "gtk_include_all.h"

void particle_cinematic_collection_start(GtkApp app)
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
                COL_X,
                &x,
                COL_Y,
                &y,
                COL_VX,
                &vx,
                COL_VY,
                &vy,
                COL_AX,
                &ax,
                COL_AY,
                &ay,
                -1
            );

            float x_float = (float)g_ascii_strtod(x, NULL);
            float y_float = (float)g_ascii_strtod(y, NULL);
            float vx_float = (float)g_ascii_strtod(vx, NULL);
            float vy_float = (float)g_ascii_strtod(vy, NULL);
            float ax_float = (float)g_ascii_strtod(ax, NULL);
            float ay_float = (float)g_ascii_strtod(ay, NULL);

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

void particle_dynamic_collection_start(GtkApp app)
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
                COL_X,
                &x,
                COL_Y,
                &y,
                COL_VX,
                &vx,
                COL_VY,
                &vy,
                COL_AX,
                &ax,
                COL_AY,
                &ay,
                COL_MASS,
                &mass,
                -1
            );

            float x_float = (float)g_ascii_strtod(x, NULL);
            float y_float = (float)g_ascii_strtod(y, NULL);
            float vx_float = (float)g_ascii_strtod(vx, NULL);
            float vy_float = (float)g_ascii_strtod(vy, NULL);
            float ax_float = (float)g_ascii_strtod(ax, NULL);
            float ay_float = (float)g_ascii_strtod(ay, NULL);
            float mass_float = (float)g_ascii_strtod(mass, NULL);

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
                    COL_X,
                    &force_x,
                    COL_Y,
                    &force_y,
                    -1
                );

                float force_x_float = (float)g_ascii_strtod(force_x, NULL);
                float force_y_float = (float)g_ascii_strtod(force_y, NULL);

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