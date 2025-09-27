# =========================
# Makefile portable con SFML
# =========================

# Carpeta local de MinGW portable
MINGW   = ./mingw64
CXX     = $(MINGW)/bin/g++
WINDRES = $(MINGW)/bin/windres

# Carpeta local de SFML portable
SFML    = ./SFML

# -------------------------
# Configuración
# -------------------------

# Cambia a 1 si quieres compilación estática (sin DLLs)
USE_STATIC = 0

# Opciones de compilación
CXXFLAGS = -std=c++17 -Wall -Iinclude -I$(SFML)/include

# Nombre del ejecutable
TARGET = Gollem4Talleris.exe

# Archivos fuente
SRC = ../src/logica/main.cpp \
      ../src/logica/Golem.cpp \
      ../src/logica/objColisionable.cpp \
      ../src/logica/Juego.cpp \
      ../src/pantallas/PantallaSeleccionar.cpp \
      ../src/pantallas/PantallaMenu.cpp \
      ../src/minijuegoPonchar/minijuegoPonchar.cpp \
      ../src/minijuegoPaginaWeb/minijuegoPaginaWeb.cpp \
      ../src/pantallas/PantallaCarga.cpp \
      ../src/minijuegoRedes/minijuegoRedes.cpp \
      ../src/minijuegoTangram/minijuegoTangram.cpp

# Recursos
RES = recursos.res
RC  = recursos.rc

# -------------------------
# Enlace dinámico vs estático
# -------------------------
ifeq ($(USE_STATIC),1)
    CXXFLAGS += -DSFML_STATIC
    LDFLAGS = -L$(SFML)/lib -L$(MINGW)/lib \
              -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s \
              -lopengl32 -lgdi32 -lfreetype -lwinmm -lopenal32 \
              -lflac -lvorbisenc -lvorbisfile -lvorbis -logg \
              -static-libgcc -static-libstdc++
else
    LDFLAGS = -L$(SFML)/lib -L$(MINGW)/lib \
              -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system \
              -lopengl32 -lgdi32 -lfreetype -lwinmm
endif

# -------------------------
# Reglas
# -------------------------

all: $(TARGET)

$(TARGET): $(SRC) $(RES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(RES) $(LDFLAGS)

$(RES): $(RC)
	$(WINDRES) $(RC) -O coff -o $(RES)

clean:
	rm -f $(TARGET) $(RES)
