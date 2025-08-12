# Definir el compilador
CXX = g++

# Definir opciones de compilación
CXXFLAGS = -std=c++17 -Wall -I../include

# Definir opciones de enlace (SFML)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Nombre del ejecutable
TARGET = ./juego

# Compilar todos los .cpp
SRC = ../src/logica/main.cpp ../src/logica/Golem.cpp ../src/logica/objColisionable.cpp ../src/logica/Juego.cpp ../src/pantallas/PantallaSeleccionar.cpp ../src/pantallas/PantallaMenu.cpp ../src/minijuegoPonchar/minijuegoPonchar.cpp

# Regla principal: compilar el juego
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Regla para limpiar archivos compilados
clean:
	rm -f $(TARGET)
