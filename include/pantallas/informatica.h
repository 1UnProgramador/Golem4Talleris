#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Informatica : public Pantalla {
private:
    Golem jugador;

    std::vector<sf::Texture> puertasTextures;
    std::vector<sf::Sprite>  puertasSprites;
    std::vector<sf::Color>   coloresBrillo;
    std::vector<sf::Text> textosPuertas;
    sf::Font fuente;

    int puertaCercana = -1;
    bool ignoreInput = true; // evita accion inmediata tras cambiar pantalla

    sf::Texture tFondoInformatica;
    sf::Sprite  FondoInformatica;

public:
    Informatica(Juego* juego);

    void ManejarEvento(sf::Event evento) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};
