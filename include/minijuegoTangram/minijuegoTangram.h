#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoTangram : public Pantalla{
    private:
        struct figura{
            sf::ConvexShape formaFigura;
            bool arrastrando = false;
            sf::Vector2f posicionAnterior;
            int orientacion = 1;
            bool seleccionada = false;
            sf::Color colorOriginal;
        };
        std::vector<figura> figuras;
        std::vector<figura> figurasObjetivo;
        sf::Vector2i posicionMouse;
        sf::Vector2f posicionEnVentana;


    public:
        minijuegoTangram(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};