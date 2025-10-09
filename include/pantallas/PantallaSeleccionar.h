#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PantallaSeleccionar : public Pantalla {
private:
    Golem jugador;
    std::vector<sf::RectangleShape> puertas;
    int puertaCercana = -1; // índice de la puerta cercana

    // Fondo
    sf::Texture tFondoNexus;
    sf::Sprite FondoNexus;

public:
    PantallaSeleccionar(Juego* juego);

    void ManejarEvento(sf::Event evento) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};