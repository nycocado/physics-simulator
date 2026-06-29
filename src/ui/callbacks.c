#include "gtk_include_all.h"

void on_window_destroy(GtkWidget* widget, gpointer data)
{
    (void)data;
    GtkWidget* root = GTK_WIDGET(gtk_widget_get_root(widget));
    if (GTK_IS_WINDOW(root))
        gtk_window_destroy(GTK_WINDOW(root));
}

void on_renderer_check_toggled(
    GtkCellRendererToggle* renderer,
    gchar* path_str,
    gpointer data
)
{
    GtkApp app = (GtkApp)data;
    GtkTreePath* path = gtk_tree_path_new_from_string(path_str);
    GtkTreeIter iter;
    gtk_tree_model_get_iter(GTK_TREE_MODEL(app->tree_store), &iter, path);
    gboolean checked;
    gtk_tree_model_get(
        GTK_TREE_MODEL(app->tree_store), &iter, COL_CHECKED, &checked, -1
    );
    checked = !checked;
    gtk_tree_store_set(app->tree_store, &iter, COL_CHECKED, checked, -1);
    if (checked)
    {
        app->variables->simulation->num_particles_use++;
    }
    else
    {
        app->variables->simulation->num_particles_use--;
    }
    gtk_tree_path_free(path);
}

void on_window_main_add_particle_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível adicionar partículas sem um projeto aberto.", app
        );
        return;
    }

    create_window_add_particle_normal_widgets(app);
    gtk_window_present(GTK_WINDOW(app->window_add_particle_normal->window));
}

void on_window_add_particle_normal_add_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkApp app = (GtkApp)data;
    gdouble xi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_particle_normal->spin_buttons->x)
    );
    gdouble yi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_particle_normal->spin_buttons->y)
    );
    gdouble vx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_particle_normal->spin_buttons->vx)
    );
    gdouble vy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_particle_normal->spin_buttons->vy)
    );
    gdouble ax = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_particle_normal->spin_buttons->ax)
    );
    gdouble ay = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_particle_normal->spin_buttons->ay)
    );
    gdouble mass = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_particle_normal->spin_buttons->mass)
    );

    GtkTreeIter iter;
    gtk_tree_store_append(app->tree_store, &iter, NULL);
    gtk_tree_store_set(
        app->tree_store,
        &iter,
        COL_X,
        xi,
        COL_Y,
        yi,
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
        "Partícula",
        -1
    );
    app->variables->simulation->num_particles_use++;
    gtk_window_destroy(GTK_WINDOW(app->window_add_particle_normal->window));
}

void on_window_edit_particle_normal_edit_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkApp app = (GtkApp)data;
    gdouble xi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->x)
    );
    gdouble yi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->y)
    );
    gdouble vx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vx)
    );
    gdouble vy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vy)
    );
    gdouble ax = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ax)
    );
    gdouble ay = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ay)
    );
    gdouble mass = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->mass)
    );

    GtkTreeIter iter;
    GtkTreeModel* model;
    gtk_tree_selection_get_selected(
        gtk_tree_view_get_selection(app->tree_view), &model, &iter
    );
    gtk_tree_store_set(
        app->tree_store,
        &iter,
        COL_X,
        xi,
        COL_Y,
        yi,
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
        -1
    );
    gtk_window_destroy(GTK_WINDOW(app->window_edit_particle_normal->window));
}

void on_window_main_add_force_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível adicionar forças sem um projeto aberto.", app
        );
        return;
    }

    GtkTreeModel* model;
    GtkTreeIter iter;
    GtkTreeSelection* selection = gtk_tree_view_get_selection(app->tree_view);
    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        create_dialog_error_message(
            "Não é possível adicionar uma força sem uma partícula selecionada.",
            app
        );
        return;
    }

    GtkTreeIter testIter;
    if (gtk_tree_model_iter_parent(model, &testIter, &iter))
    {
        create_dialog_error_message(
            "Não é possível adicionar uma força em outra força.", app
        );
        return;
    }

    create_window_add_force_normal_widgets(app);
    gtk_window_present(GTK_WINDOW(app->window_add_force_normal->window));
}

