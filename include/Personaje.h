#pragma once
#include <SFML/Graphics.hpp>
#include "../include/objColisionable.h"

class Golem : public sf::Drawable, public objColisionable
{
    private:
        sf::Sprite sprite;
        sf::Texture texturaQuieto;
        sf::Texture texturaMovLados;
        sf::Texture texturaMovAbajo;
        sf::Texture texturaMovArriba;
        float velocidad = 3;
    
        int frameWidth = 32;
        int frameHeight = 32;
        int currentFrame = 0;
        int tFrames = 6;
        sf::Clock relojAnimacion;
        float tiempoAnimacion = 0.1;

        float posicionX;
        float posicionY;

    public:
        Golem(float pInicialX, float pInicialY);
        void update(sf::VideoMode desktopMode);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::FloatRect getBounds() const override;
        void setPosition(int, int);
        int getFramewidth();
        int getFrameHeight();
        int getCurrentFrame();
        void setCurrentFrame(int);
        int totalFrames();
};

