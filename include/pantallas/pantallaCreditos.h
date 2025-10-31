#pragma once
#include "../logica/Pantalla.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>



class pantallaCreditos : public Pantalla{
    private:
        sf::Texture tFondo1;
        sf::Sprite fondo1;

        sf::Texture tFondo2;
        sf::Sprite fondo2;

        sf::Texture tFondo3;
        sf::Sprite fondo3;

        sf::Texture tFondo4;
        sf::Sprite fondo4;

        sf::Font fuente;
        sf::Text texto;
        sf::RectangleShape prueba;

        float velocidad = 0.5;
    public:
        pantallaCreditos(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};