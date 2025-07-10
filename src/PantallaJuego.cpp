#include "PantallaJuego.h"

PantallaJuego::PantallaJuego(){
    bola.setRadius(50);
    bola.setFillColor(sf::Color::Blue);
    bola.setPosition(250, 250);
}

void PantallaJuego::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
    {
        exit(0);
    }
}

void PantallaJuego::actualizar(){

}

void PantallaJuego::renderizar(sf::RenderWindow& window){
    window.draw(bola);
}