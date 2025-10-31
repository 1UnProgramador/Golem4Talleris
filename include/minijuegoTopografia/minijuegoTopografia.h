#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h" // Contiene la clase Golem
#include <SFML/Graphics.hpp>
#include <vector>

// --- ENUM DE DIFICULTAD ---
enum class DificultadTopo { FACIL, DIFICIL };

// --- ESTRUCTURA DE MARCADORES ---
struct MarcadorTopo {
    sf::Sprite sprite;
    bool medido = false;
    bool correcto = false;
};

// --- CLASE PRINCIPAL DEL MINIJUEGO ---
class Topografia : public Pantalla {
private:
    // --- Datos base ---
    Golem jugador;

    // Fondo general
    sf::Texture fondoTextura;
    sf::Sprite fondo;

    // --- Terreno (ya no se dibuja con sprites, solo con puntos) ---
    sf::Texture terrenoTextura1;
    sf::Texture terrenoTextura2;
    sf::Sprite terreno1;
    sf::Sprite terreno2;
    std::vector<sf::Vector2f> terrenoPuntos1;
    std::vector<sf::Vector2f> terrenoPuntos2;

    // --- Marcadores (Binye topo) ---
    std::vector<MarcadorTopo> marcadores;
    sf::Texture marcadorTextura;
    float marcadorPosY;
    float marcadorVelY;

    // --- Zona de trabajo (rectángulo central gris) ---
    sf::RectangleShape zonaTrabajo;

    // --- Efectos visuales (destello y transición) ---
    sf::RectangleShape destello;
    float destelloTiempo;

    // --- Tiempos ---
    sf::Clock reloj;
    float tiempoLimite;
    float tiempoTranscurrido;

    // --- Texto y fuente ---
    sf::Font fuente;
    sf::Text textoCrono;
    sf::Text mensajeFinal;

// --- Estado general ---
    bool mostrarMensajeFinal;
    float tiempoMensaje;
    int puntosMedidos;
    DificultadTopo dificultad;
    bool victoria; 

    // --- Control de entrada (antispam Enter) ---
    sf::Clock clockEnter;
    float enterCooldown;

    // --- Margen de acierto ---
    float margenAcierto;

public:
    // --- Constructor ---
    Topografia(Juego* juego, DificultadTopo dificultad = DificultadTopo::FACIL);

    // --- Métodos principales del ciclo ---
    void ManejarEvento(sf::Event event) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;

private:
    void generarTerreno(std::vector<sf::Vector2f>& puntos,
                        float xStart, float xEnd, float baseY,
                        float amplitude, int nPoints);
    float muestrearTerreno(const std::vector<sf::Vector2f>& puntos, float x) const;
    void inicializarMarcadores();
    void mostrarMensajePerder();
    void mostrarMensajeGanar(); 
};
