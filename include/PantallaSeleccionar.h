#pragma once
#include "Pantalla.h"
#include "PantallaSeleccionar.h"
#include "./Personaje.h"

#include <SFML/Graphics.hpp>

class PantallaSeleccionar : public Pantalla{
    private:
        Golem jugador;

    public: 
        PantallaSeleccionar(Juego* juego);

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};