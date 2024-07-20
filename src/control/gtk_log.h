#pragma once

#include <gtk/gtk.h>                // Inclui as bibliotecas do GTK
#include "../model/gtk_variables.h" // Inclui as bibliotecas das partículas

char *generate_log_name_for_simulation(const char *base_name);                                                                     // Função de gerar o nome do log da simulação
void replace_dot_with_comma(char *str);                                                                                            // Função de substituir ponto por vírgula
void save_simulation_cinematic_log(Particle_Cinematic_Collection particle_collection, float time, float time_step, float gravity); // Função de salvar o log da simulação cinemática
int calc_num_forces_max(Particle_Dynamic_Collection particle_collection);                                                          // Função de calcular o número total de forças
void save_simulation_dynamic_log(Particle_Dynamic_Collection particle_collection, float time, float time_step, float gravity);     // Função de salvar o log da simulação dinâmica