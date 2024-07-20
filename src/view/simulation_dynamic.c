#include "../include/gtk_include_all.h"

gboolean on_draw_dynamic(GtkWidget *widget, cairo_t *cr)
{
    get_window_size(widget);                 // Obtém o tamanho da janela
    set_background_color(cr, 0.2, 0.2, 0.2); // Define a cor de fundo

    // Pega o centro da janela, em relação ao eixo X e Y
    int x_center = app->variables->window_size->width / 2;
    int y_center = app->variables->window_size->height / 2;

    draw_axes(cr, x_center, y_center); // Desenha os eixos

    draw_time(cr, app->variables->simulation->last_time, 10, 20); // Desenha o tempo

    // Desenhar as partículas
    Particle_Dynamic_Collection particle_collection = app->variables->simulation->particle_dynamic_collection; // Pega a coleção de partículas
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)                                    // Para cada partícula
    {
        Particle_Dynamic particle = particle_collection->particles[i]; // Pega a partícula
        // Pega os valores da partícula
        float x = particle->position->x;
        float y = particle->position->y;
        // Pega os valores da força resultante
        float frx = particle->force_resultant->x;
        float fry = particle->force_resultant->y;

        // Calcula as posições iniciais e finais da partícula
        float start_x = x_center + x;
        float start_y = y_center - y;
        // Calcula as posições finais da velocidade
        float end_frx = start_x + frx;
        float end_fry = start_y - fry;

        draw_particle(cr, start_x, start_y, 5); // Desenha a partícula

        // Define o tamanho e o ângulo da seta
        double arrow_length = 10.0;
        double arrow_angle = G_PI / 6.0;

        // Define a cor e a largura da linha
        cairo_set_source_rgb(cr, 0, 1, 0);
        cairo_set_line_width(cr, 2);

        // Desenha a força resultante
        if (frx != 0 || fry != 0) // Se houver vetor
        {
            draw_arrow(cr, start_x, start_y, end_frx, end_fry, arrow_length, arrow_angle); // Desenha a seta
            if (frx != 0 && fry != 0)                                                      // Se houver vetor x e y
            {
                draw_title(cr, "f", end_frx + 5, end_fry); // Desenha o título
            }
        }

        // Desenha vetor x da força resultante
        if (frx != 0) // Se houver vetor
        {
            draw_arrow(cr, start_x, start_y, end_frx, start_y, arrow_length, arrow_angle); // Desenha a seta
            draw_title(cr, "fx", end_frx + 5, start_y);                                    // Desenha o título
        }

        // Desenha vetor y da força resultante
        if (fry != 0) // Se houver vetor
        {
            draw_arrow(cr, start_x, start_y, start_x, end_fry, arrow_length, arrow_angle); // Desenha a seta
            draw_title(cr, "fy", start_x + 5, end_fry - 5);                                // Desenha o título
        }
    }
    return FALSE; // Retorna FALSE para parar de desenhar
}

