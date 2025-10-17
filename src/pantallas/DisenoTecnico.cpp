#include "../../include/pantallas/DiseñoTecnico.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>

DisenoTecnico::DisenoTecnico(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    // Fondo
    if (!tFondoDiseno.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png")) {
        std::cerr << "Error al cargar fondo de Diseño Técnico\n";
    } else {
        FondoDiseno.setTexture(tFondoDiseno);
        float fX = sf::VideoMode::getDesktopMode().width / FondoDiseno.getGlobalBounds().width;
        float fY = sf::VideoMode::getDesktopMode().height / FondoDiseno.getGlobalBounds().height;
        FondoDiseno.setScale(fX, fY);
    }

    // Posición del jugador
    float width = (float)sf::VideoMode::getDesktopMode().width;
    float height = (float)sf::VideoMode::getDesktopMode().height;
    jugador.setPosition((width / 2) - jugador.getBounds().width / 2,
                        (height / 2) - jugador.getBounds().height / 2);

    // Textura de las puertas (Diseño Técnico)
    std::string rutaPuerta = "../assets/nexusxd/puerta diseno.png";

    coloresBrillo = {
        sf::Color(0, 180, 255, 220),
        sf::Color(255, 200, 0, 220)
    };

    const float factorAumento = 1.50f;
    const float baseW = 120.f;
    const float baseH = 200.f;
    const float puertaW = baseW * factorAumento;
    const float puertaH = baseH * factorAumento;

    const float separacion = 400.f;
    const float startX = (width / 2) - ((puertaW * 2 + separacion) / 2);
    const float posY = 120.f;

    puertasTextures.resize(2);
    puertasSprites.resize(2);

    for (int i = 0; i < 2; ++i) {
        if (!puertasTextures[i].loadFromFile(rutaPuerta)) {
            std::cerr << "Warning: No se pudo cargar " << rutaPuerta << "\n";
            sf::Image img; img.create((unsigned)baseW, (unsigned)baseH, sf::Color(150,150,150));
            puertasTextures[i].loadFromImage(img);
        }

        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        float scaleX = puertaW / (float)texSize.x;
        float scaleY = puertaH / (float)texSize.y;
        puertasSprites[i].setScale(scaleX, scaleY);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
        puertasSprites[i].setColor(sf::Color::White);
    }

    // Texto de aviso
    if (!fuente.loadFromFile("../assets/fuentes/arial.ttf")) {
        std::cerr << "No se pudo cargar fuente para aviso\n";
    }
    textoAviso.setFont(fuente);
    textoAviso.setString("Se trabaja en ello");
    textoAviso.setCharacterSize(60);
    textoAviso.setFillColor(sf::Color::White);
    textoAviso.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = textoAviso.getGlobalBounds();
    textoAviso.setPosition((width - bounds.width) / 2, (height - bounds.height) / 2);

    ignoreInput = true;
}

void DisenoTecnico::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        exit(0);
    }

    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased) {
            ignoreInput = false;
        }
        return;
    }

    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter) {
        if (puertaCercana != -1 && !mostrandoAviso) {
            // Mostrar pantalla negra con aviso
            mostrandoAviso = true;
            relojAviso.restart();
        }
    }
}

void DisenoTecnico::actualizar() {
    jugador.update(sf::VideoMode::getDesktopMode());

    if (mostrandoAviso && relojAviso.getElapsedTime().asSeconds() > 2.0f) {
        mostrandoAviso = false;
    }

    if (mostrandoAviso) return; // pausa detección mientras muestra aviso

    int nuevaPuerta = -1;
    float mejorDist = 1e9f;

    sf::FloatRect jugadorBounds = jugador.getBounds();
    float jCenterX = jugadorBounds.left + jugadorBounds.width * 0.5f;
    float jCenterY = jugadorBounds.top + jugadorBounds.height * 0.5f;

    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();
        const float expand = std::max(30.f, b.width * 0.18f);
        b.left -= expand; b.top -= expand; b.width += expand * 2.f; b.height += expand * 2.f;

        if (!jugadorBounds.intersects(b)) {
            puertasSprites[i].setColor(sf::Color::White);
            continue;
        }

        float pCenterX = b.left + b.width * 0.5f;
        float pCenterY = b.top + b.height * 0.5f;
        float dx = pCenterX - jCenterX;
        float dy = pCenterY - jCenterY;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < mejorDist) {
            mejorDist = dist;
            nuevaPuerta = i;
        }
    }

    for (int i = 0; i < (int)puertasSprites.size(); ++i)
        puertasSprites[i].setColor(i == nuevaPuerta ? coloresBrillo[i] : sf::Color::White);

    puertaCercana = nuevaPuerta;
}

void DisenoTecnico::renderizar(sf::RenderWindow& window) {
    if (mostrandoAviso) {
        window.clear(sf::Color::Black);
        window.draw(textoAviso);
        window.display();
        return;
    }

    window.clear();
    window.draw(FondoDiseno);
    for (auto& s : puertasSprites) window.draw(s);
    window.draw(jugador);
}
