#include "gtk_include_all.h"

static void render_double(
    GtkTreeViewColumn* column,
    GtkCellRenderer* renderer,
    GtkTreeModel* model,
    GtkTreeIter* iter,
    gpointer data
)
{
    (void)column;
    gdouble val;
    gint col = GPOINTER_TO_INT(data);
    gtk_tree_model_get(model, iter, col, &val, -1);
    gchar buf[64];
    g_snprintf(buf, sizeof(buf), "%.4g", val);
    g_object_set(renderer, "text", buf, NULL);
}

void set_columns_attribute(GtkApp app)
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
    gtk_tree_view_column_set_cell_data_func(
        app->window_main->columns->x,
        app->window_main->cell_renderer->x,
        render_double,
        GINT_TO_POINTER(COL_X),
        NULL
    );
    gtk_tree_view_column_set_cell_data_func(
        app->window_main->columns->y,
        app->window_main->cell_renderer->y,
        render_double,
        GINT_TO_POINTER(COL_Y),
        NULL
    );
    gtk_tree_view_column_set_cell_data_func(
        app->window_main->columns->vx,
        app->window_main->cell_renderer->vx,
        render_double,
        GINT_TO_POINTER(COL_VX),
        NULL
    );
    gtk_tree_view_column_set_cell_data_func(
        app->window_main->columns->vy,
        app->window_main->cell_renderer->vy,
        render_double,
        GINT_TO_POINTER(COL_VY),
        NULL
    );
    gtk_tree_view_column_set_cell_data_func(
        app->window_main->columns->ax,
        app->window_main->cell_renderer->ax,
        render_double,
        GINT_TO_POINTER(COL_AX),
        NULL
    );
    gtk_tree_view_column_set_cell_data_func(
        app->window_main->columns->ay,
        app->window_main->cell_renderer->ay,
        render_double,
        GINT_TO_POINTER(COL_AY),
        NULL
    );
    gtk_tree_view_column_set_cell_data_func(
        app->window_main->columns->mass,
        app->window_main->cell_renderer->mass,
        render_double,
        GINT_TO_POINTER(COL_MASS),
        NULL
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

