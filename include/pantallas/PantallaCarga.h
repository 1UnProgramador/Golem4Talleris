#pragma once
#include "../logica/Pantalla.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>



class PantallaCarga : public Pantalla{
    private:
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