void on_window_add_force_normal_add_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkApp app = (GtkApp)data;
    gdouble fx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_force_normal->spin_buttons->fx)
    );
    gdouble fy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_add_force_normal->spin_buttons->fy)
    );

    GtkTreeModel* model;
    GtkTreeIter parentIter, childIter, testIter;
    gtk_tree_selection_get_selected(
        gtk_tree_view_get_selection(app->tree_view), &model, &parentIter
    );
    gtk_tree_store_append(app->tree_store, &childIter, &parentIter);
    gtk_tree_store_set(
        app->tree_store,
        &childIter,
        COL_X,
        fx,
        COL_Y,
        fy,
        COL_VX,
        0.0,
        COL_VY,
        0.0,
        COL_AX,
        0.0,
        COL_AY,
        0.0,
        COL_MASS,
        0.0,
        COL_CHECKED,
        FALSE,
        COL_VISIBLE,
        FALSE,
        COL_TYPE,
        "Força",
        -1
    );

    GtkTreePath* path =
        gtk_tree_model_get_path(GTK_TREE_MODEL(app->tree_store), &parentIter);
    gtk_tree_view_expand_row(app->tree_view, path, FALSE);
    gtk_tree_path_free(path);
    gtk_window_destroy(GTK_WINDOW(app->window_add_force_normal->window));
}

void on_window_edit_force_normal_edit_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkApp app = (GtkApp)data;
    gdouble fx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fx)
    );
    gdouble fy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fy)
    );

    GtkTreeIter iter;
    GtkTreeModel* model;
    gtk_tree_selection_get_selected(
        gtk_tree_view_get_selection(app->tree_view), &model, &iter
    );
    gtk_tree_store_set(app->tree_store, &iter, COL_X, fx, COL_Y, fy, -1);
    gtk_window_destroy(GTK_WINDOW(app->window_edit_force_normal->window));
}

void on_window_main_edit_button_clicked(GtkWidget* widget, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível editar partículas sem um projeto aberto.", app
        );
        return;
    }

    GtkTreeModel* model;
    GtkTreeIter iter;
    if (!gtk_tree_selection_get_selected(
            gtk_tree_view_get_selection(app->tree_view), &model, &iter
        ))
    {
        create_dialog_error_message(
            "Não é possível editar uma partícula sem uma partícula selecionada.",
            app
        );
        return;
    }

    GtkTreeIter testIter;
    if (!gtk_tree_model_iter_parent(model, &testIter, &iter))
    {
        create_window_edit_particle_normal_widgets(app);
        gdouble xi, yi, vx, vy, ax, ay, mass;
        gtk_tree_model_get(
            model,
            &iter,
            COL_X,
            &xi,
            COL_Y,
            &yi,
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

        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->x),
            xi
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->y),
            yi
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vx),
            vx
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vy),
            vy
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ax),
            ax
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ay),
            ay
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(
                app->window_edit_particle_normal->spin_buttons->mass
            ),
            mass
        );

        gtk_window_present(GTK_WINDOW(app->window_edit_particle_normal->window));
    }
    else
    {
        create_window_edit_force_normal_widgets(app);
        gdouble fx, fy;
        gtk_tree_model_get(model, &iter, COL_X, &fx, COL_Y, &fy, -1);

        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fx),
            fx
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fy),
            fy
        );

        gtk_window_present(GTK_WINDOW(app->window_edit_force_normal->window));
    }
}

void on_window_main_remove_button_clicked(GtkWidget* widget, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível remover partículas sem um projeto aberto.", app
        );
        return;
    }

    GtkTreeModel* model;
    GtkTreeIter iter;
    GtkTreeSelection* selection = gtk_tree_view_get_selection(app->tree_view);
    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        create_dialog_error_message(
            "Não é possível remover uma partícula sem uma partícula "
            "selecionada.",
            app
        );
        return;
    }

    gboolean checked;
    gtk_tree_model_get(
        GTK_TREE_MODEL(app->tree_store), &iter, COL_CHECKED, &checked, -1
    );
    if (checked)
    {
        app->variables->simulation->num_particles_use--;
    }
    gtk_tree_store_remove(app->tree_store, &iter);
}

