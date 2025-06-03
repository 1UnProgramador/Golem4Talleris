#pragma once
#include <SFML/Graphics.hpp>
#include "../include/objColisionable.h"

class Obstaculo : public sf::Drawable, public objColisionable
{
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        float velocidad = 10;
        float posicionX;
        float posicionY;

    public:
        Obstaculo(int plataformaHeight, float posicionYPlataforma);
        float getPosX() const;
        int getPosY();
        void update();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::FloatRect getBounds() const override;
};

