#include "builder.h"
#include "app.h"
#include "log.h"
#include "particles/force_dialog.h"
#include "particles/particle_dialog.h"
#include "phys_item.h"
#include "project.h"
#include "simulation/dynamic_sim.h"
#include "simulation/kinematic_sim.h"
#include "simulation/simulation.h"
#include "ui/callbacks.h"
#include "ui/main_window.h"
#include "ui/window_main.h"
#include "ui/window_simulation.h"
#include "variables.h"
#include <gtk/gtk.h>

static GListModel* create_model_func_wrapper(gpointer item, gpointer user_data)
{
    (void)user_data;
    if (phys_item_get_item_type(PHYS_ITEM(item)) == PHYS_ITEM_FORCE)
        return NULL;
    return phys_item_get_children(PHYS_ITEM(item));
}

void create_window_main_widgets(GtkApp app)
{
    GtkBuilder* builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "src/ui/windows/window_main.ui", NULL);

    app->window_main->window =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_main->factories.type =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_type"));
    app->window_main->factories.x =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_x"));
    app->window_main->factories.y =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_y"));
    app->window_main->factories.vx =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_vx"));
    app->window_main->factories.vy =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_vy"));
    app->window_main->factories.ax =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_ax"));
    app->window_main->factories.ay =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_ay"));
    app->window_main->factories.mass =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_mass"));
    app->window_main->factories.check =
        GTK_LIST_ITEM_FACTORY(gtk_builder_get_object(builder, "factory_check"));

    app->column_view =
        GTK_COLUMN_VIEW(gtk_builder_get_object(builder, "column_view"));

    app->root_store = g_list_store_new(PHYS_TYPE_ITEM);

    app->tree_model = gtk_tree_list_model_new(
        G_LIST_MODEL(app->root_store),
        FALSE,
        TRUE,
        create_model_func_wrapper,
        NULL,
        NULL
    );

    app->selection_model = GTK_SELECTION_MODEL(
        gtk_single_selection_new(G_LIST_MODEL(app->tree_model))
    );
    gtk_column_view_set_model(app->column_view, app->selection_model);
    app->window_main->buttons.add_particle =
        GTK_WIDGET(gtk_builder_get_object(builder, "add_particle_button"));
    app->window_main->buttons.add_force =
        GTK_WIDGET(gtk_builder_get_object(builder, "add_force_button"));
    app->window_main->buttons.remove =
        GTK_WIDGET(gtk_builder_get_object(builder, "remove_button"));
    app->window_main->buttons.edit =
        GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
    app->window_main->buttons.cinematic =
        GTK_WIDGET(gtk_builder_get_object(builder, "cinematic_button"));
    app->window_main->buttons.dynamic =
        GTK_WIDGET(gtk_builder_get_object(builder, "dynamic_button"));

    g_signal_connect(
        app->window_main->buttons.add_particle,
        "clicked",
        G_CALLBACK(on_window_main_add_particle_button_clicked),
        app
    );
    g_signal_connect(
        app->window_main->buttons.add_force,
        "clicked",
        G_CALLBACK(on_window_main_add_force_button_clicked),
        app
    );
    g_signal_connect(
        app->window_main->buttons.remove,
        "clicked",
        G_CALLBACK(on_window_main_remove_button_clicked),
        app
    );
    g_signal_connect(
        app->window_main->buttons.edit,
        "clicked",
        G_CALLBACK(on_window_main_edit_button_clicked),
        app
    );
    g_signal_connect(
        app->window_main->buttons.cinematic,
        "clicked",
        G_CALLBACK(on_window_main_cinematic_button_clicked),
        app
    );
    g_signal_connect(
        app->window_main->buttons.dynamic,
        "clicked",
        G_CALLBACK(on_window_main_dynamic_button_clicked),
        app
    );

    GSimpleActionGroup* action_group = g_simple_action_group_new();
    static const struct
    {
            const char* name;
            GCallback fn;
    } menu_actions[] = {
        {"projects-open", G_CALLBACK(on_menu_projects_open_activate)},
        {"projects-new", G_CALLBACK(on_menu_projects_new_activate)},
        {"projects-save", G_CALLBACK(on_menu_projects_save_activate)},
        {"projects-close", G_CALLBACK(on_menu_projects_close_activate)},
    };
    for (int k = 0; k < 4; k++)
    {
        GSimpleAction* action = g_simple_action_new(menu_actions[k].name, NULL);
        g_signal_connect(action, "activate", menu_actions[k].fn, app);
        g_action_map_add_action(G_ACTION_MAP(action_group), G_ACTION(action));
        g_object_unref(action);
    }
    gtk_widget_insert_action_group(
        app->window_main->window, "win", G_ACTION_GROUP(action_group)
    );
    g_object_unref(action_group);

    g_object_unref(builder);
}

