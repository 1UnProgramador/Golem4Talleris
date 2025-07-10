#pragma once
#include "Pantalla.h"
#include <SFML/Graphics.hpp>
#include <functional>

class PantallaMenu : public Pantalla{
    private:
        sf::Font fuente;
        sf::Text texto;
        std::function<void()> onStart;
    
    public:
        PantallaMenu(std::function<void()> onStart);

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};