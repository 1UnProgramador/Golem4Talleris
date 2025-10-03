#pragma once
#include "../logica/Pantalla.h"
#include <SFML/Graphics.hpp>
#include <functional>

class PantallaMenu : public Pantalla{
    private:
        sf::Font fuente;
        sf::Text texto;

        sf::Texture tPlay;
        sf::Sprite play;
        sf::Texture tExtra;
        sf::Sprite Extra;
        sf::Texture tExit;
        sf::Sprite Exit;
        sf::Texture tFondoMenu;
        sf::Sprite FondoMenu;

    public:
        PantallaMenu(Juego* juego);

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};