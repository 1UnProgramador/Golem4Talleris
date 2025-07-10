#include "PantallaSeleccionar.h"


PantallaSeleccionar::PantallaSeleccionar()
    : jugador(0, 0)
    {
        jugador.setPosition((sf::VideoMode::getDesktopMode().width / 2) - jugador.getBounds().width / 2, (sf::VideoMode::getDesktopMode().height / 2) - jugador.getBounds().height / 2);
    }

void PantallaSeleccionar::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
    {
        exit(0);
    }
}

void PantallaSeleccionar::actualizar(){
    jugador.update(sf::VideoMode::getDesktopMode());
}

void PantallaSeleccionar::renderizar(sf::RenderWindow& window){
    window.draw(jugador);
}