CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -I$(SRC_DIR) -DUNITY_INCLUDE_DOUBLE
GTKFLAGS = `pkg-config --cflags --libs gtk4` -rdynamic
MATHFLAGS = -lm
GLIBFLAGS = `pkg-config --cflags --libs glib-2.0`
BIN_DIR = bin
BIN_TEST = bin/test
BIN_BUILD = bin/build
SRC_DIR = src
TEST_DIR = test
UNITY_DIR = test/unity
UI_DIR = src/ui/windows
BLP_FILES = $(wildcard $(UI_DIR)/*.blp)
UI_FILES = $(BLP_FILES:.blp=.ui)

_BUILD_BIN::=$(shell mkdir -p $(BIN_DIR))
_BUILD_TESTS_BIN::=$(shell mkdir -p $(BIN_TEST))
_BUILD_BUILD_BIN::=$(shell mkdir -p $(BIN_BUILD))

ALL_OBJS = $(BIN_DIR)/run.o \
           $(BIN_DIR)/app.o $(BIN_DIR)/variables.o \
           $(BIN_DIR)/project.o $(BIN_DIR)/log.o $(BIN_DIR)/collection.o \
           $(BIN_DIR)/particles/buttons.o $(BIN_DIR)/particles/particle.o \
           $(BIN_DIR)/particles/force_dialog.o $(BIN_DIR)/particles/particle_dialog.o \
           $(BIN_DIR)/physics/kinematics.o $(BIN_DIR)/physics/dynamics.o \
           $(BIN_DIR)/simulation/simulation.o $(BIN_DIR)/simulation/kinematic_sim.o \
           $(BIN_DIR)/simulation/dynamic_sim.o \
           $(BIN_DIR)/ui/builder.o $(BIN_DIR)/ui/callbacks.o \
           $(BIN_DIR)/ui/main_window.o $(BIN_DIR)/ui/window_main.o \
           $(BIN_DIR)/ui/window_simulation.o

_MAKE_SUBDIRS::=$(shell mkdir -p $(BIN_DIR)/particles $(BIN_DIR)/physics $(BIN_DIR)/simulation $(BIN_DIR)/ui)

$(BIN_DIR)/run.o: $(SRC_DIR)/run.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/run.c $(GTKFLAGS) -o $(BIN_DIR)/run.o

$(BIN_DIR)/app.o: $(SRC_DIR)/app.c $(SRC_DIR)/app.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/app.c $(GTKFLAGS) -o $(BIN_DIR)/app.o

$(BIN_DIR)/variables.o: $(SRC_DIR)/variables.c $(SRC_DIR)/variables.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/variables.c $(GTKFLAGS) -o $(BIN_DIR)/variables.o

$(BIN_DIR)/project.o: $(SRC_DIR)/project.c $(SRC_DIR)/project.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/project.c $(GTKFLAGS) -o $(BIN_DIR)/project.o

$(BIN_DIR)/log.o: $(SRC_DIR)/log.c $(SRC_DIR)/log.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/log.c $(GTKFLAGS) -o $(BIN_DIR)/log.o

$(BIN_DIR)/collection.o: $(SRC_DIR)/collection.c $(SRC_DIR)/collection.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/collection.c $(GTKFLAGS) -o $(BIN_DIR)/collection.o

$(BIN_DIR)/particles/buttons.o: $(SRC_DIR)/particles/buttons.c $(SRC_DIR)/particles/buttons.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/particles/buttons.c $(GTKFLAGS) -o $(BIN_DIR)/particles/buttons.o

$(BIN_DIR)/particles/particle.o: $(SRC_DIR)/particles/particle.c $(SRC_DIR)/particles/particle.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/particles/particle.c $(GTKFLAGS) -o $(BIN_DIR)/particles/particle.o

$(BIN_DIR)/particles/force_dialog.o: $(SRC_DIR)/particles/force_dialog.c $(SRC_DIR)/particles/force_dialog.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/particles/force_dialog.c $(GTKFLAGS) -o $(BIN_DIR)/particles/force_dialog.o

$(BIN_DIR)/particles/particle_dialog.o: $(SRC_DIR)/particles/particle_dialog.c $(SRC_DIR)/particles/particle_dialog.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/particles/particle_dialog.c $(GTKFLAGS) -o $(BIN_DIR)/particles/particle_dialog.o

$(BIN_DIR)/physics/kinematics.o: $(SRC_DIR)/physics/kinematics.c $(SRC_DIR)/physics/kinematics.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/physics/kinematics.c $(GTKFLAGS) -o $(BIN_DIR)/physics/kinematics.o

$(BIN_DIR)/physics/dynamics.o: $(SRC_DIR)/physics/dynamics.c $(SRC_DIR)/physics/dynamics.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/physics/dynamics.c $(GTKFLAGS) -o $(BIN_DIR)/physics/dynamics.o

$(BIN_DIR)/simulation/simulation.o: $(SRC_DIR)/simulation/simulation.c $(SRC_DIR)/simulation/simulation.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/simulation/simulation.c $(GTKFLAGS) -o $(BIN_DIR)/simulation/simulation.o

$(BIN_DIR)/simulation/kinematic_sim.o: $(SRC_DIR)/simulation/kinematic_sim.c $(SRC_DIR)/simulation/kinematic_sim.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/simulation/kinematic_sim.c $(GTKFLAGS) -o $(BIN_DIR)/simulation/kinematic_sim.o

$(BIN_DIR)/simulation/dynamic_sim.o: $(SRC_DIR)/simulation/dynamic_sim.c $(SRC_DIR)/simulation/dynamic_sim.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/simulation/dynamic_sim.c $(GTKFLAGS) -o $(BIN_DIR)/simulation/dynamic_sim.o

$(BIN_DIR)/ui/builder.o: $(SRC_DIR)/ui/builder.c $(SRC_DIR)/ui/builder.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ui/builder.c $(GTKFLAGS) -o $(BIN_DIR)/ui/builder.o

$(BIN_DIR)/ui/callbacks.o: $(SRC_DIR)/ui/callbacks.c $(SRC_DIR)/ui/callbacks.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ui/callbacks.c $(GTKFLAGS) -o $(BIN_DIR)/ui/callbacks.o

$(BIN_DIR)/ui/main_window.o: $(SRC_DIR)/ui/main_window.c $(SRC_DIR)/ui/main_window.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ui/main_window.c $(GTKFLAGS) -o $(BIN_DIR)/ui/main_window.o

$(BIN_DIR)/ui/window_main.o: $(SRC_DIR)/ui/window_main.c $(SRC_DIR)/ui/window_main.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ui/window_main.c $(GTKFLAGS) -o $(BIN_DIR)/ui/window_main.o

$(BIN_DIR)/ui/window_simulation.o: $(SRC_DIR)/ui/window_simulation.c $(SRC_DIR)/ui/window_simulation.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ui/window_simulation.c $(GTKFLAGS) -o $(BIN_DIR)/ui/window_simulation.o

unity.o:
	$(CC) $(CFLAGS) -c $(UNITY_DIR)/unity.c $(GTKFLAGS) -o $(BIN_DIR)/unity.o

$(BIN_DIR)/physics/kinematics_test.o: $(SRC_DIR)/physics/kinematics.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/physics/kinematics.c $(MATHFLAGS) -o $(BIN_DIR)/physics/kinematics_test.o

$(BIN_DIR)/physics/dynamics_test.o: $(SRC_DIR)/physics/dynamics.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/physics/dynamics.c $(MATHFLAGS) -o $(BIN_DIR)/physics/dynamics_test.o

phy_tests: unity.o $(BIN_DIR)/physics/kinematics_test.o $(BIN_DIR)/physics/dynamics_test.o
	$(CC) $(CFLAGS) $(TEST_DIR)/phy_tests.c $(BIN_DIR)/unity.o \
	  $(BIN_DIR)/physics/kinematics_test.o $(BIN_DIR)/physics/dynamics_test.o \
	  $(MATHFLAGS) -o $(BIN_TEST)/phy_tests

test_simulation: unity.o $(BIN_DIR)/physics/kinematics_test.o $(BIN_DIR)/physics/dynamics_test.o
	$(CC) $(CFLAGS) $(TEST_DIR)/test_simulation.c $(BIN_DIR)/unity.o \
	  $(BIN_DIR)/physics/kinematics_test.o $(BIN_DIR)/physics/dynamics_test.o \
	  $(MATHFLAGS) -o $(BIN_TEST)/test_simulation

test_locale: unity.o
	$(CC) $(CFLAGS) $(TEST_DIR)/test_locale.c $(BIN_DIR)/unity.o $(GLIBFLAGS) -o $(BIN_TEST)/test_locale

test_validation: unity.o
	$(CC) $(CFLAGS) $(TEST_DIR)/test_validation.c $(BIN_DIR)/unity.o $(GLIBFLAGS) -o $(BIN_TEST)/test_validation

$(UI_DIR)/%.ui: $(UI_DIR)/%.blp
	blueprint-compiler compile --output $@ $<

blueprint: $(UI_FILES)

comp: blueprint $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) $(GTKFLAGS) -o $(BIN_BUILD)/simulation_physic $(MATHFLAGS)

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
	rm -f $(UI_FILES)
