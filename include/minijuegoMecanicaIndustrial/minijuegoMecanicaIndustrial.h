#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoMecanicaIndustrial : public Pantalla{
    private:
        sf::Texture tFondo;
        sf::Sprite fondo;

        sf::Texture tPantalla;
        sf::Sprite sPantalla;

        sf::Texture tPistonDesactivado;
        sf::Sprite pistonDesactivado;

        sf::Texture tPistonActivado;
        sf::Sprite pistonActivado;

        bool activado = false;

        struct Pieza
        {
            std::shared_ptr<sf::Texture> tPiezas;
            sf::Sprite sPieza;
            bool piezaGolpeada = false;
        };
        std::vector<std::string> nombresPiezas;

        std::vector<Pieza> piezasBuenas;
        std::vector<Pieza> piezasMalas;

        std::vector<Pieza> piezasGeneradas;
        sf::Clock relojPiezas;
        float delayTime = 2.0f;
        int velocidad = 5;

        sf::Texture tCintas;
        sf::Sprite cintas;
        sf::Sprite cintas2;
        sf::Sprite cintas3;
        sf::Sprite cintas4;
        sf::Sprite cintas5;
        sf::Sprite cintas6;

        const int frameWidth = 110;
        const int frameHeight = 26;
        const int numFrames = 7;
        int currentFrame = 0;

        sf::Clock relojAnimacion;
        float frameTime = 0.23f;
    public:
        minijuegoMecanicaIndustrial(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};