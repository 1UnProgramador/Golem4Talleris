# Definir el compilador
CXX = g++

# Definir opciones de compilación
CXXFLAGS = -std=c++17 -Wall -I../include

# Definir opciones de enlace (SFML)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Nombre del ejecutable
TARGET = ../juego

# Archivos fuente en src/
SRC = ../src/main.cpp ../src/Game.cpp ../src/Player.cpp ../src/Enemy.cpp

# Regla principal: compilar el juego
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Regla para limpiar archivos compilados
clean:
	rm -f $(TARGET)
