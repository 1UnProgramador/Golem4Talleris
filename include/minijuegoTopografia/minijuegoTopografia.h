#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct Marcador {
    sf::Sprite sprite;
    bool medido = false;
    bool correcto = false;
};

class Topografia : public Pantalla {
private:
    Golem jugador;
    sf::Texture fondoTextura;
    sf::Sprite fondo;

    // Terreno
    sf::VertexArray lineaTerreno;
    
    // Marcadores
    std::vector<Marcador> marcadores;
    sf::Texture marcadorTextura;
    float marcadorPosY;
    float marcadorVelY;

    // Feedback
    sf::RectangleShape destello;
    float destelloTiempo;

    // Temporizador
    sf::Clock reloj;
    float tiempoLimite;

    int puntosMedidos;

public:
    Topografia(Juego* juego);

    void ManejarEvento(sf::Event event) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;

private:
    void inicializarTerreno();
    void inicializarMarcadores();
};
