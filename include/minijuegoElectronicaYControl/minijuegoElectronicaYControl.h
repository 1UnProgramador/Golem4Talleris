#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoElectronicaYControl : public Pantalla{
    private:
        sf::RectangleShape contorno;

        int movimiento = 10;

        sf::Texture tFondo;
        sf::Sprite fondo;

        sf::Texture tImpresora;
        sf::Sprite impresora;

        sf::Texture tSoporte;
        sf::Sprite soporte;

        sf::Texture tPuntero;
        sf::Sprite puntero;

        std::vector<sf::RectangleShape> lineasHorizontales;
        std::vector<sf::RectangleShape> lineasVerticales;

        std::vector<sf::RectangleShape> cubos;

    public:
        minijuegoElectronicaYControl(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};