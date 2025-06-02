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
    sprite.setPosition(20, posicionYPlataforma + nAleatorio(gen));
}

void Obstaculo::update(){
    sprite.move(20, 0);
} 

void Obstaculo::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}