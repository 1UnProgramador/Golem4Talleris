#pragma once
#include "../logica/Pantalla.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>



class PantallaCarga : public Pantalla{
    private:
        sf::Texture tFondo;
        sf::Sprite fondo;

        int offsetX = 0;
        int offsetY = 0;
        int speedX = 1;
        int speedY = 1;

        int w;
        int h;

        sf::Font fuente;
        sf::Text texto;
        sf::Text bienvenida;
        sf::Texture imagen;
        sf::Sprite sImagen;
        sf::RectangleShape barraCarga;
        sf::Clock eje;
        sf::RectangleShape cBorde;
        sf::RectangleShape cRelleno;


    public:
        PantallaCarga(Juego* juego);

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};