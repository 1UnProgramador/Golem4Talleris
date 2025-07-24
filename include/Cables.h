#pragma once
#include <SFML/Graphics.hpp>
#include "../include/objColisionable.h"

class Cables : public sf::Drawable, public objColisionable{
    private:
        sf::Sprite spriteCable;
        sf::Texture texturaCable;

        float posicionX;
        float posicionY;
    public:
        Cables(float, float);
        void update(sf::VideoMode desktopMode);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::FloatRect getBounds() const override;
};