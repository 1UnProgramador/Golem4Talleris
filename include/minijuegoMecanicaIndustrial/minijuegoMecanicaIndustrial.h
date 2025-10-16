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

        sf::Texture tCintas;
        sf::Sprite cintas;
        sf::Sprite cintas2;
        const int frameWidth = 110;
        const int frameHeight = 26;
        const int numFrames = 7;
        int currentFrame = 0;

        sf::Clock clock;
        float frameTime = 0.18f;
    public:
        minijuegoMecanicaIndustrial(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};