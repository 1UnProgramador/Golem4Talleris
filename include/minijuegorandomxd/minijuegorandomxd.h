#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h" // Asumo que Golem está en Personaje.h
#include <SFML/Graphics.hpp>
#include <vector>

// ENUM NECESARIO PARA PASAR LA DIFICULTAD
enum Dificultad { FACIL, DIFICIL };

class minijuegorandomxd : public Pantalla {
private:
    Golem jugador;
    Dificultad dificultad; // Almacena la dificultad seleccionada

    int rows, cols;
    int cursorRow, cursorCol;
    int movimiento = 20;

    float tiempoRestante;
    bool fadeActivo;
    float fadeAlpha;
    bool victoria;
    bool mostrarBien;
    bool mostrarTiempoAgotado;
    bool cronoActivo;
    float timerBien;

    bool mouseOverConfirmar;
    bool mouseOverCancelar;

    sf::Texture fondoTextura;
    sf::Sprite fondo;

    sf::Font font;
    sf::Text textoNivel;
    sf::Text textoCrono;

    sf::RectangleShape pixelShape;
    sf::RectangleShape cursorShape;
    sf::RectangleShape fadeRect;

    sf::Texture confirmarTextura;
    sf::Texture confirmarHoverTextura;
    sf::Sprite confirmarSprite;

    sf::Texture cancelarTextura;
    sf::Texture cancelarHoverTextura;
    sf::Sprite cancelarSprite;

    std::vector<std::vector<bool>> targetGrid;
    std::vector<std::vector<bool>> metalGrid;
    std::vector<std::vector<float>> badCutTimer;

    sf::Clock deltaClock;

    void generarPatron(Dificultad d);
    void generarScrewPattern();
    void generarRimPattern();
    void iniciarGrids();
    bool verificarVictoria();

public:
    // CONSTRUCTOR MODIFICADO: Acepta la dificultad.
    minijuegorandomxd(Juego* juego, Dificultad d);
    
    void ManejarEvento(sf::Event event) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};