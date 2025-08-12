#pragma once
#include <memory>
#include "../logica/Pantalla.h"
#include "../logica/objColisionable.h"
#include <SFML/Graphics.hpp>

class minijuegoPonchar : public Pantalla{
    private:
        sf::Font fuente;
        sf::Text texto;
        int tIncorrectos = 0;
        struct Cable : public sf::Drawable, public objColisionable{
            std::vector<std::string> nombresCables;

            std::shared_ptr<sf::Texture> tCable;
            sf::Sprite sCable;

            sf::RectangleShape pObjetivo;

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

    public:
        minijuegoPonchar(Juego* juego);
        void ManejarEvento(sf::Event evento) override;
        void actualizar() override;
        void renderizar(sf::RenderWindow& window) override;
};