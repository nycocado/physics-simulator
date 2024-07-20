CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g # Os únicos warnings que estão dando, é variaveis inutilizadas, mas é por causa da forma como o GTK é estruturado, então não é um problema
GTKFLAGS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic
MATHFLAGS = -lm
BIN_DIR = bin
BIN_TEST = bin/test
BIN_BUILD = bin/build
SRC_DIR = src
VIEW_DIR = src/view
MODEL_DIR = src/model
CONTROL_DIR = src/control
INCLUDE_DIR = src/include
TEST_DIR = test
UNITY_DIR = test/unity

_BUILD_BIN::=$(shell mkdir -p $(BIN_DIR))
_BUILD_TESTS_BIN::=$(shell mkdir -p $(BIN_TEST))
_BUILD_BUILD_BIN::=$(shell mkdir -p $(BIN_BUILD))

VIEW_OBJS = $(BIN_DIR)/gtk_main.o $(BIN_DIR)/gtk_callbacks.o $(BIN_DIR)/gtk_create_window.o \
            $(BIN_DIR)/simulation_cinematic.o $(BIN_DIR)/simulation_dynamic.o $(BIN_DIR)/simulation_commun.o

MODEL_OBJS = $(BIN_DIR)/gtk_app.o $(BIN_DIR)/gtk_button_add.o $(BIN_DIR)/gtk_button_edit.o \
             $(BIN_DIR)/gtk_spin_buttons_add_force_normal.o $(BIN_DIR)/gtk_spin_buttons_add_particle_normal.o \
             $(BIN_DIR)/gtk_variables.o $(BIN_DIR)/gtk_window_add_force_normal.o \
             $(BIN_DIR)/gtk_window_add_particle_normal.o $(BIN_DIR)/gtk_window_simulation.o \
             $(BIN_DIR)/gtk_window_edit_force_normal.o $(BIN_DIR)/gtk_window_edit_particle_normal.o \
             $(BIN_DIR)/gtk_window_main.o $(BIN_DIR)/particle.o $(BIN_DIR)/phy_forms_cinematics.o \
             $(BIN_DIR)/phy_forms_dynamics.o

CONTROL_OBJS = $(BIN_DIR)/gtk_project.o $(BIN_DIR)/gtk_log.o $(BIN_DIR)/gtk_collection.o

VIEW_OBJS_COMP = gtk_main.o gtk_callbacks.o gtk_create_window.o simulation_cinematic.o simulation_dynamic.o simulation_commun.o

MODEL_OBJS_COMP = gtk_app.o gtk_button_add.o gtk_button_edit.o gtk_spin_buttons_add_force_normal.o gtk_spin_buttons_add_particle_normal.o gtk_variables.o gtk_window_add_force_normal.o gtk_window_add_particle_normal.o gtk_window_simulation.o gtk_window_edit_force_normal.o gtk_window_edit_particle_normal.o gtk_window_main.o particle.o phy_forms_cinematics.o phy_forms_dynamics.o

CONTROL_OBJS_COMP = gtk_project.o gtk_log.o gtk_collection.o

run.o: $(SRC_DIR)/run.c gtk_main.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/run.c $(GTKFLAGS) -o $(BIN_DIR)/run.o

gtk_main.o: $(VIEW_DIR)/gtk_main.c $(INCLUDE_DIR)/gtk_main.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/gtk_main.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_main.o

gtk_callbacks.o: $(VIEW_DIR)/gtk_callbacks.c $(INCLUDE_DIR)/gtk_callbacks.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/gtk_callbacks.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_callbacks.o

gtk_create_window.o: $(VIEW_DIR)/gtk_create_window.c $(INCLUDE_DIR)/gtk_create_window.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/gtk_create_window.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_create_window.o

simulation_cinematic.o: $(VIEW_DIR)/simulation_cinematic.c $(INCLUDE_DIR)/simulation_cinematic.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/simulation_cinematic.c $(GTKFLAGS) -o $(BIN_DIR)/simulation_cinematic.o

simulation_dynamic.o: $(VIEW_DIR)/simulation_dynamic.c $(INCLUDE_DIR)/simulation_dynamic.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/simulation_dynamic.c $(GTKFLAGS) -o $(BIN_DIR)/simulation_dynamic.o

simulation_commun.o: $(VIEW_DIR)/simulation_commun.c $(INCLUDE_DIR)/simulation_commun.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/simulation_commun.c $(GTKFLAGS) -o $(BIN_DIR)/simulation_commun.o

gtk_app.o: $(MODEL_DIR)/gtk_app.c $(MODEL_DIR)/gtk_app.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_app.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_app.o

gtk_button_add.o: $(MODEL_DIR)/gtk_button_add.c $(MODEL_DIR)/gtk_button_add.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_button_add.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_button_add.o

gtk_button_edit.o: $(MODEL_DIR)/gtk_button_edit.c $(MODEL_DIR)/gtk_button_edit.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_button_edit.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_button_edit.o

