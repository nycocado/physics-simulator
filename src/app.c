#include "app.h"
#include <gtk/gtk.h>

GtkApp gtk_app_new()
{
    GtkApp app = g_new0(struct _GtkApp, 1);

    app->window_main = window_main_new();
    app->window_add_particle_normal = window_add_particle_normal_new();
    app->window_add_force_normal = window_add_force_normal_new();
    app->window_edit_particle_normal = window_edit_particle_normal_new();
    app->window_edit_force_normal = window_edit_force_normal_new();
    app->window_simulation = window_simulation_new();
    app->variables = variables_new();
    app->root_store = NULL;
    app->tree_model = NULL;
    app->selection_model = NULL;
    app->column_view = NULL;
    return app;
}

void gtk_app_free(GtkApp app)
{
    window_main_free(app->window_main);
    window_add_particle_normal_free(app->window_add_particle_normal);
    window_add_force_normal_free(app->window_add_force_normal);
    window_edit_particle_normal_free(app->window_edit_particle_normal);
    window_edit_force_normal_free(app->window_edit_force_normal);
    window_simulation_free(app->window_simulation);
    variables_free(app->variables);
    g_free(app);
}