static GtkFileFilter* make_sabino_filter(void)
{
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Projetos Sabino (*.sabino)");
    gtk_file_filter_add_pattern(filter, "*.sabino");
    return filter;
}

static void on_projetos_abrir_response(
    GObject* source, GAsyncResult* result, gpointer data
)
{
    GtkApp app = (GtkApp)data;
    GError* error = NULL;
    GFile* file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), result, &error);
    g_object_unref(source);
    if (file == NULL)
    {
        g_clear_error(&error);
        return;
    }
    g_free(app->variables->project->file_path);
    app->variables->project->file_path = g_file_get_path(file);
    app->variables->project->is_file_open = TRUE;
    g_object_unref(file);
    open_project(app);
}

void on_menu_projects_open_activate(
    GSimpleAction* action, GVariant* parameter, gpointer data
)
{
    (void)action; (void)parameter;
    GtkApp app = (GtkApp)data;
    if (app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Já existe um projeto aberto, feche-o antes de abrir outro.", app
        );
        return;
    }
    GtkFileDialog* dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(dialog, "Abrir Arquivo");
    GListStore* filters = g_list_store_new(GTK_TYPE_FILE_FILTER);
    GtkFileFilter* filter = make_sabino_filter();
    g_list_store_append(filters, filter);
    g_object_unref(filter);
    gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filters));
    g_object_unref(filters);
    gtk_file_dialog_open(
        dialog,
        GTK_WINDOW(app->window_main->window),
        NULL,
        on_projetos_abrir_response,
        app
    );
}

void on_menu_projects_save_activate(
    GSimpleAction* action, GVariant* parameter, gpointer data
)
{
    (void)action; (void)parameter;
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message("Não existe um projeto aberto.", app);
        return;
    }
    save_project(app);
}

static void on_projetos_novo_response(
    GObject* source, GAsyncResult* result, gpointer data
)
{
    GtkApp app = (GtkApp)data;
    GError* error = NULL;
    GFile* file =
        gtk_file_dialog_save_finish(GTK_FILE_DIALOG(source), result, &error);
    g_object_unref(source);
    if (file == NULL)
    {
        g_clear_error(&error);
        return;
    }
    gchar* path = g_file_get_path(file);
    g_object_unref(file);
    if (!g_str_has_suffix(path, ".sabino"))
    {
        gchar* with_ext = g_strdup_printf("%s.sabino", path);
        g_free(path);
        path = with_ext;
    }
    FILE* fp = fopen(path, "w+");
    if (fp != NULL)
    {
        fclose(fp);
        g_free(app->variables->project->file_path);
        app->variables->project->file_path = path;
        app->variables->project->is_file_open = TRUE;
    }
    else
    {
        g_free(path);
    }
}

void on_menu_projects_new_activate(
    GSimpleAction* action, GVariant* parameter, gpointer data
)
{
    (void)action; (void)parameter;
    GtkApp app = (GtkApp)data;
    if (app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Já existe um projeto aberto, feche-o antes de abrir outro.", app
        );
        return;
    }
    GtkFileDialog* dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(dialog, "Novo Projeto");
    gtk_file_dialog_set_initial_name(dialog, "projeto.sabino");
    gtk_file_dialog_save(
        dialog,
        GTK_WINDOW(app->window_main->window),
        NULL,
        on_projetos_novo_response,
        app
    );
}

void on_menu_projects_close_activate(
    GSimpleAction* action, GVariant* parameter, gpointer data
)
{
    (void)action; (void)parameter;
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message("Não existe um projeto aberto.", app);
        return;
    }
    close_project(app);
}

void on_window_main_cinematic_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem um projeto aberto.", app
        );
        return;
    }
    if (app->variables->simulation->num_particles_use == 0)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem partículas.", app
        );
        return;
    }
    run_simulation_cinematic(app);
}

void on_window_main_dynamic_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem um projeto aberto.", app
        );
        return;
    }
    if (app->variables->simulation->num_particles_use == 0)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem partículas.", app
        );
        return;
    }
    run_simulation_dynamic(app);
}
