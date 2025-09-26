# Definir el compilador
CXX = g++

# Rutas a SFML (al lado del Makefile)
SFML_INC = ./SFML/include
SFML_LIB = ./SFML/lib

# Opciones de compilación
CXXFLAGS = -std=c++17 -Wall -I../include -I$(SFML_INC)

# Opciones de enlace (SFML)
LDFLAGS = -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Compilador de recursos
WINDRES = windres

# Nombre del ejecutable
TARGET = ./Gollem4Talleris.exe

# Archivos fuente
SRC = ../src/logica/main.cpp ../src/logica/Golem.cpp ../src/logica/objColisionable.cpp ../src/logica/Juego.cpp ../src/pantallas/PantallaSeleccionar.cpp ../src/pantallas/PantallaMenu.cpp ../src/minijuegoPonchar/minijuegoPonchar.cpp ../src/minijuegoPaginaWeb/minijuegoPaginaWeb.cpp ../src/pantallas/PantallaCarga.cpp ../src/minijuegoRedes/minijuegoRedes.cpp ../src/minijuegoTangram/minijuegoTangram.cpp

# Recursos
RES = recursos.res
RC  = recursos.rc

# Regla principal
all: $(TARGET)

$(TARGET): $(SRC) $(RES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(RES) $(LDFLAGS)

$(RES): $(RC)
	$(WINDRES) $(RC) -O coff -o $(RES)

# Limpiar
clean:
	rm -f $(TARGET) $(RES)
