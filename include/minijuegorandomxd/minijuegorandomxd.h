#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class minijuegorandomxd : public Pantalla {
private:
    // jugador y fondo
    Golem jugador;
    sf::Texture fondoTextura;
    sf::Sprite fondo;

    // GRID
    int movimiento = 12; // tamaño del 'pixel' (cuadro)
    int cols = 20;       // columnas por mitad
    int rows = 20;       // filas

    // grids
    std::vector<std::vector<bool>> targetGrid; // rows x cols
    std::vector<std::vector<bool>> metalGrid;  // rows x cols

    // cursor en la mitad derecha
    int cursorCol = 0;
    int cursorRow = 0;

    // dificultad
    enum Dificultad { FACIL, DIFICIL } dificultad;

    // tiempo / reloj
    float tiempoRestante = 130.0f; // segundos
    sf::Clock deltaClock;
    bool cronoActivo = true;

    // visual
    sf::RectangleShape pixelShape;
    sf::RectangleShape cursorShape;
    sf::Font font;
    sf::Text textoNivel;
    sf::Text textoCrono;

    // feedback cortes malos
    std::vector<std::vector<float>> badCutTimer;

    // fade / victoria
    sf::RectangleShape fadeRect;
    bool fadeActivo = false;   
    float fadeAlpha = 0.f;
    bool victoria = false;

    // texto "Bien hecho!"
    bool mostrarBien = false;
    float timerBien = 0.f;

    // nuevo texto "Mejor suerte la proxima"
    bool mostrarTiempoAgotado = false;

    // helpers
    void generarPatron(Dificultad d);
    void generarScrewPattern();
    void generarRimPattern();
    void iniciarGrids();
    bool verificarVictoria();

public:
    minijuegorandomxd(Juego* juego, Dificultad d = FACIL);

    void ManejarEvento(sf::Event event) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};
