#include "callbacks.h"
#include "app.h"
#include "log.h"
#include "particles/force_dialog.h"
#include "particles/particle_dialog.h"
#include "phys_item.h"
#include "project.h"
#include "simulation/dynamic_sim.h"
#include "simulation/kinematic_sim.h"
#include "ui/builder.h"
#include "ui/window_main.h"
#include "ui/window_simulation.h"
#include <gtk/gtk.h>
#include <stdio.h>

void on_window_destroy(GtkWidget* widget, gpointer data)
{
    (void)data;
    GtkWidget* root = GTK_WIDGET(gtk_widget_get_root(widget));
    if (GTK_IS_WINDOW(root))
        gtk_window_destroy(GTK_WINDOW(root));
}

void on_check_toggled(GtkCheckButton* button, gpointer data)
{
    (void)data;
    PhysItem* item = g_object_get_data(G_OBJECT(button), "item");
    GtkApp app = g_object_get_data(G_OBJECT(button), "app");
    if (!item || !app)
        return;

    gboolean checked = gtk_check_button_get_active(button);
    gboolean was_checked = phys_item_get_checked(item);

    if (checked != was_checked)
    {
        phys_item_set_checked(item, checked);
        if (checked)
            app->variables->simulation.num_particles_use++;
        else
            app->variables->simulation.num_particles_use--;
    }
}

void on_window_main_add_particle_button_clicked(
    GtkButton* button,
    gpointer data
)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message(
            "Não é possível adicionar partículas sem um projeto aberto.", app
        );
        return;
    }

    GtkBuilder* builder = gtk_builder_new_from_file(
        "src/ui/windows/window_add_particle_normal.ui"
    );
    GtkWindow* win = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    g_object_set_data_full(G_OBJECT(win), "builder", builder, g_object_unref);
    g_object_set_data(G_OBJECT(win), "app", app);

    GtkWidget* add_btn =
        GTK_WIDGET(gtk_builder_get_object(builder, "add_button"));
    GtkWidget* cancel_btn =
        GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
    g_signal_connect(
        add_btn,
        "clicked",
        G_CALLBACK(on_window_add_particle_normal_add_button_clicked),
        win
    );
    g_signal_connect(
        cancel_btn, "clicked", G_CALLBACK(on_window_destroy), NULL
    );

    gtk_window_set_transient_for(win, GTK_WINDOW(app->window_main->window));
    gtk_window_present(win);
}

void on_window_add_particle_normal_add_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkWindow* win = GTK_WINDOW(data);
    GtkBuilder* builder = g_object_get_data(G_OBJECT(win), "builder");
    GtkApp app = g_object_get_data(G_OBJECT(win), "app");

    gdouble xi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_x"))
    );
    gdouble yi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_y"))
    );
    gdouble vx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_vx"))
    );
    gdouble vy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_vy"))
    );
    gdouble ax = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_ax"))
    );
    gdouble ay = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_ay"))
    );
    gdouble mass = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_mass"))
    );

    PhysItem* particle =
        phys_item_new_particle(xi, yi, vx, vy, ax, ay, mass, TRUE);
    g_list_store_append(app->root_store, particle);
    app->variables->simulation.num_particles_use++;
    g_object_unref(particle);
    gtk_window_destroy(win);
}

void on_window_edit_particle_normal_edit_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkWindow* win = GTK_WINDOW(data);
    GtkBuilder* builder = g_object_get_data(G_OBJECT(win), "builder");
    GtkApp app = g_object_get_data(G_OBJECT(win), "app");

    gdouble xi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_x"))
    );
    gdouble yi = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_y"))
    );
    gdouble vx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_vx"))
    );
    gdouble vy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_vy"))
    );
    gdouble ax = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_ax"))
    );
    gdouble ay = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_ay"))
    );
    gdouble mass = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_mass"))
    );

    GtkTreeListRow* row =
        GTK_TREE_LIST_ROW(gtk_single_selection_get_selected_item(
            GTK_SINGLE_SELECTION(app->selection_model)
        ));
    if (!row)
        return;

    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row));
    phys_item_set_x(item, xi);
    phys_item_set_y(item, yi);
    phys_item_set_vx(item, vx);
    phys_item_set_vy(item, vy);
    phys_item_set_ax(item, ax);
    phys_item_set_ay(item, ay);
    phys_item_set_mass(item, mass);
    g_object_unref(item);
    gtk_window_destroy(win);
}

