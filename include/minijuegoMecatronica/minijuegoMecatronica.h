#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoMecatronica : public Pantalla{
    private:
        sf::Texture tFondo;
        sf::Sprite fondo;

        bool agarrado = false;

        sf::RectangleShape fallo;
        float velocidadFallo;
        int falloEvento = 0;

        struct Corazon
        {
            std::shared_ptr<sf::Texture> tCorazon;
            sf::Sprite sCorazon;
        };
        std::vector<Corazon> corazones;
        int vidas = 3;

        sf::Texture tLente;
        sf::Sprite lente;

        sf::Texture tLa;
        sf::Sprite lA;


        sf::Texture tLaz;
        sf::Sprite lAz;

        sf::Texture tLr;
        sf::Sprite lR;

        sf::Texture tLv;
        sf::Sprite lV;

        sf::Vector2i posicionMouse;
        sf::Vector2f posicionEnVentana;
        struct Objeto{
            std::vector<std::string> nombresObjetos;
            std::shared_ptr<sf::Texture> tObjeto;
            sf::Sprite sObjeto;
            bool actual = false;
            bool agarrado = false;
            bool cayendo = false;
            bool reciclado = false;
        };

        std::vector<Objeto> objetos;
        int i = 0;
        std::vector<sf::Vector2f> posicionesObjetos;




        sf::Texture tPalo;
        sf::Sprite palo;

        sf::Texture tGarra;
        sf::Sprite garra;


        struct led{
            std::vector<std::string> nombresObjetos;
            std::shared_ptr<sf::Texture> tLed;
            sf::Sprite sLed;
            bool activo;
        };
        std::vector<led> leds;


        sf::Texture tB1;
        sf::Texture tB2;
        sf::Texture tB3;
        sf::Texture tB4;

        sf::Sprite b1;
        sf::Sprite b2;
        sf::Sprite b3;
        sf::Sprite b4;

        sf::Clock clock;
        sf::Clock tiempoRestante;
        sf::Font fuente;
        sf::Text tiempo;
        int tiempoInt;
    public:
        minijuegoMecatronica(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};