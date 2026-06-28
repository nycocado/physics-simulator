#pragma once

#include "gtk_include_all.h"

void set_columns_attribute();
void gtk_response_projetos_abrir(GtkDialog* dialog, gint response_id);
void gtk_response_projetos_novo(GtkDialog* dialog, gint response_id);
int run_gtk(int argc, char* argv[]);