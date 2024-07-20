#include "../include/gtk_include_all.h"

void create_window_main_widgets() // Cria os widgets da janela principal
{
    GtkBuilder *builder = gtk_builder_new(); // Cria um construtor de widgets

    gtk_builder_add_from_file(builder, "src/view/ui/window_main.glade", NULL); // Adiciona os widgets da janela principal ao construtor
    // Obtém os widgets da janela principal
    app->window_main->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_main->columns->type = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_type"));
    app->window_main->columns->x = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_x"));
    app->window_main->columns->y = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_y"));
    app->window_main->columns->vx = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_vx"));
    app->window_main->columns->vy = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_vy"));
    app->window_main->columns->ax = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_ax"));
    app->window_main->columns->ay = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_ay"));
    app->window_main->columns->mass = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_mass"));
    app->window_main->columns->check = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "column_check"));
    app->window_main->cell_renderer->type = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_type"));
    app->window_main->cell_renderer->x = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_x"));
    app->window_main->cell_renderer->y = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_y"));
    app->window_main->cell_renderer->vx = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_vx"));
    app->window_main->cell_renderer->vy = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_vy"));
    app->window_main->cell_renderer->ax = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_ax"));
    app->window_main->cell_renderer->ay = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_ay"));
    app->window_main->cell_renderer->mass = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_text_mass"));
    app->window_main->cell_renderer->check = GTK_CELL_RENDERER(gtk_builder_get_object(builder, "renderer_check"));
    app->tree_view = GTK_TREE_VIEW(gtk_builder_get_object(builder, "tree_view"));
    app->selection = GTK_TREE_SELECTION(gtk_builder_get_object(builder, "tree_selection"));
    app->tree_store = GTK_TREE_STORE(gtk_builder_get_object(builder, "tree_store"));
    app->window_main->buttons->add_particle = GTK_WIDGET(gtk_builder_get_object(builder, "add_particle_button"));
    app->window_main->buttons->add_force = GTK_WIDGET(gtk_builder_get_object(builder, "add_force_button"));
    app->window_main->buttons->remove = GTK_WIDGET(gtk_builder_get_object(builder, "remove_button"));
    app->window_main->buttons->edit = GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
    app->window_main->buttons->cinematic = GTK_WIDGET(gtk_builder_get_object(builder, "cinematic_button"));
    app->window_main->buttons->dynamic = GTK_WIDGET(gtk_builder_get_object(builder, "dynamic_button"));

    gtk_builder_connect_signals(builder, app); // Conecta os sinais dos widgets da janela principal

    g_object_unref(builder); // Libera o construtor de widgets
}

void create_window_add_particle_normal_widgets() // Cria os widgets da janela de adição de partícula
{
    GtkBuilder *builder = gtk_builder_new(); // Cria um construtor de widgets

    gtk_builder_add_from_file(builder, "src/view/ui/window_add_particle_normal.glade", NULL); // Adiciona os widgets da janela de adição ao construtor
    // Obtém os widgets da janela de adição
    app->window_add_particle_normal->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_add_particle_normal->spin_buttons->x = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_x"));
    app->window_add_particle_normal->spin_buttons->y = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_y"));
    app->window_add_particle_normal->spin_buttons->vx = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vx"));
    app->window_add_particle_normal->spin_buttons->vy = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vy"));
    app->window_add_particle_normal->spin_buttons->ax = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ax"));
    app->window_add_particle_normal->spin_buttons->ay = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ay"));
    app->window_add_particle_normal->spin_buttons->mass = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_mass"));
    app->window_add_particle_normal->buttons->add = GTK_WIDGET(gtk_builder_get_object(builder, "add_button"));
    app->window_add_particle_normal->buttons->cancel = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    // Configura os ajustes dos botões de rotação
    GtkAdjustment *adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_x"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_y"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_vx"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_vy"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_ax"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_ay"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_mass"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), 0.01, G_MAXFLOAT, 1.0, 10.0, 0.0);

    gtk_builder_connect_signals(builder, app); // Conecta os sinais dos widgets da janela de adição

    gtk_window_set_transient_for(GTK_WINDOW(app->window_add_particle_normal->window), GTK_WINDOW(app->window_main->window)); // Define a janela principal como janela pai da janela de adição

    g_object_unref(builder); // Libera o construtor de widgets
}

void create_window_add_force_normal_widgets() // Cria os widgets da janela de adição de força
{
    GtkBuilder *builder = gtk_builder_new(); // Cria um construtor de widgets

    gtk_builder_add_from_file(builder, "src/view/ui/window_add_force_normal.glade", NULL); // Adiciona os widgets da janela de adição ao construtor
    // Obtém os widgets da janela de adição
    app->window_add_force_normal->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_add_force_normal->spin_buttons->fx = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fx"));
    app->window_add_force_normal->spin_buttons->fy = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fy"));
    app->window_add_force_normal->buttons->add = GTK_WIDGET(gtk_builder_get_object(builder, "add_button"));
    app->window_add_force_normal->buttons->cancel = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    // Configura os ajustes dos botões de rotação
    GtkAdjustment *adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_fx"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_fy"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);

    gtk_builder_connect_signals(builder, app); // Conecta os sinais dos widgets da janela de adição

    gtk_window_set_transient_for(GTK_WINDOW(app->window_add_force_normal->window), GTK_WINDOW(app->window_main->window)); // Define a janela principal como janela pai da janela de adição

    g_object_unref(builder); // Libera o construtor de widgets
}

