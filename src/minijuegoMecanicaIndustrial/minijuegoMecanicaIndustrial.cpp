#include "../../include/logica/Juego.h"
#include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"

#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>

minijuegoMecanicaIndustrial::minijuegoMecanicaIndustrial(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoElectricidad.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tPantalla.loadFromFile("../assets/minijuegoMecanicaIndustrial/pantalla.png");
    sPantalla.setTexture(tPantalla);
    sPantalla.setOrigin(sPantalla.getGlobalBounds().width / 2, sPantalla.getGlobalBounds().height / 2);
    sPantalla.setPosition(sf::VideoMode::getDesktopMode().width / 2, (sf::VideoMode::getDesktopMode().height / 2));
    sPantalla.setScale(9, 9);
    sPantalla.move(0, -1 * (sPantalla.getGlobalBounds().height));

    tCintas.loadFromFile("../assets/minijuegoMecanicaIndustrial/cintas.png");
    cintas.setTexture(tCintas);
    cintas.setOrigin(cintas.getGlobalBounds().width / 2, cintas.getGlobalBounds().height / 2);
    cintas.setScale(3, 3);
    cintas.setPosition(sPantalla.getPosition().x + 350, sPantalla.getPosition().y + (sPantalla.getGlobalBounds().height / 2) + (cintas.getGlobalBounds().height / 2) + 40);

    cintas2.setTexture(tCintas);
    cintas2.setOrigin(cintas2.getGlobalBounds().width / 2, cintas2.getGlobalBounds().height / 2);
    cintas2.setScale(3, 3);
    cintas2.setPosition(cintas.getPosition().x + frameWidth, cintas.getPosition().y);

}
void minijuegoMecanicaIndustrial::ManejarEvento(sf::Event evento){

}
void minijuegoMecanicaIndustrial::actualizar(){
    if (clock.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        clock.restart();
    }
    if (clock.getElapsedTime().asSeconds() >= frameTime) {
        currentFrame = (currentFrame + 1) % numFrames; // avanza al siguiente frame
        cintas2.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        clock.restart();
    }
}
void minijuegoMecanicaIndustrial::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(sPantalla);
    window.draw(cintas);
    window.draw(cintas2);
}