#include "../include/Juego.h"
#include "../include/PantallaMenu.h"
#include "../include/PantallaJuego.h"

Juego::Juego() : window(sf::VideoMode::getDesktopMode(), "Sistema de Pantallas") {
    cambiarPantalla(std::make_unique<PantallaMenu>([this]() {
        cambiarPantalla(std::make_unique<PantallaJuego>());
    }));
}

void Juego::cambiarPantalla(std::unique_ptr<Pantalla> nuevaPantalla){
    pantallaActual = std::move(nuevaPantalla);
}

void Juego::run() {
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