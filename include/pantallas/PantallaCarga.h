#pragma once
#include "../logica/Pantalla.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <memory>

std::string wrapTextString(const std::string& text, const sf::Font& font, unsigned int characterSize, float maxWidth);
std::wstring utf8_to_wstring(const std::string& str);

class PantallaCarga : public Pantalla{
    private:
        sf::Texture botonFacil;
        sf::Texture botonFacilSeleccionado;
        sf::Sprite bFacil;

        sf::Texture botonDificil;
        sf::Texture botonDificilSeleccionado;
        sf::Sprite bDificil;

        bool facil = true;

        struct Control{
            std::shared_ptr<sf::Texture> textura;;
            sf::Sprite sprite;
        };
        std::vector<Control> controles;

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
        /* sf::RectangleShape barraCarga;
        sf::Clock eje; */
        sf::RectangleShape cBorde;
        sf::RectangleShape cRelleno;


    public:

        PantallaCarga(Juego* juego);

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};