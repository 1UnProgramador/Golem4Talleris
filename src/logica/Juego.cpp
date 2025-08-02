#include "../../include/logica/Juego.h"
#include "../../include/pantallas/PantallaMenu.h"
#include "../../include//pantallas/PantallaSeleccionar.h"

Juego::Juego() : window(sf::VideoMode::getDesktopMode(), "Sistema de Pantallas", sf::Style::Fullscreen) {
    pantallaActual = std::make_unique<PantallaMenu>(this);
}

void Juego::cambiarPantalla(std::unique_ptr<Pantalla> nuevaPantalla){
    pantallaActual = std::move(nuevaPantalla);
}

void Juego::run() {
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event evento;
        while (window.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                window.close();
            pantallaActual->ManejarEvento(evento);
        }

        pantallaActual->actualizar();

        window.clear();
        pantallaActual->renderizar(window);
        window.display();
    }
}