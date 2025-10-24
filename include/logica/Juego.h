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

        std::string seleccionado;
        int cambiarAPrograma = 0;
        bool botones = false;
        Juego();
        void run();

        void cambiarPantalla(std::unique_ptr<Pantalla> pantallaNueva);
        sf::RenderWindow& getWindow() { return window; }
};