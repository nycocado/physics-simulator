#include "main_window.h"
#include "app.h"
#include "phys_item.h"
#include "ui/callbacks.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

static void setup_label(
    GtkSignalListItemFactory* factory,
    GtkListItem* list_item,
    gpointer data
)
{
    (void)factory;
    (void)data;
    GtkWidget* label = gtk_label_new(NULL);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_list_item_set_child(list_item, label);
}

static void setup_type_expander(
    GtkSignalListItemFactory* factory,
    GtkListItem* list_item,
    gpointer data
)
{
    (void)factory;
    (void)data;
    GtkWidget* expander = gtk_tree_expander_new();
    GtkWidget* label = gtk_label_new(NULL);
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_tree_expander_set_child(GTK_TREE_EXPANDER(expander), label);
    gtk_list_item_set_child(list_item, expander);
}

static void bind_type(
    GtkSignalListItemFactory* factory,
    GtkListItem* list_item,
    gpointer data
)
{
    (void)factory;
    (void)data;
    GtkWidget* expander = gtk_list_item_get_child(list_item);
    GtkTreeListRow* row_item =
        GTK_TREE_LIST_ROW(gtk_list_item_get_item(list_item));
    if (!row_item)
        return;

    gtk_tree_expander_set_list_row(GTK_TREE_EXPANDER(expander), row_item);

    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row_item));
    GtkWidget* label = gtk_tree_expander_get_child(GTK_TREE_EXPANDER(expander));

    if (phys_item_get_item_type(item) == PHYS_ITEM_PARTICLE)
        gtk_label_set_text(GTK_LABEL(label), "Partícula");
    else
        gtk_label_set_text(GTK_LABEL(label), "Força");

    g_object_unref(item);
}

static void
update_double_property(PhysItem* item, GParamSpec* pspec, GtkWidget* label)
{
    const char* prop_name = g_object_get_data(G_OBJECT(label), "prop_name");

    if (phys_item_get_item_type(item) == PHYS_ITEM_FORCE &&
        (g_strcmp0(prop_name, "x") == 0 || g_strcmp0(prop_name, "y") == 0 ||
         g_strcmp0(prop_name, "vx") == 0 || g_strcmp0(prop_name, "vy") == 0 ||
         g_strcmp0(prop_name, "mass") == 0))
    {
        gtk_label_set_text(GTK_LABEL(label), "-");
    }
    else
    {
        double val = 0.0;
        g_object_get(item, prop_name, &val, NULL);
        char buf[64];
        g_snprintf(buf, sizeof(buf), "%.4g", val);
        gtk_label_set_text(GTK_LABEL(label), buf);
    }
}

static void bind_double_property(
    GtkSignalListItemFactory* factory,
    GtkListItem* list_item,
    gpointer data
)
{
    (void)factory;
    const char* prop_name = (const char*)data;
    GtkWidget* label = gtk_list_item_get_child(list_item);
    GtkTreeListRow* row_item =
        GTK_TREE_LIST_ROW(gtk_list_item_get_item(list_item));
    if (!row_item)
        return;
    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row_item));

    g_object_set_data(G_OBJECT(label), "prop_name", (gpointer)prop_name);
    update_double_property(item, NULL, label);

    char signal_name[64];
    g_snprintf(signal_name, sizeof(signal_name), "notify::%s", prop_name);
    g_signal_connect_object(
        item, signal_name, G_CALLBACK(update_double_property), label, 0
    );
    g_object_unref(item);
}

static void unbind_double_property(
    GtkSignalListItemFactory* factory,
    GtkListItem* list_item,
    gpointer data
)
{
    (void)factory;
    (void)data;
    GtkTreeListRow* row_item =
        GTK_TREE_LIST_ROW(gtk_list_item_get_item(list_item));
    if (!row_item)
        return;
    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row_item));
    GtkWidget* label = gtk_list_item_get_child(list_item);

    g_signal_handlers_disconnect_by_func(
        item, G_CALLBACK(update_double_property), label
    );
    g_object_unref(item);
}

static void setup_check(
    GtkSignalListItemFactory* factory,
    GtkListItem* list_item,
    gpointer data
)
{
    (void)factory;
    GtkApp app = (GtkApp)data;
    GtkWidget* check = gtk_check_button_new();
    gtk_widget_set_halign(check, GTK_ALIGN_CENTER);
    gtk_list_item_set_child(list_item, check);
    g_object_set_data(G_OBJECT(check), "app", app);
    g_signal_connect(check, "toggled", G_CALLBACK(on_check_toggled), NULL);
}

