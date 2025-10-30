#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PantallaSeleccionar : public Pantalla {
private:
    Golem jugador;

    std::vector<sf::Texture> puertasTextures;
    std::vector<sf::Sprite>  puertasSprites;
    std::vector<sf::Color>   coloresBrillo;

    int puertaCercana = -1;
    bool ignoreInput = true; // evita accion inmediata tras cambiar pantalla

    sf::Texture tFondoNexus;
    sf::Sprite  FondoNexus;


public:
    PantallaSeleccionar(Juego* juego);

    void ManejarEvento(sf::Event evento) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};
