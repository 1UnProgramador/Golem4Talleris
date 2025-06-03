#include "../include/Personaje.h"
#include <SFML/Graphics.hpp>

Golem::Golem(float pInicialX, float pInicialY){
    texture.loadFromFile("../assets/PJTEMPORAL.png");
    sprite.setTexture(texture);
    sprite.setPosition(pInicialX, pInicialY);
}

void Golem::update(sf::VideoMode desktopMode){
    //Se verifica si hay alguna tecla presionada
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sprite.move(0, -velocidad);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            sprite.move(-velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            sprite.move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sprite.move(0, velocidad);
        }

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

