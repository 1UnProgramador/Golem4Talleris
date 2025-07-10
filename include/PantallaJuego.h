#pragma once
#include "Pantalla.h"
#include <SFML/Graphics.hpp>

class PantallaJuego : public Pantalla{
    private:
        sf::CircleShape bola;

    public: 
        PantallaJuego();
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};