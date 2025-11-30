# Configuración
CXX := g++
CC := gcc
CXXFLAGS := -std=c++17 -Wall -Iinclude
CFLAGS := -Iinclude
LDFLAGS := -lglfw -lGL -ldl -lpthread

# Directorios
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# Archivos
TARGET := $(BIN_DIR)/solar_system
SRCS_CPP := $(wildcard $(SRC_DIR)/*.cpp)
SRCS_C := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CPP)) \
					 $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))

# Regla por defecto
all: $(TARGET)

# Regla del Linker (Crear ejecutable)
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Regla de compilación para C++ (Crear .o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla de compilación para C (Crear .o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para crear directorios (Solo se ejecuta si las carpetas NO existen.)
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Utilidades
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	./$(TARGET)

.PHONY: all clean run
