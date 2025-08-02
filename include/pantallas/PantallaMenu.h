#pragma once
#include "../logica/Pantalla.h"
#include <SFML/Graphics.hpp>
#include <functional>

class PantallaMenu : public Pantalla{
    private:
        sf::Font fuente;
        sf::Text texto;
    
    public:
        PantallaMenu(Juego* juego);

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};