#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Pantalla.h"

class Juego{
    private:
        sf::RenderWindow window;
        std::unique_ptr<Pantalla> pantallaActual;
    public:
        Juego();
        void run();
        void cambiarPantalla(std::unique_ptr<Pantalla> pantallaNueva);
};