TARGET = bin/simulationAsserv
SRCDIR = ../cdfr2023-programme-base-roulante-asservissment/src src test
INCLUDE_DIR = ../cdfr2023-programme-base-roulante-asservissment/include 
INCLUDE_SIM = include
BINDIR = bin
OBJDIR = obj


SRC = $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))
OBJ = $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

CFLAGS = -std=c++17 -Wall -Wno-unused-parameter -g -O0 -I$(INCLUDE_SIM) -I$(INCLUDE_DIR) -Wextra -O2 -DSIMULATION
LDLIBS = -pthread `pkg-config --cflags --libs gtk+-3.0`

CXX = g++



all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJ) | $(BINDIR)
	$(CXX) $(CFLAGS) -o $@ $^ $(LDLIBS)



# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CFLAGS) -MMD -MP -c $< -o $@

# Création directori
$(OBJDIR):
	mkdir -p $@

# Création directori
$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)


.PHONY: all clean $(TARGET)
