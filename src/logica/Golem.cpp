#include "../../include/logica/Personaje.h"
#include <SFML/Graphics.hpp>

Golem::Golem(float pInicialX, float pInicialY){
    texturaQuieto.loadFromFile("../assets/JugadorGolem/estado-reposo/JGT.png");
    texturaMovLados.loadFromFile("../assets/JugadorGolem/estado-moviendose-lados/JGML.png");
    texturaMovAbajo.loadFromFile("../assets/JugadorGolem/estado-moviendose-abajo/JGMA.png");
    texturaMovArriba.loadFromFile("../assets/JugadorGolem/estado-moviendose-arriba/JGMUp.png");
    sprite.setTexture(texturaQuieto);
    sprite.setPosition(pInicialX, pInicialY);
    sprite.setOrigin(frameWidth / 2.f, frameHeight / 2.f);
    sprite.setScale(3, 3);
    /* sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2); */
    sprite.setTextureRect(sf::IntRect(1 * frameWidth, 0, frameWidth, frameHeight));
}

void Golem::update(sf::VideoMode desktopMode){
    
    //Se verifica si hay alguna tecla presionada
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sprite.setTexture(texturaMovArriba);
            sprite.setScale(3, 3);
            tFrames = 10;
            if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion)
            {
                currentFrame = (currentFrame + 1) % tFrames;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                relojAnimacion.restart();
            }

            sprite.move(0, -velocidad);
            posicionY -= velocidad;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            sprite.setTexture(texturaMovLados);
            /* sprite.setOrigin((currentFrame * frameWidth) + (frameWidth / 2) , frameHeight / 2); */
            sprite.setScale(-3, 3);
            tFrames = 12;
            if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion)
            {
                currentFrame = (currentFrame + 1) % tFrames;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                relojAnimacion.restart();
            }
            sprite.move(-velocidad, 0);
            posicionX -= velocidad;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            sprite.setTexture(texturaMovLados);
            /* sprite.setOrigin((currentFrame * frameWidth) + (frameWidth / 2) , frameHeight / 2); */
            sprite.setScale(3, 3);
            tFrames = 12;
            if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion)
            {
                currentFrame = (currentFrame + 1) % tFrames;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                relojAnimacion.restart();
            }
            sprite.move(velocidad, 0);
            posicionX += velocidad;

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            sprite.setTexture(texturaMovAbajo);
            sprite.setScale(3, 3);
            tFrames = 10;
            if (relojAnimacion.getElapsedTime().asSeconds() > tiempoAnimacion)
            {
                currentFrame = (currentFrame + 1) % tFrames;
                sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
                relojAnimacion.restart();
            }

            sprite.move(0, velocidad);
            posicionY += velocidad;
        } else {
            sprite.setTexture(texturaQuieto);
            sprite.setScale(3, 3);
            tFrames = 6;
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
        

        if ((sprite.getPosition().x - sprite.getGlobalBounds().width / 2) < 0){
            sprite.setPosition(sprite.getGlobalBounds().width / 2, sprite.getPosition().y);
        }
        if ((sprite.getPosition().y - sprite.getGlobalBounds().height / 2) < 0){
            sprite.setPosition(sprite.getPosition().x, sprite.getGlobalBounds().height / 2);
        }
        if (sprite.getPosition().x + sprite.getGlobalBounds().width / 2 > desktopMode.width){
            sprite.setPosition(desktopMode.width - (sprite.getGlobalBounds().width / 2), sprite.getPosition().y);
        }
        if (sprite.getPosition().y + sprite.getGlobalBounds().height / 2 > desktopMode.height){
            sprite.setPosition(sprite.getPosition().x, desktopMode.height - sprite.getGlobalBounds().height / 2);
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