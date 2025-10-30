#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoDisenoArquitectonico : public Pantalla{
    private:
        sf::Texture tFondo;
        sf::Sprite fondo;

        sf::Texture tContorno;
        sf::Sprite contorno;

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

        int tolerancia;

        sf::Clock clock;
        sf::Clock tiempoRestante;
        sf::Font fuente;
        sf::Text tiempo;
        int tiempoInt;
    public:
        minijuegoDisenoArquitectonico(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};