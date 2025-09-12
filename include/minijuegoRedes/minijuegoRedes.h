#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Audio.hpp>

class minijuegoRedes : public Pantalla{
    private:
    sf::Texture texturaFlecha;
    sf::Sprite flecha1;
    sf::Sprite flecha2;


    sf::Vector2i posicionMouse;
    sf::Vector2f posicionEnVentana;

    sf::SoundBuffer bufferClick;
    sf::Sound click;
    
    
    int prueba = 1;
        struct cuadro {
            std::shared_ptr<sf::Texture> textura;
            sf::Sprite sprite;
            int rotacionObjetivo;
            int rotacion;
            std::string tipo;
        };
        std::vector<cuadro> cuadros;
        std::vector<std::vector<cuadro>> malla;
    public:
        minijuegoRedes(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};