gtk_spin_buttons_add_force_normal.o: $(MODEL_DIR)/gtk_spin_buttons_add_force_normal.c $(MODEL_DIR)/gtk_spin_buttons_add_force_normal.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_spin_buttons_add_force_normal.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_spin_buttons_add_force_normal.o

gtk_spin_buttons_add_particle_normal.o: $(MODEL_DIR)/gtk_spin_buttons_add_particle_normal.c $(MODEL_DIR)/gtk_spin_buttons_add_particle_normal.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_spin_buttons_add_particle_normal.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_spin_buttons_add_particle_normal.o

gtk_variables.o: $(MODEL_DIR)/gtk_variables.c $(MODEL_DIR)/gtk_variables.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_variables.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_variables.o

gtk_window_add_force_normal.o: $(MODEL_DIR)/gtk_window_add_force_normal.c $(MODEL_DIR)/gtk_window_add_force_normal.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_window_add_force_normal.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_window_add_force_normal.o

gtk_window_add_particle_normal.o: $(MODEL_DIR)/gtk_window_add_particle_normal.c $(MODEL_DIR)/gtk_window_add_particle_normal.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_window_add_particle_normal.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_window_add_particle_normal.o

gtk_window_simulation.o: $(MODEL_DIR)/gtk_window_simulation.c $(MODEL_DIR)/gtk_window_simulation.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_window_simulation.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_window_simulation.o

gtk_window_edit_force_normal.o: $(MODEL_DIR)/gtk_window_edit_force_normal.c $(MODEL_DIR)/gtk_window_edit_force_normal.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_window_edit_force_normal.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_window_edit_force_normal.o

gtk_window_edit_particle_normal.o: $(MODEL_DIR)/gtk_window_edit_particle_normal.c $(MODEL_DIR)/gtk_window_edit_particle_normal.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_window_edit_particle_normal.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_window_edit_particle_normal.o

gtk_window_main.o: $(MODEL_DIR)/gtk_window_main.c $(MODEL_DIR)/gtk_window_main.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/gtk_window_main.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_window_main.o

particle.o: $(MODEL_DIR)/particle.c $(MODEL_DIR)/particle.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/particle.c $(GTKFLAGS) -o $(BIN_DIR)/particle.o

gtk_project.o: $(CONTROL_DIR)/gtk_project.c $(CONTROL_DIR)/gtk_project.h
	$(CC) $(CFLAGS) -c $(CONTROL_DIR)/gtk_project.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_project.o

gtk_log.o: $(CONTROL_DIR)/gtk_log.c $(CONTROL_DIR)/gtk_log.h
	$(CC) $(CFLAGS) -c $(CONTROL_DIR)/gtk_log.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_log.o

gtk_collection.o: $(CONTROL_DIR)/gtk_collection.c $(CONTROL_DIR)/gtk_collection.h
	$(CC) $(CFLAGS) -c $(CONTROL_DIR)/gtk_collection.c $(GTKFLAGS) -o $(BIN_DIR)/gtk_collection.o

phy_forms_cinematics.o: $(MODEL_DIR)/phy_forms_cinematics.c $(MODEL_DIR)/phy_forms_cinematics.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/phy_forms_cinematics.c $(GTKFLAGS) -o $(BIN_DIR)/phy_forms_cinematics.o

phy_forms_dynamics.o: $(MODEL_DIR)/phy_forms_dynamics.c $(MODEL_DIR)/phy_forms_dynamics.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/phy_forms_dynamics.c $(GTKFLAGS) -o $(BIN_DIR)/phy_forms_dynamics.o

unity.o:
	$(CC) $(CFLAGS) -c $(UNITY_DIR)/unity.c $(GTKFLAGS) -o $(BIN_DIR)/unity.o

phy_tests: unity.o phy_forms_cinematics.o phy_forms_dynamics.o
	$(CC) $(CFLAGS) $(TEST_DIR)/phy_tests.c $(BIN_DIR)/unity.o $(BIN_DIR)/phy_forms_cinematics.o $(BIN_DIR)/phy_forms_dynamics.o $(GTKFLAGS) -o $(BIN_TEST)/phy_tests $(MATHFLAGS)

comp: run.o $(VIEW_OBJS_COMP) $(MODEL_OBJS_COMP) $(CONTROL_OBJS_COMP)
	$(CC) $(CFLAGS) $(BIN_DIR)/run.o $(VIEW_OBJS) $(MODEL_OBJS) $(CONTROL_OBJS) $(GTKFLAGS) -o $(BIN_BUILD)/simulation_physic $(MATHFLAGS)

run: comp
	$(BIN_BUILD)/simulation_physic

phy_test: phy_tests
	$(BIN_TEST)/phy_tests

valgrind: comp
	valgrind --leak-check=full $(BIN_BUILD)/simulation_physic

clear:
	rm -rf $(BIN_DIR)