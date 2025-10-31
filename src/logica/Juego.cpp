#include "../../include/logica/Juego.h"
#include "../../include/pantallas/PantallaMenu.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include <iostream>

Juego::Juego() : window(sf::VideoMode::getDesktopMode(), "Gollem4Talleris", sf::Style::Fullscreen/* , sf::ContextSettings(8) */) {
    pantallaActual = std::make_unique<PantallaMenu>(this);

    logros.push_back({"Maestro del Bit Supremo", "Completaste el taller de informatica"});
    logros.push_back({"Senor de los Voltios", "Completaste el taller de electricidad"});
    logros.push_back({"Arquitecto de los Suenos", "Completaste el taller de diseño"});
    logros.push_back({"Forjador del Acero Eterno", "Completaste el taller de metalmecanica"});
}

void Juego::desbloquearLogro(const std::string& nombre) {
    for (auto& logro : logros) {
        if (logro.nombre == nombre && !logro.desbloqueado) {
            logro.desbloqueado = true;
            std::cout << "Logro desbloqueado: " << logro.nombre << " - " << logro.descripcion << "\n";
            // Aquí podrías mostrar un pop-up visual tipo Steam
            break;
        }
    }
}

bool Juego::logroDesbloqueado(const std::string& nombre) const {
    for (const auto& logro : logros) {
        if (logro.nombre == nombre)
            return logro.desbloqueado;
    }
    return false;
}

void Juego::cambiarPantalla(std::unique_ptr<Pantalla> nuevaPantalla){
    pantallaActual = std::move(nuevaPantalla);
}

void Juego::run() {
    for (int i = 0; i <= 11; i++)
    {
        minijuegosPasados.push_back(false);
    }

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