#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoDisenoArquitectonico : public Pantalla{
    private:
        sf::Texture tFondo;
        sf::Sprite fondo;
    public:
        minijuegoDisenoArquitectonico(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};