gboolean on_timeout_dynamic(gpointer user_data)
{
    // Verifica se o widget existe
    if (!GTK_IS_WIDGET(user_data)) // Se o widget não for um widget (ou seja, não existir mais)
    {
        if (app->variables->simulation->timer != NULL) // Se o timer não for nulo
        {
            g_timer_stop(app->variables->simulation->timer); // Para o timer
        }
        return FALSE; // Retorna FALSE (para parar de chamar o timeout)
    }

    // Verifica se a simulação está rodando
    if (!app->variables->simulation->is_simulation_running) // Se a simulação não estiver rodando
    {
        return FALSE; // Retorna FALSE (para parar de chamar o timeout)
    }

    GtkWidget *drawing_area = app->window_simulation->drawing_area;                                   // Pega a área de desenho
    app->variables->simulation->last_time = g_timer_elapsed(app->variables->simulation->timer, NULL); // Pega o tempo decorrido no timer
    double elapsed_time = app->variables->simulation->last_time;                                      // Pega o tempo decorrido
    float total_time = app->variables->simulation->time;                                              // Pega o tempo total

    Particle_Dynamic_Collection particle_collection = app->variables->simulation->particle_dynamic_collection; // Pega a coleção de partículas
    // Atualizar a simulação
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++) // Para cada partícula
    {
        Particle_Dynamic particle = particle_collection->particles[i]; // Pega a partícula
        // Pega os valores da partícula
        float xi = particle->position_i->x;
        float yi = particle->position_i->y;
        float vxi = particle->velocity_i->x;
        float vyi = particle->velocity_i->y;
        float ax = particle->acceleration->x;
        float ay = particle->acceleration->y;

        // Atualiza a posição
        particle->position->x = phyc_position(xi, vxi, ax, elapsed_time);
        particle->position->y = phyc_position(yi, vyi, ay, elapsed_time);
    }

    // Verifica se o tempo decorrido é maior que o tempo total
    if (elapsed_time >= total_time) // Se o tempo decorrido for maior que o tempo total
    {
        app->variables->simulation->is_simulation_running = FALSE;                // Define que a simulação não está rodando
        g_timer_stop(app->variables->simulation->timer);                          // Para o timer
        app->variables->simulation->last_time = app->variables->simulation->time; // Define o tempo decorrido como o tempo total
    }

    gtk_widget_queue_draw(drawing_area); // Redesenha a área de desenho

    return TRUE; // Retorna TRUE (para continuar chamando o timeout)
}

void on_window_dynamic_destroy(GtkWidget *widget) // Quando a janela de simulação dinâmica for fechada
{
    variables_simulation_wipe(app->variables->simulation); // Limpa as variáveis de simulação
    gtk_widget_destroy(app->window_simulation->window);    // Destroi a janela de simulação
}

void on_dynamic_refresh_button_clicked(GtkButton *button) // Quando o botão de atualizar da simulação cinemática é clicado
{
    app->variables->simulation->is_simulation_running = FALSE; // Para a simulação
    if (app->variables->simulation->timer != NULL)             // Se o timer não for nulo
    {
        g_timer_stop(app->variables->simulation->timer); // Para o timer
    }
    app->variables->simulation->last_time = 0;                                                                 // Reseta o tempo
    Particle_Dynamic_Collection particle_collection = app->variables->simulation->particle_dynamic_collection; // Pega a coleção de partículas
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)                                    // Para cada partícula
    {
        Particle_Dynamic particle = particle_collection->particles[i]; // Pega a partícula
        // Reseta os valores da partícula
        particle->position->x = particle->position_i->x;
        particle->position->y = particle->position_i->y;
        particle->acceleration->x = particle->acceleration_i->x;
        particle->acceleration->y = particle->acceleration_i->y;
    }
    gtk_widget_queue_draw(app->window_simulation->drawing_area); // Redesenha a área de desenho
}

void forces_dynamic_apply() // Aplica as forças na simulação dinâmica
{
    Particle_Dynamic_Collection particle_collection = app->variables->simulation->particle_dynamic_collection; // Pega a coleção de partículas
    for (int i = 0; i < app->variables->simulation->num_particles_use; i++)                                    // Para cada partícula
    {
        Particle_Dynamic particle = particle_collection->particles[i]; // Pega a partícula
        GList *forces = particle->forces;                              // Pega as forças da partícula
        // Reseta os valores da partícula
        particle->acceleration->x = 0;
        particle->acceleration->y = 0;
        particle->force_resultant->x = 0;
        particle->force_resultant->y = 0;
        // Aplica a aceleração inicial
        particle->acceleration->x += particle->acceleration_i->x;
        particle->acceleration->y += particle->acceleration_i->y;
        // Aplica a força resultante
        for (GList *l = forces; l != NULL; l = l->next) // Para cada força
        {
            Vector force = l->data;                   // Pega a força
            particle->force_resultant->x += force->x; // Adiciona a força x à força resultante x
            particle->force_resultant->y += force->y; // Adiciona a força y à força resultante y
        }
        particle->acceleration->x += phyd_acceleration(particle->force_resultant->x, particle->mass);      // Aplica a aceleração x com a força resultante x
        particle->acceleration->y += phyd_acceleration(particle->force_resultant->y, particle->mass);      // Aplica a aceleração y com a força resultante y
        particle->acceleration->y -= app->variables->simulation->gravity;                                  // Aplica a aceleração y com a gravidade
        particle->force_resultant->y -= phyd_force_p(particle->mass, app->variables->simulation->gravity); // Aplica a força resultante y com a força peso
    }
}

