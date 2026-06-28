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
                    COL_X,
                    &fx,
                    COL_Y,
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
    GtkTreeIter particle_iter;
    gboolean has_particle = FALSE;
    while (getline(&line, &len, file) != -1)
    {
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n')
            line[line_len - 1] = '\0';

        char* type = strtok(line, " ");
        if (!type)
            continue;

        if (strcmp(type, "Partícula") == 0)
        {
            char* x = strtok(NULL, " ");
            char* y = strtok(NULL, " ");
            char* vx = strtok(NULL, " ");
            char* vy = strtok(NULL, " ");
            char* ax = strtok(NULL, " ");
            char* ay = strtok(NULL, " ");
            char* mass = strtok(NULL, " ");
            if (!x || !y || !vx || !vy || !ax || !ay || !mass)
                continue;
            if (g_ascii_strtod(mass, NULL) <= 0)
                continue;
            gtk_tree_store_append(app->tree_store, &particle_iter, NULL);
            gtk_tree_store_set(
                app->tree_store,
                &particle_iter,
                COL_X,
                x,
                COL_Y,
                y,
                COL_VX,
                vx,
                COL_VY,
                vy,
                COL_AX,
                ax,
                COL_AY,
                ay,
                COL_MASS,
                mass,
                COL_CHECKED,
                TRUE,
                COL_VISIBLE,
                TRUE,
                COL_TYPE,
                type,
                -1
            );
            has_particle = TRUE;
            app->variables->simulation->num_particles_use++;
        }
        else if (strcmp(type, "Força") == 0)
        {
            if (!has_particle)
                continue;
            char* x = strtok(NULL, " ");
            char* y = strtok(NULL, " ");
            if (!x || !y)
                continue;
            GtkTreeIter child_iter;
            gtk_tree_store_append(app->tree_store, &child_iter, &particle_iter);
            gtk_tree_store_set(
                app->tree_store,
                &child_iter,
                COL_X,
                x,
                COL_Y,
                y,
                COL_CHECKED,
                FALSE,
                COL_VISIBLE,
                FALSE,
                COL_TYPE,
                type,
                -1
            );
        }
    }
    free(line);
    fclose(file);
}

void close_project()
{
    variables_project_wipe(app->variables->project);
    app->variables->simulation->num_particles_use = 0;
    gtk_tree_store_clear(app->tree_store);
}
