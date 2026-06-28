#include "../include/gtk_include_all.h"

void set_columns_attribute()
{

    gtk_tree_view_column_set_fixed_width(app->window_main->columns->type, 100);

    gtk_tree_view_column_set_alignment(app->window_main->columns->type, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->x, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->y, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->vx, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->vy, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->ax, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->ay, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->mass, 0.5);
    gtk_tree_view_column_set_alignment(app->window_main->columns->check, 0.5);

    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->x, 0.5, 0.5
    );
    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->y, 0.5, 0.5
    );
    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->vx, 0.5, 0.5
    );
    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->vy, 0.5, 0.5
    );
    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->ax, 0.5, 0.5
    );
    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->ay, 0.5, 0.5
    );
    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->mass, 0.5, 0.5
    );
    gtk_cell_renderer_set_alignment(
        app->window_main->cell_renderer->check, 0.5, 0.5
    );

    gtk_tree_view_column_add_attribute(
        app->window_main->columns->type,
        app->window_main->cell_renderer->type,
        "text",
        9
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->x,
        app->window_main->cell_renderer->x,
        "text",
        0
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->y,
        app->window_main->cell_renderer->y,
        "text",
        1
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->vx,
        app->window_main->cell_renderer->vx,
        "text",
        2
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->vy,
        app->window_main->cell_renderer->vy,
        "text",
        3
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->ax,
        app->window_main->cell_renderer->ax,
        "text",
        4
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->ay,
        app->window_main->cell_renderer->ay,
        "text",
        5
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->mass,
        app->window_main->cell_renderer->mass,
        "text",
        6
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->check,
        app->window_main->cell_renderer->check,
        "active",
        7
    );
    gtk_tree_view_column_add_attribute(
        app->window_main->columns->check,
        app->window_main->cell_renderer->check,
        "visible",
        8
    );
}

void gtk_response_projetos_abrir(GtkDialog* dialog, gint response_id)
{
    if (response_id == GTK_RESPONSE_ACCEPT)
    {
        GtkWidget* file_chooser = GTK_WIDGET(dialog);
        gchar* filename =
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
        if (filename != NULL)
        {
            app->variables->project->file_path = g_strdup(filename);
            app->variables->project->is_file_open = TRUE;
            g_free(filename);
        }
        open_project();
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

void gtk_response_projetos_novo(GtkDialog* dialog, gint response_id)
{
    if (response_id == GTK_RESPONSE_ACCEPT)
    {
        gchar* filename =
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (filename != NULL)
        {
            if (!g_str_has_suffix(filename, ".sabino"))
            {
                gchar* new_filename = g_strdup_printf("%s.sabino", filename);
                g_free(filename);
                filename = new_filename;
            }
            FILE* file = fopen(filename, "w+");
            if (file != NULL)
            {
                fclose(file);
                app->variables->project->file_path = g_strdup(filename);
                app->variables->project->is_file_open = TRUE;
            }
            g_free(filename);
        }
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

int run_gtk(int argc, char* argv[])
{
    gtk_app_new();

    gtk_init(&argc, &argv);

    create_window_main_widgets(app);

    set_columns_attribute(app);

    gtk_widget_show(app->window_main->window);
    gtk_main();

    gtk_app_free();
    return 0;
}
