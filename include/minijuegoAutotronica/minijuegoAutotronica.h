#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoAutotronica : public Pantalla{
    private:
        struct Objeto{
            std::vector<std::string> nombresObjetos;
            std::shared_ptr<sf::Texture> textura;
            sf::Sprite sprite;
            bool seleccionado = false;
            bool arreglado = false;
        };
        struct Opcion{
            std::shared_ptr<sf::Texture> textura;;
            sf::Sprite sprite;
            sf::RectangleShape cuadro;
            bool seleccionado = false;
            sf::Text texto;
        };
        sf::ConvexShape hazDeLuz;
        bool luz = false;
        sf::RectangleShape humo;
        bool gas = false;

        std::vector<Opcion> opciones;
        std::vector<Objeto> objetos;
        std::vector<Objeto> objetosE1;
        sf::Texture tFondo;
        sf::Sprite fondo;

        sf::Texture tCarro;
        sf::Sprite carro;

        sf::Texture tSilenciador;
        sf::Sprite silenciador;

        sf::Texture tFreno;
        sf::Sprite freno;

        sf::Texture tBateria;
        sf::Sprite bateria;

        sf::Texture tObjeto;
        sf::Texture texturaTemporal;
        sf::Sprite objetoSeleccionado;
        sf::RectangleShape cuadro;
        sf::Texture nuevaTextura;

        sf::Vector2i posicionMouse;
        sf::Vector2f posicionEnVentana;
        bool arrastrando = false;

        sf::Clock clock;
        sf::Clock tiempoRestante;
        sf::Font fuente;
        sf::Text tiempo;
        int tiempoInt;
    public:
        minijuegoAutotronica(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};