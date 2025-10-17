#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Metalmecanica : public Pantalla {
private:
    Golem jugador;

    std::vector<sf::Texture> puertasTextures;
    std::vector<sf::Sprite>  puertasSprites;
    std::vector<sf::Color>   coloresBrillo;

    int puertaCercana = -1;
    bool ignoreInput = true; // evita acción inmediata tras cambiar pantalla

    sf::Texture tFondoMetalmecanica;
    sf::Sprite  FondoMetalmecanica;

    // --- NUEVOS ELEMENTOS ---
    sf::Font fuente;
    sf::Text textoAviso;
    bool mostrandoAviso = false;
    sf::Clock relojAviso;

public:
    Metalmecanica(Juego* juego);

    void ManejarEvento(sf::Event evento) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};