void create_window_add_particle_normal_widgets(GtkApp app)
{
    GtkBuilder* builder = gtk_builder_new();

    gtk_builder_add_from_file(
        builder, "src/ui/windows/window_add_particle_normal.ui", NULL
    );

    app->window_add_particle_normal->window =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_add_particle_normal->spin_buttons.x =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_x"));
    app->window_add_particle_normal->spin_buttons.y =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_y"));
    app->window_add_particle_normal->spin_buttons.vx =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vx"));
    app->window_add_particle_normal->spin_buttons.vy =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vy"));
    app->window_add_particle_normal->spin_buttons.ax =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ax"));
    app->window_add_particle_normal->spin_buttons.ay =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ay"));
    app->window_add_particle_normal->spin_buttons.mass =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_mass"));
    app->window_add_particle_normal->buttons.add =
        GTK_WIDGET(gtk_builder_get_object(builder, "add_button"));
    app->window_add_particle_normal->buttons.cancel =
        GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    g_signal_connect(
        app->window_add_particle_normal->buttons.add,
        "clicked",
        G_CALLBACK(on_window_add_particle_normal_add_button_clicked),
        app
    );
    g_signal_connect(
        app->window_add_particle_normal->buttons.cancel,
        "clicked",
        G_CALLBACK(on_window_destroy),
        app
    );

    gtk_window_set_transient_for(
        GTK_WINDOW(app->window_add_particle_normal->window),
        GTK_WINDOW(app->window_main->window)
    );

    g_object_unref(builder);
}

void create_window_add_force_normal_widgets(GtkApp app)
{
    GtkBuilder* builder = gtk_builder_new();

    gtk_builder_add_from_file(
        builder, "src/ui/windows/window_add_force_normal.ui", NULL
    );

    app->window_add_force_normal->window =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_add_force_normal->spin_buttons.fx =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fx"));
    app->window_add_force_normal->spin_buttons.fy =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fy"));
    app->window_add_force_normal->buttons.add =
        GTK_WIDGET(gtk_builder_get_object(builder, "add_button"));
    app->window_add_force_normal->buttons.cancel =
        GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    g_signal_connect(
        app->window_add_force_normal->buttons.add,
        "clicked",
        G_CALLBACK(on_window_add_force_normal_add_button_clicked),
        app
    );
    g_signal_connect(
        app->window_add_force_normal->buttons.cancel,
        "clicked",
        G_CALLBACK(on_window_destroy),
        app
    );

    gtk_window_set_transient_for(
        GTK_WINDOW(app->window_add_force_normal->window),
        GTK_WINDOW(app->window_main->window)
    );

    g_object_unref(builder);
}

void create_window_edit_particle_normal_widgets(GtkApp app)
{
    GtkBuilder* builder = gtk_builder_new();

    gtk_builder_add_from_file(
        builder, "src/ui/windows/window_edit_particle_normal.ui", NULL
    );

    app->window_edit_particle_normal->window =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_edit_particle_normal->spin_buttons.x =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_x"));
    app->window_edit_particle_normal->spin_buttons.y =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_y"));
    app->window_edit_particle_normal->spin_buttons.vx =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vx"));
    app->window_edit_particle_normal->spin_buttons.vy =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vy"));
    app->window_edit_particle_normal->spin_buttons.ax =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ax"));
    app->window_edit_particle_normal->spin_buttons.ay =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ay"));
    app->window_edit_particle_normal->spin_buttons.mass =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_mass"));
    app->window_edit_particle_normal->buttons.edit =
        GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
    app->window_edit_particle_normal->buttons.cancel =
        GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    g_signal_connect(
        app->window_edit_particle_normal->buttons.edit,
        "clicked",
        G_CALLBACK(on_window_edit_particle_normal_edit_button_clicked),
        app
    );
    g_signal_connect(
        app->window_edit_particle_normal->buttons.cancel,
        "clicked",
        G_CALLBACK(on_window_destroy),
        app
    );

    gtk_window_set_transient_for(
        GTK_WINDOW(app->window_edit_particle_normal->window),
        GTK_WINDOW(app->window_main->window)
    );

    g_object_unref(builder);
}

void create_window_edit_force_normal_widgets(GtkApp app)
{
    GtkBuilder* builder = gtk_builder_new();

    gtk_builder_add_from_file(
        builder, "src/ui/windows/window_edit_force_normal.ui", NULL
    );

    app->window_edit_force_normal->window =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_edit_force_normal->spin_buttons.fx =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fx"));
    app->window_edit_force_normal->spin_buttons.fy =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fy"));
    app->window_edit_force_normal->buttons.edit =
        GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
    app->window_edit_force_normal->buttons.cancel =
        GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    g_signal_connect(
        app->window_edit_force_normal->buttons.edit,
        "clicked",
        G_CALLBACK(on_window_edit_force_normal_edit_button_clicked),
        app
    );
    g_signal_connect(
        app->window_edit_force_normal->buttons.cancel,
        "clicked",
        G_CALLBACK(on_window_destroy),
        app
    );

    gtk_window_set_transient_for(
        GTK_WINDOW(app->window_edit_force_normal->window),
        GTK_WINDOW(app->window_main->window)
    );

    g_object_unref(builder);
}

