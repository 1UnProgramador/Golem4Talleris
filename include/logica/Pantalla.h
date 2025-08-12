#pragma once
#include <SFML/Graphics.hpp>


class Juego;

class Pantalla{
    protected:
        Juego* juego;
    public:
        Pantalla(Juego* j) : juego(j){}

        virtual void ManejarEvento(sf::Event event) = 0;
        virtual void actualizar() = 0;
        virtual void renderizar(sf::RenderWindow& window) = 0;
        virtual ~Pantalla() = default;
};
