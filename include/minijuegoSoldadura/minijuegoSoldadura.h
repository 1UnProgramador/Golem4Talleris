#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoSoldadura : public Pantalla{
    private:
        sf::Texture tFondo;
        sf::Sprite fondo;
        struct PanelSoldable
        {
            std::shared_ptr<sf::Texture> tPanel;
            sf::Sprite sPanel;
            std::vector<sf::Sprite> marcas;
            bool activada = false;
        };
        std::vector<PanelSoldable> paneles;

        sf::Texture tMarcaLimpia;
        sf::Texture tMarcaSucia;

        sf::Vector2i posicionMouse;
        sf::Vector2f posicionEnVentana;

        bool soldando = false;

        sf::RectangleShape debugging;

    public:
        minijuegoSoldadura(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};