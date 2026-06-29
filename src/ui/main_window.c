#include "gtk_include_all.h"

static void setup_label(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    (void)factory;
    (void)data;
    GtkWidget *label = gtk_label_new(NULL);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_list_item_set_child(list_item, label);
}

static void bind_type(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    (void)factory;
    (void)data;
    GtkWidget *label = gtk_list_item_get_child(list_item);
    GtkTreeListRow *row_item = GTK_TREE_LIST_ROW(gtk_list_item_get_item(list_item));
    if (!row_item) return;
    PhysItem *item = PHYS_ITEM(gtk_tree_list_row_get_item(row_item));

    if (phys_item_get_item_type(item) == PHYS_ITEM_PARTICLE) {
        gtk_label_set_text(GTK_LABEL(label), "Partícula");
    } else {
        gtk_label_set_text(GTK_LABEL(label), "Força");
    }
    g_object_unref(item);
}

#define BIND_DOUBLE(name, getter) \
static void bind_##name(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) { \
    (void)factory; \
    (void)data; \
    GtkWidget *label = gtk_list_item_get_child(list_item); \
    GtkTreeListRow *row_item = GTK_TREE_LIST_ROW(gtk_list_item_get_item(list_item)); \
    if (!row_item) return; \
    PhysItem *item = PHYS_ITEM(gtk_tree_list_row_get_item(row_item)); \
    if (phys_item_get_item_type(item) == PHYS_ITEM_FORCE && \
        (g_strcmp0(#name, "x") == 0 || g_strcmp0(#name, "y") == 0 || \
         g_strcmp0(#name, "vx") == 0 || g_strcmp0(#name, "vy") == 0 || \
         g_strcmp0(#name, "mass") == 0)) { \
        gtk_label_set_text(GTK_LABEL(label), "-"); \
    } else { \
        char buf[64]; \
        g_snprintf(buf, sizeof(buf), "%.4g", phys_item_##getter(item)); \
        gtk_label_set_text(GTK_LABEL(label), buf); \
    } \
    g_object_unref(item); \
}

BIND_DOUBLE(x, get_x)
BIND_DOUBLE(y, get_y)
BIND_DOUBLE(vx, get_vx)
BIND_DOUBLE(vy, get_vy)
BIND_DOUBLE(ax, get_ax)
BIND_DOUBLE(ay, get_ay)
BIND_DOUBLE(mass, get_mass)

static void setup_check(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    (void)factory;
    (void)data;
    GtkWidget *check = gtk_check_button_new();
    gtk_widget_set_halign(check, GTK_ALIGN_CENTER);
    gtk_list_item_set_child(list_item, check);
}

static void bind_check(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    (void)factory;
    (void)data;
    GtkWidget *check = gtk_list_item_get_child(list_item);
    GtkTreeListRow *row_item = GTK_TREE_LIST_ROW(gtk_list_item_get_item(list_item));
    if (!row_item) return;
    PhysItem *item = PHYS_ITEM(gtk_tree_list_row_get_item(row_item));

    if (phys_item_get_item_type(item) == PHYS_ITEM_FORCE) {
        gtk_widget_set_visible(check, FALSE);
    } else {
        gtk_widget_set_visible(check, TRUE);
        gtk_check_button_set_active(GTK_CHECK_BUTTON(check), phys_item_get_checked(item));
    }
    g_object_unref(item);
}

void set_columns_attribute(GtkApp app)
{
    g_signal_connect(app->window_main->factories.type, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.type, "bind", G_CALLBACK(bind_type), NULL);

    g_signal_connect(app->window_main->factories.x, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.x, "bind", G_CALLBACK(bind_x), NULL);

    g_signal_connect(app->window_main->factories.y, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.y, "bind", G_CALLBACK(bind_y), NULL);

    g_signal_connect(app->window_main->factories.vx, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.vx, "bind", G_CALLBACK(bind_vx), NULL);

    g_signal_connect(app->window_main->factories.vy, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.vy, "bind", G_CALLBACK(bind_vy), NULL);

    g_signal_connect(app->window_main->factories.ax, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.ax, "bind", G_CALLBACK(bind_ax), NULL);

    g_signal_connect(app->window_main->factories.ay, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.ay, "bind", G_CALLBACK(bind_ay), NULL);

    g_signal_connect(app->window_main->factories.mass, "setup", G_CALLBACK(setup_label), NULL);
    g_signal_connect(app->window_main->factories.mass, "bind", G_CALLBACK(bind_mass), NULL);

    g_signal_connect(app->window_main->factories.check, "setup", G_CALLBACK(setup_check), NULL);
    g_signal_connect(app->window_main->factories.check, "bind", G_CALLBACK(bind_check), NULL);
}

