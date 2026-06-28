CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g
GTKFLAGS = `pkg-config --cflags --libs gtk+-3.0` -rdynamic
MATHFLAGS = -lm
GLIBFLAGS = `pkg-config --cflags --libs glib-2.0`
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

VIEW_OBJS = $(BIN_DIR)/main_window.o $(BIN_DIR)/callbacks.o $(BIN_DIR)/builder.o \
            $(BIN_DIR)/simulation_cinematic.o $(BIN_DIR)/simulation_dynamic.o $(BIN_DIR)/simulation_commun.o

MODEL_OBJS = $(BIN_DIR)/app.o $(BIN_DIR)/buttons.o \
             $(BIN_DIR)/force_dialog.o $(BIN_DIR)/particle_dialog.o \
             $(BIN_DIR)/variables.o $(BIN_DIR)/window_simulation.o \
             $(BIN_DIR)/window_main.o $(BIN_DIR)/particle.o \
             $(BIN_DIR)/phy_forms_cinematics.o $(BIN_DIR)/phy_forms_dynamics.o

CONTROL_OBJS = $(BIN_DIR)/project.o $(BIN_DIR)/log.o $(BIN_DIR)/collection.o

VIEW_OBJS_COMP = main_window.o callbacks.o builder.o simulation_cinematic.o simulation_dynamic.o simulation_commun.o

MODEL_OBJS_COMP = app.o buttons.o force_dialog.o particle_dialog.o variables.o window_simulation.o window_main.o particle.o phy_forms_cinematics.o phy_forms_dynamics.o

CONTROL_OBJS_COMP = project.o log.o collection.o

run.o: $(SRC_DIR)/run.c main_window.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/run.c $(GTKFLAGS) -o $(BIN_DIR)/run.o

main_window.o: $(VIEW_DIR)/main_window.c $(INCLUDE_DIR)/main_window.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/main_window.c $(GTKFLAGS) -o $(BIN_DIR)/main_window.o

callbacks.o: $(VIEW_DIR)/callbacks.c $(INCLUDE_DIR)/callbacks.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/callbacks.c $(GTKFLAGS) -o $(BIN_DIR)/callbacks.o

builder.o: $(VIEW_DIR)/builder.c $(INCLUDE_DIR)/builder.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/builder.c $(GTKFLAGS) -o $(BIN_DIR)/builder.o

simulation_cinematic.o: $(VIEW_DIR)/simulation_cinematic.c $(INCLUDE_DIR)/simulation_cinematic.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/simulation_cinematic.c $(GTKFLAGS) -o $(BIN_DIR)/simulation_cinematic.o

simulation_dynamic.o: $(VIEW_DIR)/simulation_dynamic.c $(INCLUDE_DIR)/simulation_dynamic.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/simulation_dynamic.c $(GTKFLAGS) -o $(BIN_DIR)/simulation_dynamic.o

simulation_commun.o: $(VIEW_DIR)/simulation_commun.c $(INCLUDE_DIR)/simulation_commun.h
	$(CC) $(CFLAGS) -c $(VIEW_DIR)/simulation_commun.c $(GTKFLAGS) -o $(BIN_DIR)/simulation_commun.o

app.o: $(MODEL_DIR)/app.c $(MODEL_DIR)/app.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/app.c $(GTKFLAGS) -o $(BIN_DIR)/app.o

buttons.o: $(MODEL_DIR)/buttons.c $(MODEL_DIR)/buttons.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/buttons.c $(GTKFLAGS) -o $(BIN_DIR)/buttons.o

force_dialog.o: $(MODEL_DIR)/force_dialog.c $(MODEL_DIR)/force_dialog.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/force_dialog.c $(GTKFLAGS) -o $(BIN_DIR)/force_dialog.o

particle_dialog.o: $(MODEL_DIR)/particle_dialog.c $(MODEL_DIR)/particle_dialog.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/particle_dialog.c $(GTKFLAGS) -o $(BIN_DIR)/particle_dialog.o

variables.o: $(MODEL_DIR)/variables.c $(MODEL_DIR)/variables.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/variables.c $(GTKFLAGS) -o $(BIN_DIR)/variables.o

