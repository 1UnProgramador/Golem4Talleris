#include "../include/Obstaculo.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h>
#include <random>

Obstaculo::Obstaculo(int plataformaHeight, float posicionYPlataforma){
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> nAleatorio(0, plataformaHeight);

    texture.loadFromFile("../assets/OBSTACULOTEMPORAL.png");
    sprite.setTexture(texture);
    posicionX = 20;
    posicionY = posicionYPlataforma + nAleatorio(gen);
    sprite.setPosition(posicionX, posicionY);
}

void Obstaculo::update(){
    sprite.move(20, 0);
    posicionX += 20;
} 

void Obstaculo::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

sf::FloatRect Obstaculo::getBounds() const{
    return sprite.getGlobalBounds();

}

float Obstaculo::getPosX() const{
    return posicionX;
}
int Obstaculo::getPosY(){
    return posicionY;
}
