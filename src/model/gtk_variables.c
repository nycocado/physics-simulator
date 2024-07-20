#include "../include/gtk_include_all.h"

Variables variables_new() // Função de criação das variáveis
{
    Variables variables = g_slice_new(struct _Variables); // Aloca memória para as variáveis
    // Inicializa as variáveis
    variables->project = variables_project_new();
    variables->simulation = variables_simulation_new();
    variables->window_size = window_size_new();
    return variables;
}

void variables_free(Variables variables) // Função de liberação das variáveis
{
    variables_project_free(variables->project);
    variables_simulation_free(variables->simulation);
    window_size_free(variables->window_size);
    g_slice_free(struct _Variables, variables);
}

Variables_Simulation variables_simulation_new() // Função de criação das variáveis de simulação
{
    Variables_Simulation variables_simulation = g_slice_new(struct _Variables_Simulation); // Aloca memória para as variáveis de simulação
    // Inicializa as variáveis de simulação
    variables_simulation->is_simulation_running = FALSE;
    variables_simulation->num_particles_use = 0;
    variables_simulation->particle_cinematic_collection = NULL;
    variables_simulation->particle_dynamic_collection = NULL;
    variables_simulation->gravity = 0;
    variables_simulation->time = 0;
    variables_simulation->time_step = 0;
    variables_simulation->gravity_cache = 0;
    variables_simulation->time_cache = 0;
    variables_simulation->time_step_cache = 0;
    variables_simulation->frames = 0;
    variables_simulation->timer = NULL;
    variables_simulation->last_time = 0;
    variables_simulation->firts_time = TRUE;
    return variables_simulation;
}

void variables_simulation_wipe(Variables_Simulation variables_simulation) // Função de limpeza das variáveis de simulação
{
    if (variables_simulation->particle_cinematic_collection != NULL) // Se a coleção de partículas cinemáticas não for nula
    {
        particle_cinematic_collection_free(variables_simulation->particle_cinematic_collection); // Libera a coleção de partículas cinemáticas
    }
    if (variables_simulation->particle_dynamic_collection != NULL) // Se a coleção de partículas dinâmicas não for nula
    {
        particle_dynamic_collection_free(variables_simulation->particle_dynamic_collection); // Libera a coleção de partículas dinâmicas
    }
    if (variables_simulation->timer != NULL) // Se o temporizador não for nulo
    {
        g_timer_stop(variables_simulation->timer);    // Para o temporizador
        g_timer_destroy(variables_simulation->timer); // Destroi o temporizador
        variables_simulation->timer = NULL;           // Define o temporizador como nulo
    }
    // Define as variáveis de simulação como nulas ou zero
    variables_simulation->last_time = 0;
    variables_simulation->gravity_cache = 0;
    variables_simulation->time_cache = 0;
    variables_simulation->time_step_cache = 0;
    variables_simulation->gravity = 0;
    variables_simulation->time = 0;
    variables_simulation->time_step = 0;
    variables_simulation->frames = 0;
    variables_simulation->is_simulation_running = FALSE;
    variables_simulation->particle_cinematic_collection = NULL;
    variables_simulation->particle_dynamic_collection = NULL;
    variables_simulation->firts_time = TRUE;
}

void variables_simulation_free(Variables_Simulation variables_simulation) // Função de liberação das variáveis de simulação
{
    variables_simulation_wipe(variables_simulation);
    g_slice_free(struct _Variables_Simulation, variables_simulation);
}

Variables_Project variables_project_new() // Função de criação das variáveis do projeto
{
    Variables_Project variables_project = g_slice_new(struct _Variables_Project); // Aloca memória para as variáveis do projeto\
    // Inicializa as variáveis do projeto
    variables_project->file_path = NULL;
    variables_project->is_file_open = FALSE;
    return variables_project;
}

void variables_project_wipe(Variables_Project variables_project) // Função de limpeza das variáveis do projeto
{
    if (variables_project->file_path != NULL) // Se o caminho do arquivo não for nulo
    {
        g_free(variables_project->file_path); // Libera o caminho do arquivo
    }
    // Define as variáveis do projeto como nulas
    variables_project->file_path = NULL;
    variables_project->is_file_open = FALSE;
}

void variables_project_free(Variables_Project variables_project) // Função de liberação das variáveis do projeto
{
    variables_project_wipe(variables_project);
    g_slice_free(struct _Variables_Project, variables_project);
}

Window_Size window_size_new() // Função de criação do tamanho da janela
{
    Window_Size window_size = g_slice_new(struct _Window_Size); // Aloca memória para o tamanho da janela
    // Inicializa o tamanho da janela
    window_size->width = 0;
    window_size->height = 0;
    return window_size;
}

void window_size_free(Window_Size window_size) // Função de liberação do tamanho da janela
{
    g_slice_free(struct _Window_Size, window_size);
}