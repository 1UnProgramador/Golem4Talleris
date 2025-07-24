#pragma once
#include "Pantalla.h"
#include <SFML/Graphics.hpp>

class minijuegoPonchar : public Pantalla{
    private:

    public:
        minijuegoPonchar();
        ~minijuegoPonchar();

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};