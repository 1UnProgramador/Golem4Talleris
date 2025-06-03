#pragma once
#include <SFML/Graphics.hpp>
#include "../include/objColisionable.h"

class Golem : public sf::Drawable, public objColisionable
{
    private:
    sf::Sprite sprite;
    sf::Texture texture;
    float velocidad = 10;
    float posicionX;
    float posicionY;

    public:
    Golem(float pInicialX, float pInicialY);
    void update(sf::VideoMode desktopMode);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const override;
};

