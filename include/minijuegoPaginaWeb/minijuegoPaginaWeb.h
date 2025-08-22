#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoPaginaWeb : public Pantalla {
    private:
        sf::Font fuente;
        struct configuracionWeb {
            sf::Font fuente;
            sf::Text Texto;
            sf::Color backgroundColor;
            sf::Color textColor;
            int fontSize;
            int layout; // 0 = título izquierda, 1 = título centrado...
        };
        struct Bloque {
            sf::RectangleShape rectangulo;
            sf::Text texto;
            bool seleccionado = false;
            sf::Vector2f offset;
            bool conectado = false;
        };
        std::vector<Bloque> bloques;
        configuracionWeb objetivo;
        sf::View vistaCodigo;
        sf::View vistaPanel;
        sf::View vistaPagina;
        sf::Vector2f mouseEnPanel;
        sf::Vector2f mouseEnCodigo;
        sf::Vector2f mouseEnPagina;
        sf::RectangleShape fondoCodigo;
        sf::RectangleShape fondoPanel;
        sf::RectangleShape fondoPagina;
        sf::RectangleShape pagina;
        int moviemientoPanel = 0;
        sf::Vector2i posicionMouse;
        sf::Vector2f posicionEnVentana;

    public:
        minijuegoPaginaWeb(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};