static void bind_check(
    GtkSignalListItemFactory* factory,
    GtkListItem* list_item,
    gpointer data
)
{
    (void)factory;
    (void)data;
    GtkWidget* check = gtk_list_item_get_child(list_item);
    GtkTreeListRow* row_item =
        GTK_TREE_LIST_ROW(gtk_list_item_get_item(list_item));
    if (!row_item)
        return;
    PhysItem* item = PHYS_ITEM(gtk_tree_list_row_get_item(row_item));

    g_object_set_data(G_OBJECT(check), "item", item);

    g_signal_handlers_block_by_func(check, G_CALLBACK(on_check_toggled), NULL);
    if (phys_item_get_item_type(item) == PHYS_ITEM_FORCE)
    {
        gtk_widget_set_visible(check, FALSE);
    }
    else
    {
        gtk_widget_set_visible(check, TRUE);
        gtk_check_button_set_active(
            GTK_CHECK_BUTTON(check), phys_item_get_checked(item)
        );
    }
    g_signal_handlers_unblock_by_func(
        check, G_CALLBACK(on_check_toggled), NULL
    );
    g_object_unref(item);
}

void set_columns_attribute(GtkApp app)
{
    g_signal_connect(
        app->window_main->factories.type, "setup", G_CALLBACK(setup_type_expander), NULL
    );
    g_signal_connect(
        app->window_main->factories.type, "bind", G_CALLBACK(bind_type), NULL
    );

    g_signal_connect(
        app->window_main->factories.x, "setup", G_CALLBACK(setup_label), NULL
    );
    g_signal_connect(
        app->window_main->factories.x,
        "bind",
        G_CALLBACK(bind_double_property),
        "x"
    );
    g_signal_connect(
        app->window_main->factories.x,
        "unbind",
        G_CALLBACK(unbind_double_property),
        NULL
    );

    g_signal_connect(
        app->window_main->factories.y, "setup", G_CALLBACK(setup_label), NULL
    );
    g_signal_connect(
        app->window_main->factories.y,
        "bind",
        G_CALLBACK(bind_double_property),
        "y"
    );
    g_signal_connect(
        app->window_main->factories.y,
        "unbind",
        G_CALLBACK(unbind_double_property),
        NULL
    );

    g_signal_connect(
        app->window_main->factories.vx, "setup", G_CALLBACK(setup_label), NULL
    );
    g_signal_connect(
        app->window_main->factories.vx,
        "bind",
        G_CALLBACK(bind_double_property),
        "vx"
    );
    g_signal_connect(
        app->window_main->factories.vx,
        "unbind",
        G_CALLBACK(unbind_double_property),
        NULL
    );

    g_signal_connect(
        app->window_main->factories.vy, "setup", G_CALLBACK(setup_label), NULL
    );
    g_signal_connect(
        app->window_main->factories.vy,
        "bind",
        G_CALLBACK(bind_double_property),
        "vy"
    );
    g_signal_connect(
        app->window_main->factories.vy,
        "unbind",
        G_CALLBACK(unbind_double_property),
        NULL
    );

    g_signal_connect(
        app->window_main->factories.ax, "setup", G_CALLBACK(setup_label), NULL
    );
    g_signal_connect(
        app->window_main->factories.ax,
        "bind",
        G_CALLBACK(bind_double_property),
        "ax"
    );
    g_signal_connect(
        app->window_main->factories.ax,
        "unbind",
        G_CALLBACK(unbind_double_property),
        NULL
    );

    g_signal_connect(
        app->window_main->factories.ay, "setup", G_CALLBACK(setup_label), NULL
    );
    g_signal_connect(
        app->window_main->factories.ay,
        "bind",
        G_CALLBACK(bind_double_property),
        "ay"
    );
    g_signal_connect(
        app->window_main->factories.ay,
        "unbind",
        G_CALLBACK(unbind_double_property),
        NULL
    );

    g_signal_connect(
        app->window_main->factories.mass, "setup", G_CALLBACK(setup_label), NULL
    );
    g_signal_connect(
        app->window_main->factories.mass,
        "bind",
        G_CALLBACK(bind_double_property),
        "mass"
    );
    g_signal_connect(
        app->window_main->factories.mass,
        "unbind",
        G_CALLBACK(unbind_double_property),
        NULL
    );

    g_signal_connect(
        app->window_main->factories.check, "setup", G_CALLBACK(setup_check), app
    );
    g_signal_connect(
        app->window_main->factories.check, "bind", G_CALLBACK(bind_check), NULL
    );
}