void create_window_edit_particle_normal_widgets() // Cria os widgets da janela de edição de partícula
{
    GtkBuilder *builder = gtk_builder_new(); // Cria um construtor de widgets

    gtk_builder_add_from_file(builder, "src/view/ui/window_edit_particle_normal.glade", NULL); // Adiciona os widgets da janela de edição ao construtor

    // Obtém os widgets da janela de edição
    app->window_edit_particle_normal->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_edit_particle_normal->spin_buttons->x = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_x"));
    app->window_edit_particle_normal->spin_buttons->y = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_y"));
    app->window_edit_particle_normal->spin_buttons->vx = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vx"));
    app->window_edit_particle_normal->spin_buttons->vy = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_vy"));
    app->window_edit_particle_normal->spin_buttons->ax = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ax"));
    app->window_edit_particle_normal->spin_buttons->ay = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_ay"));
    app->window_edit_particle_normal->spin_buttons->mass = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_mass"));
    app->window_edit_particle_normal->buttons->edit = GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
    app->window_edit_particle_normal->buttons->cancel = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    // Configura os ajustes dos botões de rotação
    GtkAdjustment *adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_x"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_y"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_vx"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_vy"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_ax"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_ay"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_mass"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), 1e-30, G_MAXFLOAT, 1.0, 10.0, 0.0);

    gtk_builder_connect_signals(builder, app); // Conecta os sinais dos widgets da janela de edição

    gtk_window_set_transient_for(GTK_WINDOW(app->window_edit_particle_normal->window), GTK_WINDOW(app->window_main->window)); // Define a janela principal como janela pai da janela de edição

    g_object_unref(builder); // Libera o construtor de widgets
}

void create_window_edit_force_normal_widgets() // Cria os widgets da janela de edição de força
{
    GtkBuilder *builder = gtk_builder_new(); // Cria um construtor de widgets

    gtk_builder_add_from_file(builder, "src/view/ui/window_edit_force_normal.glade", NULL); // Adiciona os widgets da janela de edição ao construtor

    // Obtém os widgets da janela de edição
    app->window_edit_force_normal->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_edit_force_normal->spin_buttons->fx = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fx"));
    app->window_edit_force_normal->spin_buttons->fy = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_fy"));
    app->window_edit_force_normal->buttons->edit = GTK_WIDGET(gtk_builder_get_object(builder, "edit_button"));
    app->window_edit_force_normal->buttons->cancel = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    // Configura os ajustes dos botões de rotação
    GtkAdjustment *adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_fx"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_fy"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);

    gtk_builder_connect_signals(builder, app); // Conecta os sinais dos widgets da janela de edição

    gtk_window_set_transient_for(GTK_WINDOW(app->window_edit_force_normal->window), GTK_WINDOW(app->window_main->window)); // Define a janela principal como janela pai da janela de edição

    g_object_unref(builder); // Libera o construtor de widgets
}

void create_window_simulation_widgets(int i) // Cria os widgets da janela de simulação
{
    GtkBuilder *builder = gtk_builder_new(); // Cria um construtor de widgets

    if (i == CINEMATIC) // Se for uma simulação cinemática
    {
        gtk_builder_add_from_file(builder, "src/view/ui/window_cinematic.glade", NULL); // Adiciona os widgets da janela de simulação cinemática ao construtor
    }
    else if (i == DYNAMIC) // Se for uma simulação dinâmica
    {
        gtk_builder_add_from_file(builder, "src/view/ui/window_dynamic.glade", NULL); // Adiciona os widgets da janela de simulação dinâmica ao construtor
    }

    // Obtém os widgets da janela principal
    app->window_simulation->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app->window_simulation->drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
    app->window_simulation->buttons->start = GTK_WIDGET(gtk_builder_get_object(builder, "start_button"));
    app->window_simulation->spin_buttons->gravity = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_g"));
    app->window_simulation->spin_buttons->time = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_t"));
    app->window_simulation->spin_buttons->step = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_p"));
    app->window_simulation->spin_buttons->frames = GTK_WIDGET(gtk_builder_get_object(builder, "spin_button_f"));

    // Configura os ajustes dos botões de rotação
    GtkAdjustment *adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_g"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), -G_MAXFLOAT, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_t"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), 0.01, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_p"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), 0.01, G_MAXFLOAT, 1.0, 10.0, 0.0);
    adjustment = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment_f"));
    gtk_adjustment_configure(adjustment, gtk_adjustment_get_value(adjustment), 1, G_MAXFLOAT, 1.0, 10.0, 0.0);

    gtk_widget_set_size_request(app->window_simulation->drawing_area, 1000, 500); // Define o tamanho da área de desenho

    gtk_builder_connect_signals(builder, app); // Conecta os sinais dos widgets da janela principal

    gtk_window_set_transient_for(GTK_WINDOW(app->window_simulation->window), GTK_WINDOW(app->window_main->window)); // Define a janela principal como janela pai da janela de simulação

    g_object_unref(builder); // Libera o construtor de widgets
}

void create_dialog_error_message(const gchar *message) // Cria uma janela de erro
{
    GtkWidget *dialog_error = gtk_message_dialog_new(GTK_WINDOW(app->window_main->window), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", message); // Cria uma janela de erro
    gtk_window_set_position(GTK_WINDOW(dialog_error), GTK_WIN_POS_CENTER_ON_PARENT);                                                                                                                // Define a posição da janela de erro (centralizada na janela principal)
    gtk_dialog_run(GTK_DIALOG(dialog_error));                                                                                                                                                       // Mostra a janela de erro
    gtk_widget_destroy(dialog_error);                                                                                                                                                               // Fecha a janela de erro
}