void create_window_simulation_widgets(int i, GtkApp app)
{
    GtkBuilder* builder = gtk_builder_new();

    if (i == SIMULATION_CINEMATIC)
    {
        gtk_builder_add_from_file(
            builder, "src/ui/windows/window_cinematic.ui", NULL
        );
    }
    else if (i == SIMULATION_DYNAMIC)
    {
        gtk_builder_add_from_file(
            builder, "src/ui/windows/window_dynamic.ui", NULL
        );
    }

    app->variables->simulation.type = i;
    app->window_simulation->window =
        GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_simulation->drawing_area =
        GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
    app->window_simulation->buttons.start =
        GTK_WIDGET(gtk_builder_get_object(builder, "start_button"));
    app->window_simulation->buttons.stop =
        GTK_WIDGET(gtk_builder_get_object(builder, "stop_button"));
    app->window_simulation->buttons.refresh =
        GTK_WIDGET(gtk_builder_get_object(builder, "refresh_button"));
    app->window_simulation->spin_buttons.gravity =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_g"));
    app->window_simulation->spin_buttons.time =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_t"));
    app->window_simulation->spin_buttons.step =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_p"));
    app->window_simulation->spin_buttons.frames =
        GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_f"));

    app->window_simulation->follow_check =
        GTK_WIDGET(gtk_builder_get_object(builder, "follow_check"));
    app->window_simulation->zoom_check =
        GTK_WIDGET(gtk_builder_get_object(builder, "zoom_check"));
    app->window_simulation->trail_check =
        GTK_WIDGET(gtk_builder_get_object(builder, "trail_check"));
    app->window_simulation->follow_spin =
        GTK_WIDGET(gtk_builder_get_object(builder, "follow_spin"));

    int max_particles = app->variables->simulation.num_particles_use;
    if (max_particles < 1)
        max_particles = 1;
    gtk_spin_button_set_range(
        GTK_SPIN_BUTTON(app->window_simulation->follow_spin),
        1.0,
        (double)max_particles
    );

    if (i == SIMULATION_CINEMATIC)
    {
        g_signal_connect(
            app->window_simulation->window,
            "close-request",
            G_CALLBACK(on_window_cinematic_destroy),
            app
        );
        g_signal_connect(
            app->window_simulation->buttons.refresh,
            "clicked",
            G_CALLBACK(on_cinematic_refresh_button_clicked),
            app
        );
        g_signal_connect(
            app->window_simulation->buttons.start,
            "clicked",
            G_CALLBACK(on_simulation_start_button_clicked),
            app
        );
        g_signal_connect(
            app->window_simulation->buttons.stop,
            "clicked",
            G_CALLBACK(on_cinematic_stop_button_clicked),
            app
        );
        gtk_drawing_area_set_draw_func(
            GTK_DRAWING_AREA(app->window_simulation->drawing_area),
            on_draw_cinematic,
            app,
            NULL
        );
    }
    else
    {
        g_signal_connect(
            app->window_simulation->window,
            "close-request",
            G_CALLBACK(on_window_dynamic_destroy),
            app
        );
        g_signal_connect(
            app->window_simulation->buttons.refresh,
            "clicked",
            G_CALLBACK(on_dynamic_refresh_button_clicked),
            app
        );
        g_signal_connect(
            app->window_simulation->buttons.start,
            "clicked",
            G_CALLBACK(on_simulation_start_button_clicked),
            app
        );
        g_signal_connect(
            app->window_simulation->buttons.stop,
            "clicked",
            G_CALLBACK(on_dynamic_stop_button_clicked),
            app
        );
        gtk_drawing_area_set_draw_func(
            GTK_DRAWING_AREA(app->window_simulation->drawing_area),
            on_draw_dynamic,
            app,
            NULL
        );
    }

    Variables_Simulation sim = &app->variables->simulation;
    gtk_spin_button_set_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.gravity),
        sim->gravity
    );
    gtk_spin_button_set_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.time), sim->time
    );
    gtk_spin_button_set_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.step),
        sim->time_step
    );
    gtk_spin_button_set_value(
        GTK_SPIN_BUTTON(app->window_simulation->spin_buttons.frames),
        sim->frames
    );

    gtk_window_set_transient_for(
        GTK_WINDOW(app->window_simulation->window),
        GTK_WINDOW(app->window_main->window)
    );
    gtk_window_set_modal(GTK_WINDOW(app->window_simulation->window), TRUE);

    g_object_unref(builder);
}

void create_dialog_error_message(const gchar* message, GtkApp app)
{
    GtkAlertDialog* dialog = gtk_alert_dialog_new("%s", message);
    gtk_alert_dialog_show(dialog, GTK_WINDOW(app->window_main->window));
    g_object_unref(dialog);
}