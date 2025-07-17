#include "../include/Personaje.h"
#include <SFML/Graphics.hpp>

Golem::Golem(float pInicialX, float pInicialY){
    texture.loadFromFile("../assets/JugadorGolem/estado-reposo/SGolem.png");
    sprite.setTexture(texture);
    sprite.setPosition(pInicialX, pInicialY);
    sprite.setScale(3, 3);
    /* sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2); */
    sprite.setTextureRect(sf::IntRect(1 * frameWidth, 0, frameWidth, frameHeight));
}

void Golem::update(sf::VideoMode desktopMode){
    
    bool estaQuieto = !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    //Se verifica si hay alguna tecla presionada
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sprite.move(0, -velocidad);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            sprite.setScale(-3, -3);
            if (currentFrame <= 6 || currentFrame > 19){
                currentFrame = 6;
                tFrames = 19;
            }
            if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion)
            {
                currentFrame = (currentFrame + 1) % tFrames;
                if (currentFrame == 0) currentFrame = 7;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                relojAnimacion.restart();
            }
            sprite.move(-velocidad, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            sprite.setScale(3, 3);
            if (currentFrame <= 6 || currentFrame > 19){
                currentFrame = 6;
                tFrames = 19;
            }
            if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion)
            {
                currentFrame = (currentFrame + 1) % tFrames;
                if (currentFrame == 0) currentFrame = 7;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                relojAnimacion.restart();
            }
            sprite.move(velocidad, 0);

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            sprite.move(0, velocidad);
        } else {
            if (currentFrame >= 6){
                currentFrame = 0;
                tFrames = 6;
            }
            if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion)
            {
                currentFrame = (currentFrame + 1) % tFrames;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                relojAnimacion.restart();
            }
            
        }

        /* if (estaQuieto && relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion){
            currentFrame = (currentFrame + 1) % tFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            relojAnimacion.restart();
        } */

        //No se puede salir de la plataforma
        

        if (sprite.getPosition().x < (desktopMode.width / 2) - 379){
            sprite.setPosition((desktopMode.width / 2) - 379, sprite.getPosition().y);
        }
        if (sprite.getPosition().x + sprite.getGlobalBounds().width > (desktopMode.width / 2) + 379){
            sprite.setPosition((desktopMode.width / 2) + 379 - sprite.getGlobalBounds().width, sprite.getPosition().y);
        }
        if (sprite.getPosition().y < (desktopMode.height / 2) - 309){
            sprite.setPosition(sprite.getPosition().x, (desktopMode.height / 2) - 309);
        }
        if (sprite.getPosition().y + sprite.getGlobalBounds().height > (desktopMode.height /2 ) + 309){
            sprite.setPosition(sprite.getPosition().x, (desktopMode.height / 2) + 309 - sprite.getGlobalBounds().height);
        }
}
void Golem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}
sf::FloatRect Golem::getBounds() const{
    return sprite.getGlobalBounds();

}

void Golem::setPosition(int x, int y){
    sprite.setPosition(x, y);
}

int Golem::getFramewidth(){
    return frameWidth;
}

int Golem::getFrameHeight(){
    return frameHeight;
}

int Golem::getCurrentFrame(){
    return currentFrame;
}

void Golem::setCurrentFrame(int x){
    currentFrame = x;
}

int Golem::totalFrames(){
    return tFrames;
}
