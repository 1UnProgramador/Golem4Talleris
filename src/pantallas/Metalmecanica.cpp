#include "../../include/pantallas/metalmecanica.h"
/* #include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"
#include "../../include/minijuegoSoldadura/minijuegoSoldadura.h" */
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>

Metalmecanica::Metalmecanica(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // =========================
    // Fondo
    // =========================
    if (!tFondoMetalmecanica.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png")) {
        std::cerr << "Error al cargar fondo de metalmecánica\n";
    } else {
        FondoMetalmecanica.setTexture(tFondoMetalmecanica);
        float fX = width / FondoMetalmecanica.getGlobalBounds().width;
        float fY = height / FondoMetalmecanica.getGlobalBounds().height;
        FondoMetalmecanica.setScale(fX, fY);
    }

    // =========================
    // Jugador
    // =========================
    {
        sf::FloatRect pb = jugador.getBounds();
        int inicialX = (int)std::round((width / 2.f) - pb.width * 0.5f);
        int inicialY = (int)std::round(height - pb.height * 2.5f);
        jugador.setPosition(inicialX, inicialY);
    }

    // =========================
    // Configuración de puertas
    // =========================
    std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta metalmecanica4.png",
        "../assets/nexusxd/puerta metalmecanica4.png"
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
    float posY = height * 0.15f;

    puertasTextures.resize(2);
    puertasSprites.resize(2);
    for (int i = 0; i < 2; ++i) {
        if (!puertasTextures[i].loadFromFile(rutas[i])) {
            std::cerr << "Warning: No se pudo cargar " << rutas[i] << "\n";
            sf::Image img;
            img.create(120, 200, sf::Color(150,150,150));
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

    // =========================
    // Fuente y textos de puertas ("P5", "P12")
    // =========================
    if (!fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf")) {
        std::cerr << "No se pudo cargar fuente para textos de puertas\n";
    }

    std::vector<std::string> nombresPuertas = { "P5", "P12" };
    textosPuertas.resize(2);
    for (int i = 0; i < 2; ++i) {
        textosPuertas[i].setFont(fuente);
        textosPuertas[i].setString(nombresPuertas[i]);
        textosPuertas[i].setCharacterSize(35);
        textosPuertas[i].setFillColor(sf::Color::White);
        textosPuertas[i].setOutlineColor(sf::Color::Black);
        textosPuertas[i].setOutlineThickness(3.f);
        textosPuertas[i].setStyle(sf::Text::Bold);

        sf::FloatRect textBounds = textosPuertas[i].getLocalBounds();
        sf::FloatRect puertaBounds = puertasSprites[i].getGlobalBounds();
        textosPuertas[i].setPosition(
            puertaBounds.left + (puertaBounds.width / 2.f) - (textBounds.width / 2.f),
            puertaBounds.top - textBounds.height * -0.5f
        );
    }
}

// =========================
// EVENTOS
// =========================
void Metalmecanica::ManejarEvento(sf::Event evento)
{
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
    }

    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased) {
            ignoreInput = false;
        }
        return;
    }

    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter && puertaCercana != -1) {
        switch (puertaCercana) {
            case 0:
                juego->cambiarAPrograma = 5;
                juego->instrucciones = "Binevenido al hogar de las máquinas, aquí como buen mecánico industrial (P5), vas a tener que desechar al contenedor las piezas que no coincidan con la que se muestran en la pantalla. Demuestrale a los demás tu percepción e intuición visual.";
                juego->botones = true;
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P5
            case 1:
                juego->cambiarAPrograma = 12;
                juego->instrucciones = "Acá nos vamos a poner un poco más calientes, porqué en el siguiente";
                juego->botones = true;
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P12
        }
    }
}

// =========================
// LÓGICA
// =========================
void Metalmecanica::actualizar()
{
    jugador.update(sf::VideoMode::getDesktopMode());

    if (mostrandoAviso && relojAviso.getElapsedTime().asSeconds() > 2.0f)
        mostrandoAviso = false;
    if (mostrandoAviso)
        return;

    int nuevaPuerta = -1;
    float mejorDist = 1e9f;

    sf::FloatRect jugadorBounds = jugador.getBounds();
    float jCenterX = jugadorBounds.left + jugadorBounds.width * 0.5f;
    float jCenterY = jugadorBounds.top + jugadorBounds.height * 0.5f;

    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();
        const float expand = std::max(3.f, b.width * 0.02f);
        b.left -= expand;
        b.top -= expand;
        b.width += expand * 2.f;
        b.height += expand * 2.f;

        if (!jugadorBounds.intersects(b)) {
            puertasSprites[i].setColor(sf::Color::White);
            continue;
        }

        float pCenterX = b.left + b.width * 0.5f;
        float pCenterY = b.top + b.height * 0.5f;
        float dx = pCenterX - jCenterX;
        float dy = pCenterY - jCenterY;
        float dist = std::sqrt(dx*dx + dy*dy);
        if (dist < mejorDist) {
            mejorDist = dist;
            nuevaPuerta = i;
        }
    }

    for (int i = 0; i < (int)puertasSprites.size(); ++i)
        puertasSprites[i].setColor(i == nuevaPuerta ? coloresBrillo[i] : sf::Color::White);

    puertaCercana = nuevaPuerta;
}

// =========================
// RENDERIZAR
// =========================
void Metalmecanica::renderizar(sf::RenderWindow& window)
{
    if (mostrandoAviso) {
        window.clear(sf::Color::Black);
        window.draw(textoAviso);
        window.display();
        return;
    }

    window.clear();
    window.draw(FondoMetalmecanica);
    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        window.draw(puertasSprites[i]);
        window.draw(textosPuertas[i]); // textos "P5" y "P12"
    }
    window.draw(jugador);
}
