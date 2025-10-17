#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"
#include "../../include/logica/Juego.h"
#include <memory>

#include <cmath>

PantallaSeleccionar::PantallaSeleccionar(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    // Fondo del Nexus
    if (!tFondoNexus.loadFromFile("../assets/nexusxd/fondo nexus.png")) {
        printf("Error al cargar fondo nexus\n");
    }
    FondoNexus.setTexture(tFondoNexus);

    float fX = sf::VideoMode::getDesktopMode().width / FondoNexus.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / FondoNexus.getGlobalBounds().height;
    FondoNexus.setScale(fX, fY);

    // Posición inicial del jugador al centro de la pantalla
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    jugador.setPosition((width / 2) - jugador.getBounds().width / 2,
                        (height / 2) - jugador.getBounds().height / 2);

    // Crear 4 puertas (rectángulos marrones en la parte superior)
    float puertaWidth = 120.f;
    float puertaHeight = 200.f;
    float separacion = 200.f;

    float startX = (width / 2) - (puertaWidth * 2 + separacion * 1.5f);
    float posY = 100.f;

    for (int i = 0; i < 4; i++) {
        sf::RectangleShape puerta(sf::Vector2f(puertaWidth, puertaHeight));
        puerta.setFillColor(sf::Color(101, 67, 33)); // café oscuro
        puerta.setPosition(startX + i * (puertaWidth + separacion), posY);
        puertas.push_back(puerta);
    }
}

void PantallaSeleccionar::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        exit(0);
    }

    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter) {
        // Si hay una puerta cercana, cambiar de pantalla
        if (puertaCercana != -1) {
            juego->cambiarPantalla(std::make_unique<minijuegoMecanicaIndustrial>(juego));
        }
    }
}

void PantallaSeleccionar::actualizar() {
    jugador.update(sf::VideoMode::getDesktopMode());

    puertaCercana = -1; // Reiniciar detección

    // Detectar si el jugador está cerca de alguna puerta
    for (int i = 0; i < (int)puertas.size(); ++i) {
        sf::FloatRect puertaBounds = puertas[i].getGlobalBounds();
        sf::FloatRect jugadorBounds = jugador.getBounds();

        if (jugadorBounds.intersects(puertaBounds)) {
            puertaCercana = i;
            puertas[i].setFillColor(sf::Color(160, 82, 45)); // café claro
        } else {
            puertas[i].setFillColor(sf::Color(101, 67, 33)); // café oscuro
        }
    }
}

void PantallaSeleccionar::renderizar(sf::RenderWindow& window) {
    window.clear();

    // Dibujar fondo primero
    window.draw(FondoNexus);

    // Dibujar puertas
    for (auto& puerta : puertas)
        window.draw(puerta);

    // Dibujar jugador
    window.draw(jugador);
}
