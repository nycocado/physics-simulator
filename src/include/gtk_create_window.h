#pragma once

#include "gtk_include_all.h"

void create_window_main_widgets();
void create_window_add_particle_normal_widgets();
void create_window_add_force_normal_widgets();
void create_window_edit_particle_normal_widgets();
void create_window_edit_force_normal_widgets();
void create_window_simulation_widgets(int i);
void create_dialog_error_message(const gchar* message);