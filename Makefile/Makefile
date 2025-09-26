# Definir el compilador
CXX = g++

# Definir opciones de compilación
CXXFLAGS = -std=c++17 -Wall -I../include

# Definir opciones de enlace (SFML)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Compilador de recursos
WINDRES = windres

# Nombre del ejecutable
TARGET = ./Gollem4Talleris

# Compilar todos los .cpp
SRC = ../src/logica/main.cpp ../src/logica/Golem.cpp ../src/logica/objColisionable.cpp ../src/logica/Juego.cpp ../src/pantallas/PantallaSeleccionar.cpp ../src/pantallas/PantallaMenu.cpp ../src/minijuegoPonchar/minijuegoPonchar.cpp ../src/minijuegoPaginaWeb/minijuegoPaginaWeb.cpp ../src/pantallas/PantallaCarga.cpp ../src/minijuegoRedes/minijuegoRedes.cpp ../src/minijuegoTangram/minijuegoTangram.cpp

# Archivos de recursos
RES = recursos.res
RC  = recursos.rc

# Regla principal: compilar el juego
all: $(TARGET)

$(TARGET): $(SRC) $(RES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(RES) $(LDFLAGS)

$(RES): $(RC)
	$(WINDRES) $(RC) -O coff -o $(RES)

# Regla para limpiar archivos compilados
clean:
	rm -f $(TARGET) $(RES)
