#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Electricidad : public Pantalla {
private:
    Golem jugador;

    std::vector<sf::Texture> puertasTextures;
    std::vector<sf::Sprite>  puertasSprites;
    std::vector<sf::Color>   coloresBrillo;
    std::vector<sf::Text> textosPuertas;

    int puertaCercana = -1;
    bool ignoreInput = true;

    sf::Texture tFondoElectricidad;
    sf::Sprite  FondoElectricidad;
    sf::Font fuente;
public:
    Electricidad(Juego* juego);

    void ManejarEvento(sf::Event evento) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};