void on_window_main_add_force_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message(
            "Não é possível adicionar forças sem um projeto aberto.", app
        );
        return;
    }

    GtkTreeListRow* row =
        GTK_TREE_LIST_ROW(gtk_single_selection_get_selected_item(
            GTK_SINGLE_SELECTION(app->selection_model)
        ));
    if (!row)
    {
        create_dialog_error_message(
            "Não é possível adicionar uma força sem uma partícula selecionada.",
            app
        );
        return;
    }

    if (gtk_tree_list_row_get_depth(row) > 0)
    {
        create_dialog_error_message(
            "Não é possível adicionar uma força em outra força.", app
        );
        return;
    }

    GtkBuilder* builder =
        gtk_builder_new_from_file("src/ui/windows/window_add_force_normal.ui");
    GtkWindow* win = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    g_object_set_data_full(G_OBJECT(win), "builder", builder, g_object_unref);
    g_object_set_data(G_OBJECT(win), "app", app);
    g_object_set_data(G_OBJECT(win), "row", row);

    GtkWidget* add_btn =
        GTK_WIDGET(gtk_builder_get_object(builder, "add_button"));
    GtkWidget* cancel_btn =
        GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
    g_signal_connect(
        add_btn,
        "clicked",
        G_CALLBACK(on_window_add_force_normal_add_button_clicked),
        win
    );
    g_signal_connect(
        cancel_btn, "clicked", G_CALLBACK(on_window_destroy), NULL
    );

    gtk_window_set_transient_for(win, GTK_WINDOW(app->window_main->window));
    gtk_window_present(win);
}

void on_window_add_force_normal_add_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkWindow* win = GTK_WINDOW(data);
    GtkBuilder* builder = g_object_get_data(G_OBJECT(win), "builder");
    (void)g_object_get_data(G_OBJECT(win), "app");
    GtkTreeListRow* parent_row = g_object_get_data(G_OBJECT(win), "row");

    gdouble fx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fx"))
    );
    gdouble fy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fy"))
    );

    if (!parent_row)
        return;

    PhysItem* parent_item = PHYS_ITEM(gtk_tree_list_row_get_item(parent_row));
    PhysItem* force = phys_item_new_force(fx, fy);
    phys_item_add_child(parent_item, force);
    gtk_tree_list_row_set_expanded(parent_row, TRUE);
    g_object_unref(force);
    g_object_unref(parent_item);
    gtk_window_destroy(win);
}

void on_window_edit_force_normal_edit_button_clicked(
    GtkWidget* widget,
    gpointer data
)
{
    GtkWindow* win = GTK_WINDOW(data);
    GtkBuilder* builder = g_object_get_data(G_OBJECT(win), "builder");
    GtkApp app = g_object_get_data(G_OBJECT(win), "app");

    gdouble fx = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fx"))
    );
    gdouble fy = gtk_spin_button_get_value(
        GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fy"))
    );

    GtkTreeListRow* row =
        GTK_TREE_LIST_ROW(gtk_single_selection_get_selected_item(
            GTK_SINGLE_SELECTION(app->selection_model)
        ));
    if (!row)
        return;

    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row));
    phys_item_set_ax(item, fx);
    phys_item_set_ay(item, fy);
    g_object_unref(item);
    gtk_window_destroy(win);
}

void on_window_main_edit_button_clicked(GtkWidget* widget, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message(
            "Não é possível editar partículas sem um projeto aberto.", app
        );
        return;
    }

    GtkTreeListRow* row =
        GTK_TREE_LIST_ROW(gtk_single_selection_get_selected_item(
            GTK_SINGLE_SELECTION(app->selection_model)
        ));
    if (!row)
    {
        create_dialog_error_message(
            "Não é possível editar uma partícula sem uma partícula "
            "selecionada.",
            app
        );
        return;
    }

    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row));

    if (phys_item_get_item_type(item) == PHYS_ITEM_PARTICLE)
    {
        GtkBuilder* builder = gtk_builder_new_from_file(
            "src/ui/windows/window_edit_particle_normal.ui"
        );
        GtkWindow* win =
            GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
        g_object_set_data_full(
            G_OBJECT(win), "builder", builder, g_object_unref
        );
        g_object_set_data(G_OBJECT(win), "app", app);

        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_x")),
            phys_item_get_x(item)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_y")),
            phys_item_get_y(item)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_vx")),
            phys_item_get_vx(item)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_vy")),
            phys_item_get_vy(item)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_ax")),
            phys_item_get_ax(item)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_ay")),
            phys_item_get_ay(item)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(
                gtk_builder_get_object(builder, "spin_button_mass")
            ),
            phys_item_get_mass(item)
        );

        GtkWidget* edit_btn =
            GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
        GtkWidget* cancel_btn =
            GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
        g_signal_connect(
            edit_btn,
            "clicked",
            G_CALLBACK(on_window_edit_particle_normal_edit_button_clicked),
            win
        );
        g_signal_connect(
            cancel_btn, "clicked", G_CALLBACK(on_window_destroy), NULL
        );

        gtk_window_set_transient_for(win, GTK_WINDOW(app->window_main->window));
        gtk_window_present(win);
    }
    else
    {
        GtkBuilder* builder = gtk_builder_new_from_file(
            "src/ui/windows/window_edit_force_normal.ui"
        );
        GtkWindow* win =
            GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
        g_object_set_data_full(
            G_OBJECT(win), "builder", builder, g_object_unref
        );
        g_object_set_data(G_OBJECT(win), "app", app);

        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fx")),
            phys_item_get_ax(item)
        );
        gtk_spin_button_set_value(
            GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "spin_button_fy")),
            phys_item_get_ay(item)
        );

        GtkWidget* edit_btn =
            GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
        GtkWidget* cancel_btn =
            GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));
        g_signal_connect(
            edit_btn,
            "clicked",
            G_CALLBACK(on_window_edit_force_normal_edit_button_clicked),
            win
        );
        g_signal_connect(
            cancel_btn, "clicked", G_CALLBACK(on_window_destroy), NULL
        );

        gtk_window_set_transient_for(win, GTK_WINDOW(app->window_main->window));
        gtk_window_present(win);
    }
    g_object_unref(item);
}

