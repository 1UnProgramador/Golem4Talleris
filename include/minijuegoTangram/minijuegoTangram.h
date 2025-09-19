#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoTangram : public Pantalla{
    private:
        sf::ConvexShape tG1;
        sf::ConvexShape tG2;
        sf::ConvexShape tM1;
        sf::ConvexShape tP1;
        sf::ConvexShape tP2;
        sf::ConvexShape c1;
        sf::ConvexShape p1;
    public:
        minijuegoTangram(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};