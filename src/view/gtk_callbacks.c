#include "../include/gtk_include_all.h"

void on_window_destroy(GtkWidget* widget)
{
    GtkWidget* toplevel = gtk_widget_get_toplevel(widget);

    if (GTK_IS_WINDOW(toplevel))
    {
        gtk_widget_destroy(toplevel);
    }
}

void on_renderer_check_toggled(GtkCellRendererToggle* renderer, gchar* path_str)
{
    GtkTreePath* path = gtk_tree_path_new_from_string(path_str);
    GtkTreeIter iter;
    gtk_tree_model_get_iter(GTK_TREE_MODEL(app->tree_store), &iter, path);
    gboolean checked;
    gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 7, &checked, -1);
    checked = !checked;
    gtk_tree_store_set(app->tree_store, &iter, 7, checked, -1);
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

void on_window_main_add_particle_button_clicked(GtkButton* button)
{
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível adicionar partículas sem um projeto aberto."
        );
        return;
    }

    create_window_add_particle_normal_widgets();
    gtk_widget_show_all(app->window_add_particle_normal->window);
}

void on_window_add_particle_normal_add_button_clicked(GtkWidget* widget)
{

    const gchar* xi = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_particle_normal->spin_buttons->x)
    );
    const gchar* yi = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_particle_normal->spin_buttons->y)
    );
    const gchar* vx = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_particle_normal->spin_buttons->vx)
    );
    const gchar* vy = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_particle_normal->spin_buttons->vy)
    );
    const gchar* ax = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_particle_normal->spin_buttons->ax)
    );
    const gchar* ay = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_particle_normal->spin_buttons->ay)
    );
    const gchar* mass = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_particle_normal->spin_buttons->mass)
    );

    GtkTreeIter iter;
    gtk_tree_store_append(app->tree_store, &iter, NULL);
    gtk_tree_store_set(
        app->tree_store,
        &iter,
        0,
        xi,
        1,
        yi,
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
        "Partícula",
        -1
    );
    app->variables->simulation->num_particles_use++;
    gtk_widget_destroy(app->window_add_particle_normal->window);
}

void on_window_edit_particle_normal_edit_button_clicked()
{

    const gchar* xi = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->x)
    );
    const gchar* yi = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->y)
    );
    const gchar* vx = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->vx)
    );
    const gchar* vy = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->vy)
    );
    const gchar* ax = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->ax)
    );
    const gchar* ay = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->ay)
    );
    const gchar* mass = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_particle_normal->spin_buttons->mass)
    );

    GtkTreeIter iter;
    GtkTreeModel* model;
    gtk_tree_selection_get_selected(
        gtk_tree_view_get_selection(app->tree_view), &model, &iter
    );
    gtk_tree_store_set(
        app->tree_store,
        &iter,
        0,
        xi,
        1,
        yi,
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
        -1
    );
    gtk_widget_destroy(app->window_edit_particle_normal->window);
}

void on_window_main_add_force_button_clicked(GtkButton* button)
{
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível adicionar forças sem um projeto aberto."
        );
        return;
    }

    GtkTreeModel* model;
    GtkTreeIter iter;
    GtkTreeSelection* selection = gtk_tree_view_get_selection(app->tree_view);
    if (!gtk_tree_selection_get_selected(selection, &model, &iter))
    {
        create_dialog_error_message(
            "Não é possível adicionar uma força sem uma partícula selecionada."
        );
        return;
    }

    GtkTreeIter testIter;
    if (gtk_tree_model_iter_parent(model, &testIter, &iter))
    {
        create_dialog_error_message(
            "Não é possível adicionar uma força em outra força."
        );
        return;
    }

    create_window_add_force_normal_widgets();
    gtk_widget_show_all(app->window_add_force_normal->window);
}

void on_window_add_force_normal_add_button_clicked(GtkWidget* widget)
{

    const gchar* fx = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_force_normal->spin_buttons->fx)
    );
    const gchar* fy = gtk_entry_get_text(
        GTK_ENTRY(app->window_add_force_normal->spin_buttons->fy)
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
        0,
        fx,
        1,
        fy,
        2,
        "",
        3,
        "",
        4,
        "",
        5,
        "",
        6,
        "",
        7,
        FALSE,
        8,
        FALSE,
        9,
        "Força",
        -1
    );

    GtkTreePath* path =
        gtk_tree_model_get_path(GTK_TREE_MODEL(app->tree_store), &parentIter);
    gtk_tree_view_expand_row(app->tree_view, path, FALSE);
    gtk_tree_path_free(path);
    gtk_widget_destroy(app->window_add_force_normal->window);
}

void on_window_edit_force_normal_edit_button_clicked()
{

    const gchar* fx = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_force_normal->spin_buttons->fx)
    );
    const gchar* fy = gtk_entry_get_text(
        GTK_ENTRY(app->window_edit_force_normal->spin_buttons->fy)
    );

    GtkTreeIter iter;
    GtkTreeModel* model;
    gtk_tree_selection_get_selected(
        gtk_tree_view_get_selection(app->tree_view), &model, &iter
    );
    gtk_tree_store_set(app->tree_store, &iter, 0, fx, 1, fy, -1);
    gtk_widget_destroy(app->window_edit_force_normal->window);
}

