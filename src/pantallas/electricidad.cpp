#include "../../include/pantallas/electricidad.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"

#include <iostream>
#include <cmath>

Electricidad::Electricidad(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    float width  = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    if (!tFondoElectricidad.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png")) {
        std::cerr << "Error al cargar fondo electricidad\n";
    } else {
        FondoElectricidad.setTexture(tFondoElectricidad);
        float fX = width / FondoElectricidad.getGlobalBounds().width;
        float fY = height / FondoElectricidad.getGlobalBounds().height;
        FondoElectricidad.setScale(fX, fY);
    }

    jugador.setPosition(
        (width / 2.f) - jugador.getBounds().width / 2.f,
        height * 0.78f
    );

    std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta electricidad1.png",
        "../assets/nexusxd/puerta electricidad1.png"
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
            std::cerr << "No se pudo cargar " << rutas[i] << "\n";
            sf::Image img; img.create(120, 200, sf::Color(180,180,180));
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

void Electricidad::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
    }

    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased)
            ignoreInput = false;
        return;
    }

    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter) {
        if (puertaCercana != -1) {
            switch (puertaCercana) {
                case 0:
                    juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
                    break;
                case 1:
                    std::cout << "Puerta 2 sin implementar\n";
                    break;
            }
        }
    }
}

void Electricidad::actualizar() {
    jugador.update(sf::VideoMode::getDesktopMode());

    int nuevaPuerta = -1;
    sf::FloatRect jugadorBounds = jugador.getBounds();

    for (size_t i = 0; i < puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();

        const float expand = std::max(10.f, b.width * 0.05f);
        b.left   -= expand;
        b.top    -= expand;
        b.width  += expand * 2.f;
        b.height += expand * 2.f;

        if (jugadorBounds.intersects(b)) {
            nuevaPuerta = static_cast<int>(i);
        }
    }

    for (size_t i = 0; i < puertasSprites.size(); ++i)
        puertasSprites[i].setColor(i == static_cast<size_t>(puertaCercana) ? coloresBrillo[i] : sf::Color::White);

    puertaCercana = nuevaPuerta;
}

void Electricidad::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(FondoElectricidad);

    for (auto& s : puertasSprites)
        window.draw(s);

    window.draw(jugador);
}
