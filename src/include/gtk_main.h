#pragma once

#include "gtk_include_all.h"

void set_columns_attribute();                                          // Define as configurações das colunas da tabela
void gtk_response_projetos_abrir(GtkDialog *dialog, gint response_id); // Função de resposta do diálogo de abrir projeto
void gtk_response_projetos_novo(GtkDialog *dialog, gint response_id);  // Função de resposta do diálogo de novo projeto
int run_gtk(int argc, char *argv[]);                                   // Função principal do GTK