void on_dynamic_start_button_clicked(GtkButton *button) // Quando o botão de iniciar da simulação cinemática é clicado
{
    if (!app->variables->simulation->is_simulation_running) // Se a simulação não estiver rodando
    {
        // Pega os valores dos spin buttons
        app->variables->simulation->gravity = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->gravity));
        app->variables->simulation->time_step = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->step));
        app->variables->simulation->time = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->time));
        app->variables->simulation->frames = gtk_spin_button_get_value(GTK_SPIN_BUTTON(app->window_simulation->spin_buttons->frames));
        forces_dynamic_apply(); // Aplica as forças

        // Salva o log da simulação (se os valores mudarem, nesse caso são verificados os caches de gravidade, tempo e passo de tempo)
        if (app->variables->simulation->firts_time || app->variables->simulation->gravity != app->variables->simulation->gravity_cache || app->variables->simulation->time_step != app->variables->simulation->time_step_cache || app->variables->simulation->time != app->variables->simulation->time_cache)
        {
            save_simulation_dynamic_log(app->variables->simulation->particle_dynamic_collection, app->variables->simulation->time, app->variables->simulation->time_step, app->variables->simulation->gravity);
        }

        // Atualiza os caches
        app->variables->simulation->firts_time = FALSE;
        app->variables->simulation->gravity_cache = app->variables->simulation->gravity;
        app->variables->simulation->time_cache = app->variables->simulation->time;
        app->variables->simulation->time_step_cache = app->variables->simulation->time_step;

        // Cria o timer
        if (app->variables->simulation->timer == NULL) // Se o timer for nulo
        {
            app->variables->simulation->timer = g_timer_new(); // Cria um novo timer
        }

        // Inicia o timer
        if (app->variables->simulation->last_time == 0) // Se for a primeira vez
        {
            g_timer_start(app->variables->simulation->timer); // Inicia o timer
        }
        else // Se não for a primeira vez
        {
            g_timer_continue(app->variables->simulation->timer); // Continua o timer
        }

        app->variables->simulation->is_simulation_running = TRUE; // Define que a simulação está rodando

        int timeout_interval = (int)(1000 / app->variables->simulation->frames);                   // Define o intervalo de tempo (em milissegundos)
        g_timeout_add(timeout_interval, on_timeout_dynamic, app->window_simulation->drawing_area); // Adiciona um timeout
    }
}

void on_dynamic_stop_button_clicked(GtkButton *button) // Quando o botão de parar da simulação dinâmica é clicado
{
    if (app->variables->simulation->is_simulation_running) // Se a simulação estiver rodando
    {
        app->variables->simulation->is_simulation_running = FALSE; // Define que a simulação não está rodando
        g_timer_stop(app->variables->simulation->timer);           // Para o timer
    }
}

void run_simulation_dynamic() // Inicia a simulacao de dinâmica
{
    particle_dynamic_collection_start();                 // Inicia a coleção de partículas dinâmicas
    create_window_simulation_widgets(DYNAMIC);                 // Cria os widgets da janela de simulação
    gtk_widget_show_all(app->window_simulation->window); // Mostra a janela de simulação
}