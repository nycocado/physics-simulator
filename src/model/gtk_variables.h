#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK
#include "particle.h" // Inclui as bibliotecas das partículas

// Declaração dos ponteiros das variáveis
typedef struct _Variables *Variables;
typedef struct _Variables_Simulation *Variables_Simulation;
typedef struct _Variables_Project *Variables_Project;
typedef struct _Window_Size *Window_Size;

struct _Variables // Estrutura das variáveis
{
    Variables_Simulation simulation;
    Variables_Project project;
    Window_Size window_size;
};

struct _Variables_Simulation // Estrutura das variáveis de simulação
{
    gboolean is_simulation_running;
    int num_particles_use;
    Particle_Cinematic_Collection particle_cinematic_collection;
    Particle_Dynamic_Collection particle_dynamic_collection;
    float gravity;
    float time;
    float time_step;
    float gravity_cache;
    float time_cache;
    float time_step_cache;
    float frames;
    float last_time;
    GTimer *timer;
    gboolean firts_time;
};

struct _Variables_Project // Estrutura das variáveis do projeto
{
    gchar *file_path;
    gboolean is_file_open;
};

struct _Window_Size // Estrutura do tamanho da janela
{
    int width;
    int height;
};

Variables variables_new();                                                 // Função de criação das variáveis
void variables_free(Variables variables);                                  // Função de liberação das variáveis
Variables_Simulation variables_simulation_new();                           // Função de criação das variáveis de simulação
void variables_simulation_wipe(Variables_Simulation variables_simulation); // Função de limpeza das variáveis de simulação
void variables_simulation_free(Variables_Simulation variables_simulation); // Função de liberação das variáveis de simulação
Variables_Project variables_project_new();                                 // Função de criação das variáveis do projeto
void variables_project_wipe(Variables_Project variables_project);          // Função de limpeza das variáveis do projeto
void variables_project_free(Variables_Project variables_project);          // Função de liberação das variáveis do projeto
Window_Size window_size_new();                                             // Função de criação do tamanho da janela
void window_size_free(Window_Size window_size);                            // Função de liberação do tamanho da janela