# =========================
# Makefile portable con SFML
# =========================

# Carpeta local de MinGW portable
MINGW   = $(CURDIR)/mingw64
CXX     = "$(MINGW)/bin/g++.exe"
WINDRES = "$(MINGW)/bin/windres.exe"

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
      ../src/pantallas/PantallaCarga.cpp \
      ../src/pantallas/Informatica.cpp \
      ../src/pantallas/Electricidad.cpp \
      ../src/pantallas/DisenoTecnico.cpp \
      ../src/pantallas/Metalmecanica.cpp \
      ../src/minijuegoPonchar/minijuegoPonchar.cpp \
      ../src/minijuegoPaginaWeb/minijuegoPaginaWeb.cpp \
      ../src/minijuegoRedes/minijuegoRedes.cpp \
      ../src/minijuegoTangram/minijuegoTangram.cpp \
      ../src/minijuegoAutotronica/minijuegoAutotronica.cpp \
      ../src/minijuegoMecatronica/minijuegoMecatronica.cpp \
      ../src/minijuegoElectronicaYControl/minijuegoElectronicaYControl.cpp \
      ../src/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.cpp \
      ../src/minijuegoSoldadura/minijuegoSoldadura.cpp


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
    LDFLAGS = -L$(SFML)/build/lib -L$(MINGW)/lib \
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
