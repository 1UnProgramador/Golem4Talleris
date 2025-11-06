#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoPaginaWeb : public Pantalla {
    private:
        sf::Clock clock;
        sf::Clock tiempoRestante;
        sf::Font fuente;
        sf::Text tiempo;
        int tiempoInt = 120;

        sf::Texture tFondo;
        sf::Sprite fondo;

        struct Pieza {
            std::shared_ptr<sf::Texture> textura;
            sf::Sprite sprite;
            sf::Vector2f posicionInicial;
            sf::Vector2f posicionObjetivo;
            bool agarrada = false;
            bool posicionada = false;
        };
        std::vector<Pieza> piezas;


        sf::Vector2i posicionMouse;
        sf::Vector2f posicionEnVentana;
        /* sf::Texture tCompraAzul;
        sf::Sprite compraAzul;


        sf::Texture tCompraRojo;
        sf::Sprite compraRojo;

        sf::Texture tContornoWeb;
        sf::Sprite contornoWeb;

        sf::Texture tImagen;
        sf::Sprite imagen; */

    public:
        /* bool dentroVista(const sf::Vector2f& pos, const sf::View& vista, const sf::RenderWindow& window); */
        minijuegoPaginaWeb(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};