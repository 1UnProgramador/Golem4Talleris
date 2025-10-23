#include "../../include/pantallas/Metalmecanica.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"

#include <iostream>
#include <cmath>

Metalmecanica::Metalmecanica(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    float width  = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    if (!tFondoMetalmecanica.loadFromFile("../assets/nexusxd/fondo nexus metalmecanica.png")) {
        std::cerr << "Error al cargar fondo de Metalmecanica\n";
    } else {
        FondoMetalmecanica.setTexture(tFondoMetalmecanica);
        float fX = width / FondoMetalmecanica.getGlobalBounds().width;
        float fY = height / FondoMetalmecanica.getGlobalBounds().height;
        FondoMetalmecanica.setScale(fX, fY);
    }

    jugador.setPosition(
        (width / 2.f) - jugador.getBounds().width / 2.f,
        height * 0.78f
    );

    std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta metalmecanica1.png",
        "../assets/nexusxd/puerta metalmecanica2.png"
    };

    coloresBrillo = {
        sf::Color(0, 180, 255, 220),
        sf::Color(255, 200, 0, 220)
    };

    const float factorAncho = 0.15f;
    const float factorSeparacion = 0.10f;
    float puertaW = width * factorAncho;
    float puertaH = puertaW * (200.f / 120.f);
    float separacion = width * factorSeparacion;

    float startX = (width - (puertaW * 2 + separacion)) / 2.f;
    float posY = height * 0.12f;

    puertasTextures.resize(2);
    puertasSprites.resize(2);

    for (size_t i = 0; i < puertasSprites.size(); ++i) {
        if (!puertasTextures[i].loadFromFile(rutas[i])) {
            std::cerr << "Warning: No se pudo cargar " << rutas[i] << "\n";
            sf::Image img; img.create(120, 200, sf::Color(150,150,150));
            puertasTextures[i].loadFromImage(img);
        }

        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        float scaleX = puertaW / static_cast<float>(texSize.x);
        float scaleY = puertaH / static_cast<float>(texSize.y);
        puertasSprites[i].setScale(scaleX, scaleY);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
        puertasSprites[i].setColor(sf::Color::White);
    }

    ignoreInput = true;
}

void Metalmecanica::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
    }

    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased)
            ignoreInput = false;
        return;
    }
}

void Metalmecanica::actualizar() {
    jugador.update(sf::VideoMode::getDesktopMode());
}

void Metalmecanica::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(FondoMetalmecanica);

    for (auto& s : puertasSprites)
        window.draw(s);

    window.draw(jugador);
}
