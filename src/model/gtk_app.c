#include "../include/gtk_include_all.h"

GtkApp app; // Variável global da aplicação GTK

void gtk_app_new() // Função de criação da aplicação GTK
{
    app = g_slice_new0(struct _GtkApp); // Aloca a memória da aplicação
    // Inicializa os objetos da aplicação
    app->window_main = window_main_new();
    app->window_add_particle_normal = window_add_particle_normal_new();
    app->window_add_force_normal = window_add_force_normal_new();
    app->window_edit_particle_normal = window_edit_particle_normal_new();
    app->window_edit_force_normal = window_edit_force_normal_new();
    app->window_simulation = window_simulation_new();
    app->variables = variables_new();
    app->tree_store = NULL;
    app->tree_view = NULL;
    app->selection = NULL;
}

void gtk_app_free() // Função de liberação da aplicação GTK
{
    // Libera os objetos da aplicação
    window_main_free(app->window_main);
    window_add_particle_normal_free(app->window_add_particle_normal);
    window_add_force_normal_free(app->window_add_force_normal);
    window_edit_particle_normal_free(app->window_edit_particle_normal);
    window_edit_force_normal_free(app->window_edit_force_normal);
    window_simulation_free(app->window_simulation);
    variables_free(app->variables);
    g_slice_free(struct _GtkApp, app);
}