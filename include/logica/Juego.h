#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../../include/logica/Pantalla.h"
#include "MusicManager.h"


class Juego{
    private:
        sf::RenderWindow window;
        std::unique_ptr<Pantalla> pantallaActual;

    public:
        struct Logro {
            std::string nombre;
            std::string descripcion;
            bool desbloqueado = false;
        };

        std::vector<Logro> logros;

        void desbloquearLogro(const std::string& nombre);
        bool logroDesbloqueado(const std::string& nombre) const;

        std::string instrucciones;

        std::string seleccionado;
        int cambiarAPrograma = 0;
        bool botones = false;
        bool minijuegoFacil = true;
        std::vector<bool> minijuegosPasados;
        Juego();
        void run();

        void cambiarPantalla(std::unique_ptr<Pantalla> pantallaNueva);
        sf::RenderWindow& getWindow() { return window; }

        bool backspace = false;
        bool enter = false;
        bool esc = false;
        bool flechas = false;
        bool mouse = false;
        bool space = false;
        bool wasd = false;
};