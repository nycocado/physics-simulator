#include "app.h"
#include "ui/builder.h"
#include "ui/main_window.h"
#include <gtk/gtk.h>

static void on_activate(GApplication* gapp, gpointer data)
{
    GtkApp app = (GtkApp)data;
    create_window_main_widgets(app);
    set_columns_attribute(app);
    gtk_window_set_application(
        GTK_WINDOW(app->window_main->window), GTK_APPLICATION(gapp)
    );
    gtk_window_present(GTK_WINDOW(app->window_main->window));
}

int main(int argc, char* argv[])
{
    GtkApp app = gtk_app_new();
    GtkApplication* gapp =
        gtk_application_new("com.simuladorfisica", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(gapp, "activate", G_CALLBACK(on_activate), app);
    int status = g_application_run(G_APPLICATION(gapp), argc, argv);
    g_object_unref(gapp);
    gtk_app_free(app);
    return status;
}
