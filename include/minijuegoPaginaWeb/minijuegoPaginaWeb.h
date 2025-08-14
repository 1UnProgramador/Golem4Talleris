#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoPaginaWeb : public Pantalla {
    private:
        struct configuracionWeb {
            sf::Font fuente;
            sf::Text Texto;
            sf::Color backgroundColor;
            sf::Color textColor;
            int fontSize;
            int layout; // 0 = título izquierda, 1 = título centrado...
        };
        configuracionWeb objetivo;
        sf::View vistaCodigo;
        sf::View vistaPagina;
        sf::RectangleShape mundo;
        sf::CircleShape jugador;
    public:
        minijuegoPaginaWeb(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};