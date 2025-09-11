#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoPaginaWeb : public Pantalla {
    private:
        sf::Font fuente;
        sf::Texture texturaFlechaSeleccionar;
        std::vector<std::string> textosBloques = {"fuente: ", "texto: ", "color de fondo: ", "color de texto: ", "tamano de fuente: ", "centrado titulo: "};
        struct configuracionWeb {
            sf::Font fuente;
            sf::Text Texto;
            sf::Color backgroundColor;
            sf::Color textColor;
            int fontSize;
            int layout; // 0 = título izquierda, 1 = título centrado...

        };
        struct Bloque {
            sf::Sprite flecha;
            sf::RectangleShape rectangulo;
            sf::Text texto;
            bool seleccionado = false;
            sf::Vector2f offset;
            bool conectadoU = false;
            bool  conectadoD = false;
            bool arrastrando = false;
            sf::Vector2f grabOffset{0.f, 0.f};
            int pantalla = 0;
        };
        std::vector<Bloque> bloques;
        std::vector<Bloque> copiaBloques;
        configuracionWeb objetivo;
        sf::View vistaCodigo;
        sf::View vistaPanel;
        sf::View vistaPagina;
        sf::Vector2f mouseEnPanel;
        sf::Vector2f mouseEnCodigo;
        sf::Vector2f mouseEnPagina;
        sf::Vector2f mouseEnPantalla;
        sf::RectangleShape fondoCodigo;
        sf::RectangleShape fondoPanel;
        sf::RectangleShape fondoPagina;
        sf::RectangleShape pagina;
        int moviemientoPanel = 0;
        int posicionBloques = 1;
        sf::Vector2i posicionMouse;
        sf::Vector2f mouseEnPantallaRelativa;
        sf::Vector2f posicionEnVentana;

    public:
        /* bool dentroVista(const sf::Vector2f& pos, const sf::View& vista, const sf::RenderWindow& window); */
        minijuegoPaginaWeb(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};