#include "../include/gtk_include_all.h"

Window_Simulation window_simulation_new() // Função de criação da janela de simulação
{
    Window_Simulation window_simulation = g_slice_new(struct _Window_Simulation); // Aloca memória para a janela de simulação
    window_simulation->window = NULL;
    window_simulation->drawing_area = NULL;
    window_simulation->buttons = buttons_simulation_new();
    window_simulation->spin_buttons = spin_buttons_simulation_new();
    return window_simulation;
}

void window_simulation_free(Window_Simulation window_simulation) // Função de liberação da janela de simulação
{
    buttons_simulation_free(window_simulation->buttons);
    spin_buttons_simulation_free(window_simulation->spin_buttons);
    g_slice_free(struct _Window_Simulation, window_simulation);
}

Spin_Buttons_Simulation spin_buttons_simulation_new() // Função de criação dos botões de simulação
{
    Spin_Buttons_Simulation spin_buttons = g_slice_new(struct _Spin_Buttons_Simulation); // Aloca memória para os botões de simulação
    // Inicializa os botões de simulação
    spin_buttons->gravity = NULL;
    spin_buttons->time = NULL;
    spin_buttons->step = NULL;
    spin_buttons->frames = NULL;
    return spin_buttons;
}

void spin_buttons_simulation_free(Spin_Buttons_Simulation spin_buttons) // Função de liberação dos botões de simulação
{
    g_slice_free(struct _Spin_Buttons_Simulation, spin_buttons);
}

Buttons_Simulation buttons_simulation_new() // Função de criação dos botões de simulação
{
    Buttons_Simulation buttons = g_slice_new(struct _Buttons_Simulation); // Aloca memória para os botões de simulação
    // Inicializa os botões de simulação
    buttons->start = NULL;
    buttons->stop = NULL;
    buttons->refresh = NULL;
    return buttons;
}

void buttons_simulation_free(Buttons_Simulation buttons) // Função de liberação dos botões de simulação
{
    g_slice_free(struct _Buttons_Simulation, buttons);
}