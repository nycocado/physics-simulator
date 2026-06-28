#include "../include/gtk_include_all.h"

void save_project()
{
    FILE* file = fopen(app->variables->project->file_path, "w");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao salvar o projeto");
        return;
    }

    GtkTreeIter iter;
    gboolean valid =
        gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->tree_store), &iter);
    while (valid)
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
        fprintf(
            file, "Partícula %s %s %s %s %s %s %s\n", x, y, vx, vy, ax, ay, mass
        );

        g_free(x);
        g_free(y);
        g_free(vx);
        g_free(vy);
        g_free(ax);
        g_free(ay);
        g_free(mass);

        GtkTreeIter childIter;
        if (gtk_tree_model_iter_children(
                GTK_TREE_MODEL(app->tree_store), &childIter, &iter
            ))
        {
            do
            {
                gchar *fx, *fy;
                gtk_tree_model_get(
                    GTK_TREE_MODEL(app->tree_store),
                    &childIter,
                    0,
                    &fx,
                    1,
                    &fy,
                    -1
                );
                fprintf(file, "Força %s %s\n", fx, fy);

                g_free(fx);
                g_free(fy);
            } while (gtk_tree_model_iter_next(
                GTK_TREE_MODEL(app->tree_store), &childIter
            ));
        }
        valid =
            gtk_tree_model_iter_next(GTK_TREE_MODEL(app->tree_store), &iter);
    }
    fclose(file);
}

void open_project()
{
    FILE* file = fopen(app->variables->project->file_path, "r");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao abrir o projeto");
        return;
    }
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
    {
        char *type, *x, *y, *vx, *vy, *ax, *ay, *mass;
        line[strlen(line) - 1] = '\0';

        type = strtok(line, " ");
        x = strtok(NULL, " ");
        y = strtok(NULL, " ");
        vx = strtok(NULL, " ");
        vy = strtok(NULL, " ");
        ax = strtok(NULL, " ");
        ay = strtok(NULL, " ");
        mass = strtok(NULL, " ");

        if (!type || !x || !y || !vx || !vy || !ax || !ay || !mass)
            continue;

        GtkTreeIter iter, childIter;
        if (strcmp(type, "Partícula") == 0)
        {
            gtk_tree_store_append(app->tree_store, &iter, NULL);
            gtk_tree_store_set(
                app->tree_store,
                &iter,
                0,
                x,
                1,
                y,
                2,
                vx,
                3,
                vy,
                4,
                ax,
                5,
                ay,
                6,
                mass,
                7,
                TRUE,
                8,
                TRUE,
                9,
                type,
                -1
            );
            app->variables->simulation->num_particles_use++;
        }
        else if (strcmp(type, "Força") == 0)
        {
            gtk_tree_store_append(app->tree_store, &childIter, &iter);
            gtk_tree_store_set(
                app->tree_store,
                &childIter,
                0,
                x,
                1,
                y,
                7,
                FALSE,
                8,
                FALSE,
                9,
                type,
                -1
            );
        }
    }
    fclose(file);
}

void close_project()
{
    variables_project_wipe(app->variables->project);
    app->variables->simulation->num_particles_use = 0;
    gtk_tree_store_clear(app->tree_store);
}