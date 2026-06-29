#include "gtk_include_all.h"

void save_project(GtkApp app)
{
    FILE* file = fopen(app->variables->project->file_path, "w");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao salvar o projeto", app);
        return;
    }

    Variables_Simulation* sim = app->variables->simulation;
    if (sim->gravity != 0 || sim->time != 0 || sim->time_step != 0 ||
        sim->frames != 0)
    {
        char buf[G_ASCII_DTOSTR_BUF_SIZE];
        fprintf(file, "SETTINGS");
        fprintf(
            file,
            " gravity=%s",
            g_ascii_dtostr(buf, sizeof(buf), sim->gravity)
        );
        fprintf(
            file, " time=%s", g_ascii_dtostr(buf, sizeof(buf), sim->time)
        );
        fprintf(
            file,
            " step=%s",
            g_ascii_dtostr(buf, sizeof(buf), sim->time_step)
        );
        fprintf(
            file,
            " frames=%s",
            g_ascii_dtostr(buf, sizeof(buf), sim->frames)
        );
        fprintf(file, "\n");
    }

    GtkTreeIter iter;
    gboolean valid =
        gtk_tree_model_get_iter_first(GTK_TREE_MODEL(app->tree_store), &iter);
    while (valid)
    {
        gchar *x, *y, *vx, *vy, *ax, *ay, *mass;
        gboolean checked;
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
            COL_CHECKED,
            &checked,
            -1
        );
        fprintf(
            file,
            "Partícula %s %s %s %s %s %s %s %d\n",
            x,
            y,
            vx,
            vy,
            ax,
            ay,
            mass,
            checked ? 1 : 0
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

void open_project(GtkApp app)
{
    FILE* file = fopen(app->variables->project->file_path, "r");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao abrir o projeto", app);
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

        if (strcmp(type, "SETTINGS") == 0)
        {
            Variables_Simulation* sim = app->variables->simulation;
            char* token;
            while ((token = strtok(NULL, " ")) != NULL)
            {
                char* eq = strchr(token, '=');
                if (!eq)
                    continue;
                *eq = '\0';
                double val = g_ascii_strtod(eq + 1, NULL);
                if (strcmp(token, "gravity") == 0)
                    sim->gravity = (float)val;
                else if (strcmp(token, "time") == 0)
                    sim->time = (float)val;
                else if (strcmp(token, "step") == 0)
                    sim->time_step = (float)val;
                else if (strcmp(token, "frames") == 0)
                    sim->frames = (float)val;
            }
        }
        else if (strcmp(type, "Partícula") == 0)
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
            char* checked_str = strtok(NULL, " ");
            gboolean checked = (checked_str == NULL) ? TRUE
                                                     : (checked_str[0] != '0');
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
                checked,
                COL_VISIBLE,
                TRUE,
                COL_TYPE,
                type,
                -1
            );
            has_particle = TRUE;
            if (checked)
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

void close_project(GtkApp app)
{
    variables_project_wipe(app->variables->project);
    app->variables->simulation->num_particles_use = 0;
    gtk_tree_store_clear(app->tree_store);
}
