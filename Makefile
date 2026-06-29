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


SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

BLP_FILES = $(wildcard $(UI_DIR)/*.blp)
UI_FILES = $(BLP_FILES:.blp=.ui)


$(shell mkdir -p $(BIN_DIR) $(BIN_TEST) $(BIN_BUILD))


$(UI_DIR)/%.ui: $(UI_DIR)/%.blp
	blueprint-compiler compile --output $@ $<

blueprint: $(UI_FILES)


$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(GTKFLAGS) -o $@


comp: blueprint $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GTKFLAGS) -o $(BIN_BUILD)/simulation_physic $(MATHFLAGS)

run: comp
	$(BIN_BUILD)/simulation_physic


unity.o:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $(UNITY_DIR)/unity.c $(GTKFLAGS) -o $(BIN_DIR)/unity.o

$(BIN_DIR)/physics/kinematics_test.o: $(SRC_DIR)/physics/kinematics.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(MATHFLAGS) -o $@

$(BIN_DIR)/physics/dynamics_test.o: $(SRC_DIR)/physics/dynamics.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(MATHFLAGS) -o $@

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