window_simulation.o: $(MODEL_DIR)/window_simulation.c $(MODEL_DIR)/window_simulation.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/window_simulation.c $(GTKFLAGS) -o $(BIN_DIR)/window_simulation.o

window_main.o: $(MODEL_DIR)/window_main.c $(MODEL_DIR)/window_main.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/window_main.c $(GTKFLAGS) -o $(BIN_DIR)/window_main.o

particle.o: $(MODEL_DIR)/particle.c $(MODEL_DIR)/particle.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/particle.c $(GTKFLAGS) -o $(BIN_DIR)/particle.o

project.o: $(CONTROL_DIR)/project.c $(CONTROL_DIR)/project.h
	$(CC) $(CFLAGS) -c $(CONTROL_DIR)/project.c $(GTKFLAGS) -o $(BIN_DIR)/project.o

log.o: $(CONTROL_DIR)/log.c $(CONTROL_DIR)/log.h
	$(CC) $(CFLAGS) -c $(CONTROL_DIR)/log.c $(GTKFLAGS) -o $(BIN_DIR)/log.o

collection.o: $(CONTROL_DIR)/collection.c $(CONTROL_DIR)/collection.h
	$(CC) $(CFLAGS) -c $(CONTROL_DIR)/collection.c $(GTKFLAGS) -o $(BIN_DIR)/collection.o

phy_forms_cinematics.o: $(MODEL_DIR)/phy_forms_cinematics.c $(MODEL_DIR)/phy_forms_cinematics.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/phy_forms_cinematics.c $(GTKFLAGS) -o $(BIN_DIR)/phy_forms_cinematics.o

phy_forms_dynamics.o: $(MODEL_DIR)/phy_forms_dynamics.c $(MODEL_DIR)/phy_forms_dynamics.h
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/phy_forms_dynamics.c $(GTKFLAGS) -o $(BIN_DIR)/phy_forms_dynamics.o

unity.o:
	$(CC) $(CFLAGS) -c $(UNITY_DIR)/unity.c $(GTKFLAGS) -o $(BIN_DIR)/unity.o

phy_tests: unity.o phy_forms_cinematics.o phy_forms_dynamics.o
	$(CC) $(CFLAGS) $(TEST_DIR)/phy_tests.c $(BIN_DIR)/unity.o $(BIN_DIR)/phy_forms_cinematics.o $(BIN_DIR)/phy_forms_dynamics.o $(GTKFLAGS) -o $(BIN_TEST)/phy_tests $(MATHFLAGS)

test_simulation: unity.o phy_forms_cinematics.o phy_forms_dynamics.o
	$(CC) $(CFLAGS) $(TEST_DIR)/test_simulation.c $(BIN_DIR)/unity.o $(BIN_DIR)/phy_forms_cinematics.o $(BIN_DIR)/phy_forms_dynamics.o $(GTKFLAGS) -o $(BIN_TEST)/test_simulation $(MATHFLAGS)

test_locale: unity.o
	$(CC) $(CFLAGS) $(TEST_DIR)/test_locale.c $(BIN_DIR)/unity.o $(GLIBFLAGS) -o $(BIN_TEST)/test_locale

test_validation: unity.o
	$(CC) $(CFLAGS) $(TEST_DIR)/test_validation.c $(BIN_DIR)/unity.o $(GLIBFLAGS) -o $(BIN_TEST)/test_validation

comp: run.o $(VIEW_OBJS_COMP) $(MODEL_OBJS_COMP) $(CONTROL_OBJS_COMP)
	$(CC) $(CFLAGS) $(BIN_DIR)/run.o $(VIEW_OBJS) $(MODEL_OBJS) $(CONTROL_OBJS) $(GTKFLAGS) -o $(BIN_BUILD)/simulation_physic $(MATHFLAGS)

run: comp
	$(BIN_BUILD)/simulation_physic

phy_test: phy_tests
	$(BIN_TEST)/phy_tests

simulation_test: test_simulation
	$(BIN_TEST)/test_simulation

locale_test: test_locale
	$(BIN_TEST)/test_locale

validation_test: test_validation
	$(BIN_TEST)/test_validation

all_tests: phy_test simulation_test locale_test validation_test

valgrind: comp
	valgrind --leak-check=full $(BIN_BUILD)/simulation_physic

clean:
	rm -rf $(BIN_DIR)
