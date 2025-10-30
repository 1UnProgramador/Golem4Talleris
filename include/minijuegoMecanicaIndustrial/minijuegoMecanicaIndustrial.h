#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoMecanicaIndustrial : public Pantalla{
    private:
        sf::Font fuente;
        sf::Text texto;

        sf::Texture tFondo;
        sf::Sprite fondo;

        sf::Texture tPantalla;
        sf::Sprite sPantalla;

        sf::Texture tPistonDesactivado;
        sf::Sprite pistonDesactivado;

        sf::Texture tPistonActivado;
        sf::Sprite pistonActivado;

        sf::Texture tBoteBasurero;
        sf::Sprite boteBasurero;

        bool activado = false;

        struct Pieza
        {
            std::shared_ptr<sf::Texture> tPiezas;
            sf::Sprite sPieza;
            bool piezaGolpeada = false;
            bool activada = false;
            bool piezaBuena = false;
        };
        struct Corazon
        {
            std::shared_ptr<sf::Texture> tCorazon;
            sf::Sprite sCorazon;
        };
        std::vector<Corazon> corazones;
        int vidas = 3;
        int puntos = 0;
        int necesarios = 0;

        std::vector<std::string> nombresPiezas;

        std::vector<Pieza> piezasBuenas;
        std::vector<Pieza> piezasMalas;
        std::vector<Pieza> piezasInvisibles;

        std::vector<Pieza> piezasGeneradas;
        sf::Clock relojPiezas;
        float delayTime = 1.0f;
        int numeroPiezas = 10;
        int velocidad = 5;
        sf::Clock cambioPieza;

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