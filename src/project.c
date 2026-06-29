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
    FILE* file = fopen(app->variables->project.file_path, "w");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao salvar o projeto", app);
        return;
    }

    Variables_Simulation sim = &app->variables->simulation;
    if (sim->gravity != 0 || sim->time != 0 || sim->time_step != 0 ||
        sim->frames != 0)
    {
        char buf[G_ASCII_DTOSTR_BUF_SIZE];
        fprintf(file, "SETTINGS");
        fprintf(
            file, " gravity=%s", g_ascii_dtostr(buf, sizeof(buf), sim->gravity)
        );
        fprintf(file, " time=%s", g_ascii_dtostr(buf, sizeof(buf), sim->time));
        fprintf(
            file, " step=%s", g_ascii_dtostr(buf, sizeof(buf), sim->time_step)
        );
        fprintf(
            file, " frames=%s", g_ascii_dtostr(buf, sizeof(buf), sim->frames)
        );
        fprintf(file, "\n");
    }

    guint n_items = g_list_model_get_n_items(G_LIST_MODEL(app->root_store));
    for (guint i = 0; i < n_items; i++)
    {
        g_autoptr(PhysItem) item =
            g_list_model_get_item(G_LIST_MODEL(app->root_store), i);
        gdouble x = phys_item_get_x(item);
        gdouble y = phys_item_get_y(item);
        gdouble vx = phys_item_get_vx(item);
        gdouble vy = phys_item_get_vy(item);
        gdouble ax = phys_item_get_ax(item);
        gdouble ay = phys_item_get_ay(item);
        gdouble mass = phys_item_get_mass(item);
        gboolean checked = phys_item_get_checked(item);

        fprintf(
            file,
            "Partícula %g %g %g %g %g %g %g %d\n",
            x,
            y,
            vx,
            vy,
            ax,
            ay,
            mass,
            checked ? 1 : 0
        );

        GListModel* children = phys_item_get_children(item);
        guint n_children = g_list_model_get_n_items(children);
        for (guint j = 0; j < n_children; j++)
        {
            g_autoptr(PhysItem) child = g_list_model_get_item(children, j);
            gdouble fx = phys_item_get_ax(child);
            gdouble fy = phys_item_get_ay(child);
            fprintf(file, "Força %g %g\n", fx, fy);
        }
    }
    fclose(file);
}

static gdouble parse_double_locale_safe(char* str)
{
    if (!str)
        return 0.0;
    for (char* p = str; *p; p++)
    {
        if (*p == ',')
            *p = '.';
    }
    return g_ascii_strtod(str, NULL);
}

void open_project(GtkApp app)
{
    FILE* file = fopen(app->variables->project.file_path, "r");
    if (file == NULL)
    {
        create_dialog_error_message("Erro ao abrir o projeto", app);
        return;
    }
    g_list_store_remove_all(app->root_store);

    size_t len = 0;
    char* line = NULL;
    PhysItem* current_particle = NULL;
    while (getline(&line, &len, file) != -1)
    {
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n')
        {
            line[line_len - 1] = '\0';
            line_len--;
        }
        if (line_len > 0 && line[line_len - 1] == '\r')
        {
            line[line_len - 1] = '\0';
            line_len--;
        }

        char* type = strtok(line, " ");
        if (!type)
            continue;

        if (strcmp(type, "SETTINGS") == 0)
        {
            Variables_Simulation sim = &app->variables->simulation;
            char* token;
            while ((token = strtok(NULL, " ")) != NULL)
            {
                char* eq = strchr(token, '=');
                if (!eq)
                    continue;
                *eq = '\0';
                double val = parse_double_locale_safe(eq + 1);
                if (strcmp(token, "gravity") == 0)
                    sim->gravity = val;
                else if (strcmp(token, "time") == 0)
                    sim->time = val;
                else if (strcmp(token, "step") == 0)
                    sim->time_step = val;
                else if (strcmp(token, "frames") == 0)
                    sim->frames = val;
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
            gdouble dx = parse_double_locale_safe(x);
            gdouble dy = parse_double_locale_safe(y);
            gdouble dvx = parse_double_locale_safe(vx);
            gdouble dvy = parse_double_locale_safe(vy);
            gdouble dax = parse_double_locale_safe(ax);
            gdouble day = parse_double_locale_safe(ay);
            gdouble dmass = parse_double_locale_safe(mass);
            if (dmass <= 0)
                continue;
            char* checked_str = strtok(NULL, " ");
            gboolean checked =
                (checked_str == NULL) ? TRUE : (checked_str[0] != '0');
            PhysItem* particle = phys_item_new_particle(
                dx, dy, dvx, dvy, dax, day, dmass, checked
            );
            g_list_store_append(app->root_store, particle);

            if (current_particle)
                g_object_unref(current_particle);
            current_particle = particle;
            if (checked)
                app->variables->simulation.num_particles_use++;
        }
        else if (strcmp(type, "Força") == 0)
        {
            if (!current_particle)
                continue;
            char* fx_str = strtok(NULL, " ");
            char* fy_str = strtok(NULL, " ");
            if (!fx_str || !fy_str)
                continue;
            gdouble dfx = parse_double_locale_safe(fx_str);
            gdouble dfy = parse_double_locale_safe(fy_str);

            PhysItem* force = phys_item_new_force(dfx, dfy);
            phys_item_add_child(current_particle, force);
            g_object_unref(force);
        }
    }
    if (current_particle)
        g_object_unref(current_particle);
    free(line);
    fclose(file);
}

void close_project(GtkApp app)
{
    variables_project_wipe(&app->variables->project);
    app->variables->simulation.num_particles_use = 0;
    g_list_store_remove_all(app->root_store);
}
