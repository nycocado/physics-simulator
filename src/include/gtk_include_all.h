#pragma once

#include <gtk/gtk.h> // Inclui todas as bibliotecas do GTK
#include <cairo.h>   // Inclui a biblioteca do Cairo
#include <stdlib.h>  // Inclui a biblioteca padrão
#include <math.h>    // Inclui a biblioteca matemática

#define CINEMATIC 1 // Define o valor de cinemática
#define DYNAMIC 2   // Define o valor de dinâmica

#include "gtk_callbacks.h"        // Inclui os callbacks do GTK
#include "gtk_create_window.h"    // Inclui as funções de criação de janelas
#include "gtk_main.h"             // Inclui a função principal do GTK
#include "simulation_cinematic.h" // Inclui as funções de simulação cinemática
#include "simulation_dynamic.h"   // Inclui as funções de simulação dinâmica
#include "simulation_commun.h"    // Inclui as funções de simulação comuns

// Objetos:
#include "../model/gtk_app.h"                              // Inclui a aplicação GTK
#include "../model/gtk_button_add.h"                       // Inclui o botão de adição
#include "../model/gtk_button_edit.h"                      // Inclui o botão de edição
#include "../model/gtk_spin_buttons_add_force_normal.h"    // Inclui os spin buttons de adição de força
#include "../model/gtk_spin_buttons_add_particle_normal.h" // Inclui os spin buttons de adição de partícula
#include "../model/gtk_variables.h"                        // Inclui as variáveis do GTK
#include "../model/gtk_window_add_force_normal.h"          // Inclui a janela de adição de força
#include "../model/gtk_window_add_particle_normal.h"       // Inclui a janela de adição de partícula
#include "../model/gtk_window_simulation.h"                // Inclui a janela de simulação
#include "../model/gtk_window_edit_force_normal.h"         // Inclui a janela de edição de força
#include "../model/gtk_window_edit_particle_normal.h"      // Inclui a janela de edição de partícula
#include "../model/gtk_window_main.h"                      // Inclui a janela principal
#include "../model/particle.h"                             // Inclui a partícula
#include "../model/phy_forms_cinematics.h"                 // Inclui as formas cinemáticas
#include "../model/phy_forms_dynamics.h"                   // Inclui as formas dinâmicas

#include "../control/gtk_project.h"    // Inclui as funções de projeto
#include "../control/gtk_log.h"        // Inclui as funções de log
#include "../control/gtk_collection.h" // Inclui as funções de coleção