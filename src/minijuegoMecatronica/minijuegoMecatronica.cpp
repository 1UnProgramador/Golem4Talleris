#include "../../include/logica/Juego.h"
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"
#include "../../include/minijuegoRedes/minijuegoRedes.h"

#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>

minijuegoMecatronica::minijuegoMecatronica(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoElectricidad.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tLente.loadFromFile("../assets/minijuegoMecatronica/lente.png");
    lente.setTexture(tLente);
    lente.setScale(3, 3);
    lente.setOrigin(lente.getGlobalBounds().width / 2, lente.getGlobalBounds().height / 2);


    tPalo.loadFromFile("../assets/minijuegoMecatronica/palo.png");
    palo.setTexture(tPalo);
    palo.setScale(4, 5);
    palo.setOrigin(palo.getGlobalBounds().width / 2, 0);
    palo.setPosition(sf::VideoMode::getDesktopMode().width / 2, 0);

    tGarra.loadFromFile("../assets/minijuegoMecatronica/garra.png");
    garra.setTexture(tGarra);
    garra.setScale(5, 5);
    garra.setOrigin(garra.getGlobalBounds().width / 2, 0);

    garra.setPosition(palo.getPosition().x, palo.getPosition().y);



    tB1.loadFromFile("../assets/minijuegoMecatronica/caneca1.png");
    tB2.loadFromFile("../assets/minijuegoMecatronica/caneca2.png");
    tB3.loadFromFile("../assets/minijuegoMecatronica/caneca3.png");
    tB4.loadFromFile("../assets/minijuegoMecatronica/caneca4.png");

    b1.setTexture(tB1);
    b1.setScale(3, 3);
    b2.setTexture(tB2);
    b2.setScale(3, 3);
    b3.setTexture(tB3);
    b3.setScale(3, 3);
    b4.setTexture(tB4);
    b4.setScale(3, 3);

    float separacion = 200;
    b1.setPosition(100, sf::VideoMode::getDesktopMode().height - b1.getGlobalBounds().height);
    b2.setPosition(b1.getPosition().x + b1.getGlobalBounds().width + separacion, sf::VideoMode::getDesktopMode().height - b2.getGlobalBounds().height);
    b3.setPosition(b2.getPosition().x + b2.getGlobalBounds().width + separacion, sf::VideoMode::getDesktopMode().height - b3.getGlobalBounds().height);
    b4.setPosition(b3.getPosition().x + b3.getGlobalBounds().width + separacion, sf::VideoMode::getDesktopMode().height - b4.getGlobalBounds().height);

    lente.setPosition(b3.getPosition().x + (separacion / 2) - 50, sf::VideoMode::getDesktopMode().height / 2);

    tLa.loadFromFile("../assets/minijuegoMecatronica/apagado.png");
    lA.setTexture(tLa);
    lA.setOrigin(lA.getLocalBounds().width / 2, lA.getLocalBounds().height);
    lA.setPosition(lente.getPosition().x, lente.getPosition().y - 20);
}
void minijuegoMecatronica::ManejarEvento(sf::Event evento){
    if(evento.type == sf::Event::KeyPressed){
        if (evento.key.code == sf::Keyboard::Enter){
            juego->cambiarPantalla(std::make_unique<minijuegoRedes>(juego));
        } else if(evento.key.code == sf::Keyboard::Left){
            garra.move(-10, 0);
        } else if(evento.key.code == sf::Keyboard::Right){
            garra.move(10, 0);
        }
    }
}
void minijuegoMecatronica::actualizar(){

}
void minijuegoMecatronica::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(b1);
    window.draw(b2);
    window.draw(b3);
    window.draw(b4);

    window.draw(lente);
    window.draw(lA);
    window.draw(palo);
    window.draw(garra);
}