void on_window_main_remove_button_clicked(GtkWidget* widget, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message(
            "Não é possível remover partículas sem um projeto aberto.", app
        );
        return;
    }

    GtkTreeListRow* row =
        GTK_TREE_LIST_ROW(gtk_single_selection_get_selected_item(
            GTK_SINGLE_SELECTION(app->selection_model)
        ));
    if (!row)
    {
        create_dialog_error_message(
            "Não é possível remover uma partícula sem uma partícula "
            "selecionada.",
            app
        );
        return;
    }

    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row));

    if (phys_item_get_item_type(item) == PHYS_ITEM_PARTICLE)
    {
        if (phys_item_get_checked(item))
        {
            app->variables->simulation.num_particles_use--;
        }

        guint n_items = g_list_model_get_n_items(G_LIST_MODEL(app->root_store));
        for (guint i = 0; i < n_items; i++)
        {
            g_autoptr(PhysItem) child =
                g_list_model_get_item(G_LIST_MODEL(app->root_store), i);
            if (child == item)
            {
                g_list_store_remove(app->root_store, i);
                break;
            }
        }
    }
    else
    {
        guint n_items = g_list_model_get_n_items(G_LIST_MODEL(app->root_store));
        for (guint i = 0; i < n_items; i++)
        {
            g_autoptr(PhysItem) particle =
                g_list_model_get_item(G_LIST_MODEL(app->root_store), i);
            phys_item_remove_child(particle, item);
        }
    }
    g_object_unref(item);
}

static GtkFileFilter* make_sabino_filter(void)
{
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Projetos Sabino (*.sabino)");
    gtk_file_filter_add_pattern(filter, "*.sabino");
    return filter;
}

static void
on_projetos_abrir_response(GObject* source, GAsyncResult* result, gpointer data)
{
    GtkApp app = (GtkApp)data;
    GError* error = NULL;
    GFile* file =
        gtk_file_dialog_open_finish(GTK_FILE_DIALOG(source), result, &error);
    g_object_unref(source);
    if (file == NULL)
    {
        g_clear_error(&error);
        return;
    }
    g_free(app->variables->project.file_path);
    app->variables->project.file_path = g_file_get_path(file);
    g_object_unref(file);

    if (open_project(app))
    {
        app->variables->project.is_file_open = TRUE;
    }
    else
    {
        g_free(app->variables->project.file_path);
        app->variables->project.file_path = NULL;
        app->variables->project.is_file_open = FALSE;
    }
}

void on_menu_projects_open_activate(
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
)
{
    (void)action;
    (void)parameter;
    GtkApp app = (GtkApp)data;
    if (app->variables->project.is_file_open)
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
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
)
{
    (void)action;
    (void)parameter;
    GtkApp app = (GtkApp)data;
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message("Não existe um projeto aberto.", app);
        return;
    }
    save_project(app);
}

static void
on_projetos_novo_response(GObject* source, GAsyncResult* result, gpointer data)
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
        g_free(app->variables->project.file_path);
        app->variables->project.file_path = path;
        app->variables->project.is_file_open = TRUE;
    }
    else
    {
        g_free(path);
    }
}

void on_menu_projects_new_activate(
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
)
{
    (void)action;
    (void)parameter;
    GtkApp app = (GtkApp)data;
    if (app->variables->project.is_file_open)
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
    GSimpleAction* action,
    GVariant* parameter,
    gpointer data
)
{
    (void)action;
    (void)parameter;
    GtkApp app = (GtkApp)data;
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message("Não existe um projeto aberto.", app);
        return;
    }
    close_project(app);
}

void on_window_main_cinematic_button_clicked(GtkButton* button, gpointer data)
{
    GtkApp app = (GtkApp)data;
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem um projeto aberto.", app
        );
        return;
    }
    if (app->variables->simulation.num_particles_use == 0)
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
    if (!app->variables->project.is_file_open)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem um projeto aberto.", app
        );
        return;
    }
    if (app->variables->simulation.num_particles_use == 0)
    {
        create_dialog_error_message(
            "Não é possível iniciar a simulação sem partículas.", app
        );
        return;
    }
    run_simulation_dynamic(app);
}