void on_window_main_edit_button_clicked(GtkWidget* widget)
{

    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível editar partículas sem um projeto aberto."
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
            "Não é possível editar uma partícula sem uma partícula selecionada."
        );
        return;
    }

    GtkTreeIter testIter;
    if (!gtk_tree_model_iter_parent(model, &testIter, &iter))
    {
        create_window_edit_particle_normal_widgets();
        gchar *xi, *yi, *vx, *vy, *ax, *ay, *mass;
        gtk_tree_model_get(
            model,
            &iter,
            0,
            &xi,
            1,
            &yi,
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

        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->x),
            atof(xi)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->y),
            atof(yi)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vx),
            atof(vx)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->vy),
            atof(vy)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ax),
            atof(ax)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_particle_normal->spin_buttons->ay),
            atof(ay)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(
                app->window_edit_particle_normal->spin_buttons->mass
            ),
            atof(mass)
        );

        g_free(xi);
        g_free(yi);
        g_free(vx);
        g_free(vy);
        g_free(ax);
        g_free(ay);
        g_free(mass);
        gtk_widget_show_all(app->window_edit_particle_normal->window);
    }
    else
    {
        create_window_edit_force_normal_widgets();
        gchar *fx, *fy;
        gtk_tree_model_get(model, &iter, 0, &fx, 1, &fy, -1);

        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fx),
            atof(fx)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(app->window_edit_force_normal->spin_buttons->fy),
            atof(fy)
        );

        g_free(fx);
        g_free(fy);
        gtk_widget_show_all(app->window_edit_force_normal->window);
    }
}

void on_window_main_remove_button_clicked(GtkWidget* widget)
{
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível remover partículas sem um projeto aberto."
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
            "selecionada."
        );
        return;
    }

    gboolean checked;
    gtk_tree_model_get(GTK_TREE_MODEL(app->tree_store), &iter, 7, &checked, -1);
    if (checked)
    {
        app->variables->simulation->num_particles_use--;
    }
    gtk_tree_store_remove(app->tree_store, &iter);
}

void on_selection_change_abrir(GtkFileChooser* chooser)
{

    GtkWidget* dialog = GTK_WIDGET(chooser);
    GtkWidget* select_button = gtk_dialog_get_widget_for_response(
        GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT
    );

    gchar* filename = gtk_file_chooser_get_filename(chooser);
    gboolean is_valid = filename &&
                        g_file_test(filename, G_FILE_TEST_IS_REGULAR) &&
                        g_file_test(filename, G_FILE_TEST_EXISTS) &&
                        g_str_has_suffix(filename, ".sabino");

    gtk_widget_set_sensitive(select_button, is_valid);

    if (filename)
    {
        g_free(filename);
    }
}

void on_menu_projetos_abrir_activate()
{
    if (app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Já existe um projeto aberto, feche-o antes de abrir outro."
        );
        return;
    }
    GtkWidget* dialog = gtk_file_chooser_dialog_new(
        "Abrir Arquivo",
        GTK_WINDOW(app->window_main->window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancelar",
        GTK_RESPONSE_CANCEL,
        "_Abrir",
        GTK_RESPONSE_ACCEPT,
        NULL
    );
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    g_signal_connect(
        G_OBJECT(dialog),
        "response",
        G_CALLBACK(gtk_response_projetos_abrir),
        app
    );
    g_signal_connect(
        G_OBJECT(dialog),
        "selection-changed",
        G_CALLBACK(on_selection_change_abrir),
        NULL
    );
    gtk_widget_show_all(dialog);
}

void on_menu_projetos_salvar_activate()
{
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message("Não existe um projeto aberto.");
        return;
    }
    save_project();
}

void on_menu_projetos_novo_activate()
{
    if (app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Já existe um projeto aberto, feche-o antes de abrir outro."
        );
        return;
    }
    GtkWidget* dialog = gtk_file_chooser_dialog_new(
        "Salvar Arquivo",
        GTK_WINDOW(app->window_main->window),
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "_Cancelar",
        GTK_RESPONSE_CANCEL,
        "_Salvar",
        GTK_RESPONSE_ACCEPT,
        NULL
    );
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_file_chooser_set_do_overwrite_confirmation(
        GTK_FILE_CHOOSER(dialog), TRUE
    );
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "andre.sabino");
    g_signal_connect(
        G_OBJECT(dialog),
        "response",
        G_CALLBACK(gtk_response_projetos_novo),
        app
    );

    gtk_widget_show_all(dialog);
}

void on_menu_projetos_fechar_activate()
{
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message("Não existe um projeto aberto.");
        return;
    }
    close_project();
}

void on_window_main_cinematic_button_clicked(GtkButton* button)
{
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem um projeto aberto."
        );
        return;
    }
    if (app->variables->simulation->num_particles_use == 0)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem partículas."
        );
        return;
    }
    run_simulation_cinematic();
}

void on_window_main_dynamic_button_clicked(GtkButton* button)
{
    if (!app->variables->project->is_file_open)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem um projeto aberto."
        );
        return;
    }
    if (app->variables->simulation->num_particles_use == 0)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem partículas."
        );
        return;
    }
    run_simulation_dynamic();
}