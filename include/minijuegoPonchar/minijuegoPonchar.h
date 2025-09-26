#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoPonchar : public Pantalla{
    private:
        struct Cable : public sf::Drawable, public objColisionable{
            std::vector<std::string> nombresCables;

            std::shared_ptr<sf::Texture> tCable;
            sf::Sprite sCable;

            sf::RectangleShape pObjetivo;
            bool objetivoOcupado = false;

            bool arrastrando = false;
            sf::Vector2f offset;
            int pinObjetivo;
            bool conectado = false;
            bool correcto = false;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
                target.draw(sCable, states);
            }
            sf::FloatRect getBounds() const override {
                return sCable.getGlobalBounds();
            }
        };
        sf::Vector2i posicionMouse;
        sf::Vector2f posicionEnVentana;

        std::vector<Cable> cables;
        std::vector<sf::RectangleShape> pines;

        sf::Texture tConector;
        sf::Sprite conector;

    public:
        minijuegoPonchar(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};