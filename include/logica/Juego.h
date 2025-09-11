#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../../include/logica/Pantalla.h"

class Juego{
    private:
        sf::RenderWindow window;
        std::unique_ptr<Pantalla> pantallaActual;
    public:
        std::string instrucciones;
        Juego();
        void run();

        void cambiarPantalla(std::unique_ptr<Pantalla> pantallaNueva);
        sf::RenderWindow& getWindow() { return window; }
};