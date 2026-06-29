#pragma once

#include "gtk_include_all.h"

void set_columns_attribute(GtkApp app);
void gtk_response_projetos_abrir(GtkDialog* dialog, gint response_id, gpointer data);
void gtk_response_projetos_novo(GtkDialog* dialog, gint response_id, gpointer data);
int run_gtk(int argc, char* argv[], GtkApp app);
