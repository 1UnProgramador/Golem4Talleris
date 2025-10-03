#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoMecatronica : public Pantalla{
    private:
        sf::Texture tFondo;
        sf::Sprite fondo;

        sf::Texture tLente;
        sf::Sprite lente;

        sf::Texture tLa;
        sf::Sprite lA;


        sf::Texture tPalo;
        sf::Sprite palo;

        sf::Texture tGarra;
        sf::Sprite garra;

        sf::Texture tB1;
        sf::Texture tB2;
        sf::Texture tB3;
        sf::Texture tB4;

        sf::Sprite b1;
        sf::Sprite b2;
        sf::Sprite b3;
        sf::Sprite b4;
    public:
        minijuegoMecatronica(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};