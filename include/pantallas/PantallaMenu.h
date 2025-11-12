#pragma once
#include "../logica/Pantalla.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>


class PantallaMenu : public Pantalla{

    private:
        sf::Font fuente;
        sf::Text texto;

        /* sf::SoundBuffer sSonido; */
        sf::Music sonido;
        /* sf::Clock reloj;

        bool cambioPantalla; */
        //Titulo
        sf::Texture tTitulo;
        sf::Sprite Titulo;

        // Play
        sf::Texture tPlay, tPlayselec;
        sf::Sprite play;

        // Extra
        sf::Texture tExtra, tExtraselec;
        sf::Sprite Extra;

        // Exit
        sf::Texture tExit, tExitselec;
        sf::Sprite Exit;

        // Fondo
        sf::Texture tFondoMenu;
        sf::Sprite FondoMenu;

        int opcionSeleccionada = 0; // 0 = Play, 1 = Extra, 2 = Exit


    public:
        PantallaMenu(Juego* juego);

        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;

};

