

TARGET = bin/simulationAsserv

SRCDIR_sim =  src
SRCDIR_test += test
SRCDIR_libcom += ../librairie-commune/src
SRCDIR_asserv += ../cdfr2023-programme-base-roulante-asservissment/src

INCLUDE_DIR =  -Iinclude
INCLUDE_DIR += -I../librairie-commune/include
INCLUDE_DIR += -I../cdfr2023-programme-base-roulante-asservissment/include

BINDIR = bin
OBJDIR = obj
OBJDIR_sim = obj/sim
OBJDIR_test = obj/test
OBJDIR_libcom = obj/libcom
OBJDIR_asserv = obj/asserv

SRC_sim = $(wildcard $(SRCDIR_sim)/*.cpp)
SRC_test = $(wildcard $(SRCDIR_test)/*.cpp)
SRC_libcom = $(wildcard $(SRCDIR_libcom)/*.cpp)
SRC_asserv = $(wildcard $(SRCDIR_asserv)/*.cpp)


OBJ = $(patsubst $(SRCDIR_sim)/%.cpp,$(OBJDIR_sim)/%.o,$(SRC_sim))
OBJ += $(patsubst $(SRCDIR_test)/%.cpp,$(OBJDIR_test)/%.o,$(SRC_test))
OBJ += $(patsubst $(SRCDIR_libcom)/%.cpp,$(OBJDIR_libcom)/%.o,$(SRC_libcom))
OBJ += $(patsubst $(SRCDIR_asserv)/%.cpp,$(OBJDIR_asserv)/%.o,$(SRC_asserv))

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wno-unused-parameter -g -O0 $(INCLUDE_DIR) -Wextra -DSIMULATION
LDLIBS = -pthread `pkg-config --cflags --libs gtk+-3.0`

DEPENDS = $(OBJ:.o=.d)

all: $(TARGET)

check:
	@echo $(OBJ)
	@echo "Number of OBJ files: " $(shell echo $(OBJ) | wc -w)

# Création de l'exécutable
$(TARGET): $(OBJ) | $(BINDIR)
	@echo " APP  $@"
	@$(CXX) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(BINDIR):
	@echo " DIR  $@"
	@mkdir -p $(BINDIR)

-include $(DEPENDS)


$(OBJDIR_sim)/%.o: $(SRCDIR_sim)/%.cpp | $(OBJDIR_sim)
	@echo " CXX  $@"
	@$(CXX) $(CXXFLAGS) $(LDLIBS) -MMD -MP -c $< -o $@

$(OBJDIR_sim):
	@echo " DIR  $@"
	@mkdir -p $@


$(OBJDIR_test)/%.o: $(SRCDIR_test)/%.cpp | $(OBJDIR_test)
	@echo " CXX  $@"
	@$(CXX) $(CXXFLAGS) $(LDLIBS) -MMD -MP -c $< -o $@

$(OBJDIR_test):
	@echo " DIR  $@"
	@mkdir -p $@


$(OBJDIR_asserv)/%.o: $(SRCDIR_asserv)/%.cpp | $(OBJDIR_asserv)
	@echo " CXX  $@"
	@$(CXX) $(CXXFLAGS) $(LDLIBS) -MMD -MP -c $< -o $@

$(OBJDIR_asserv):
	@echo " DIR  $@"
	@mkdir -p $@


$(OBJDIR_libcom)/%.o: $(SRCDIR_libcom)/%.cpp | $(OBJDIR_libcom)
	@echo " CXX  $@"
	@$(CXX) $(CXXFLAGS) $(LDLIBS) -MMD -MP -c $< -o $@

$(OBJDIR_libcom):
	@echo " DIR  $@"
	@mkdir -p $@


clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean $(TARGET)
