#pragma once

#include <gtk/gtk.h> // Inclui as bibliotecas do GTK

// Declaração dos ponteiros das janelas de simulação
typedef struct _Window_Simulation *Window_Simulation;
typedef struct _Spin_Buttons_Simulation *Spin_Buttons_Simulation;
typedef struct _Buttons_Simulation *Buttons_Simulation;

struct _Window_Simulation // Estrutura da janela de simulação
{
    GtkWidget *window;
    GtkWidget *drawing_area;
    Spin_Buttons_Simulation spin_buttons;
    Buttons_Simulation buttons;
};

struct _Spin_Buttons_Simulation // Estrutura dos botões de rotação da simulação
{
    GtkWidget *gravity;
    GtkWidget *time;
    GtkWidget *step;
    GtkWidget *frames;
};

struct _Buttons_Simulation // Estrutura dos botões da simulação
{
    GtkWidget *start;
    GtkWidget *stop;
    GtkWidget *refresh;
};

Window_Simulation window_simulation_new(); // Função de criação da janela de simulação
void window_simulation_free(Window_Simulation window_simulation); // Função de liberação da janela de simulação
Spin_Buttons_Simulation spin_buttons_simulation_new(); // Função de criação dos botões de simulação
void spin_buttons_simulation_free(Spin_Buttons_Simulation spin_buttons); // Função de liberação dos botões de simulação
Buttons_Simulation buttons_simulation_new(); // Função de criação dos botões de simulação
void buttons_simulation_free(Buttons_Simulation buttons); // Função de liberação dos botões de simulação