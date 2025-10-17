#include "../../include/pantallas/DiseñoTecnico.h"
#include "../../include/minijuegoPonchar/minijuegoPonchar.h"
#include "../../include/logica/Juego.h"
#include <memory>
#include <cmath>

DiseñoTecnico::DiseñoTecnico(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    if (!tFondoDiseno.loadFromFile("../assets/nexusxd/fondo nexus.png")) {
        printf("Error al cargar fondo de diseño técnico\n");
    }
    FondoDiseno.setTexture(tFondoDiseno);

    float fX = sf::VideoMode::getDesktopMode().width / FondoDiseno.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / FondoDiseno.getGlobalBounds().height;
    FondoDiseno.setScale(fX, fY);

    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;
    jugador.setPosition((width / 2) - jugador.getBounds().width / 2, height - 250);

    float puertaWidth = 120.f;
    float puertaHeight = 200.f;
    float separacion = 250.f;
    float startX = (width / 2) - ((puertaWidth * 3) + separacion * 2) / 2;
    float posY = 100.f;

    for (int i = 0; i < 3; i++) {
        sf::RectangleShape puerta(sf::Vector2f(puertaWidth, puertaHeight));
        puerta.setFillColor(sf::Color(101, 67, 33));
        puerta.setPosition(startX + i * (puertaWidth + separacion), posY);
        puertas.push_back(puerta);
    }
}

void DiseñoTecnico::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
        exit(0);

    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter && puertaCercana != -1)
        juego->cambiarPantalla(std::make_unique<minijuegoPonchar>(juego));
}

void DiseñoTecnico::actualizar() {
    jugador.update(sf::VideoMode::getDesktopMode());
    puertaCercana = -1;

    for (int i = 0; i < (int)puertas.size(); ++i) {
        if (jugador.getBounds().intersects(puertas[i].getGlobalBounds())) {
            puertaCercana = i;
            puertas[i].setFillColor(sf::Color(160, 82, 45));
        } else {
            puertas[i].setFillColor(sf::Color(101, 67, 33));
        }
    }
}

void DiseñoTecnico::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(FondoDiseno);
    for (auto& puerta : puertas)
        window.draw(puerta);
    window.draw(jugador);
}
