#pragma once
#include "../logica/Pantalla.h"
#include "../logica/Personaje.h"
#include <SFML/Graphics.hpp>
#include <vector>

class DiseñoTecnico : public Pantalla {
private:
    Golem jugador;
    std::vector<sf::RectangleShape> puertas;
    int puertaCercana = -1;

    sf::Texture tFondoDiseno;
    sf::Sprite FondoDiseno;

public:
    DiseñoTecnico(Juego* juego);

    void ManejarEvento(sf::Event evento) override;
    void actualizar() override;
    void renderizar(sf::RenderWindow& window) override;
};
