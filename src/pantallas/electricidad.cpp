#include "../../include/pantallas/electricidad.h"
/* #include "../../include/minijuegoElectronicaYControl/minijuegoElectronicaYControl.h"
#include "../../include/minijuegoAutotronica/minijuegoAutotronica.h"
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"
#include "../../include/minijuegoRedes/minijuegoRedes.h" */
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"
#include "../../src/logica/assetManager.h"
#include <iostream>
#include <cmath>

Electricidad::Electricidad(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // =========================
    // Fondo
    // =========================
    if (!tFondoElectricidad.loadFromMemory(fondoNexus_png, fondoNexus_png_len)) {
        std::cerr << "Error al cargar fondo de Electricidad\n";
    } else {
        FondoElectricidad.setTexture(tFondoElectricidad);
        FondoElectricidad.setScale(
            width / FondoElectricidad.getGlobalBounds().width,
            height / FondoElectricidad.getGlobalBounds().height
        );
    }

    // =========================
    // Jugador centrado abajo
    // =========================
    sf::FloatRect b = jugador.getBounds();
    jugador.setPosition((width / 2.f) - b.width / 2.f, height - b.height * 2.5f);

    // =========================
    // Configuración de puertas
    // =========================
    std::string rutaPuerta = "../assets/nexusxd/puerta electricidad2.png";

    coloresBrillo = {
        sf::Color(0, 200, 255, 220),
        sf::Color(255, 220, 80, 220),
        sf::Color(0, 200, 120, 220),
        sf::Color(80, 140, 255, 220)
    };

    const float factorAncho = 0.15f;
    const float factorSeparacion = 0.10f;

    float puertaW = width * factorAncho;
    float puertaH = puertaW * (200.f / 120.f);
    float separacion = width * factorSeparacion;
    float startX = (width - (puertaW * 4 + separacion * 3)) / 2.f;
    float posY = height * 0.15f;

    puertasTextures.resize(4);
    puertasSprites.resize(4);

    for (std::size_t i = 0; i < puertasSprites.size(); ++i) {
        if (!puertasTextures[i].loadFromMemory(puertaElectricidad2_png, puertaElectricidad2_png_len))
            std::cerr << "No se pudo cargar puerta electricidad " << i << "\n";

        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        puertasSprites[i].setScale(puertaW / texSize.x, puertaH / texSize.y);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
    }

    // =========================
    // Fuente y textos de puertas (P4, P7, P10, P11)
    // =========================
    if (!fuente.loadFromMemory(Bangers_Regular_ttf, Bangers_Regular_ttf_len))
        std::cerr << "No se pudo cargar la fuente para los textos de puertas\n";

    std::vector<std::string> nombresPuertas = { "P4", "P7", "P10", "P11" };
    textosPuertas.resize(4);

    for (int i = 0; i < 4; ++i) {
        textosPuertas[i].setFont(fuente);
        textosPuertas[i].setString(nombresPuertas[i]);
        textosPuertas[i].setCharacterSize(35);
        textosPuertas[i].setFillColor(sf::Color::White);
        textosPuertas[i].setOutlineColor(sf::Color::Black);
        textosPuertas[i].setOutlineThickness(3.f);
        textosPuertas[i].setStyle(sf::Text::Bold);

        sf::FloatRect textBounds = textosPuertas[i].getLocalBounds();
        sf::FloatRect puertaBounds = puertasSprites[i].getGlobalBounds();

        // Centrado arriba de la puerta
        textosPuertas[i].setPosition(
            puertaBounds.left + (puertaBounds.width / 2.f) - (textBounds.width / 2.f),
            puertaBounds.top - textBounds.height * -0.5f
        );
    }

    ignoreInput = true;
}

// =========================
// EVENTOS
// =========================
void Electricidad::ManejarEvento(sf::Event evento)
{
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));

    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased)
            ignoreInput = false;
        return;
    }

    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter && puertaCercana != -1) {
        switch (puertaCercana) {
            case 0:
                juego->cambiarAPrograma = 4;
                juego->seleccionado = "minijuegoMecatronica";
                juego->botones = true;
                juego->instrucciones = "Algunas cosas de mecatronica (P4) se pueden aplicar muy bien a la vida cotidiana...";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P4
            case 1:
                juego->cambiarAPrograma = 7;
                juego->seleccionado = "minijuegoAutotronica";
                juego->botones = true;
                juego->instrucciones = "Trivia de Autotronica (P7)...";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P7
            case 2:
                juego->cambiarAPrograma = 10;
                juego->seleccionado = "minijuegoElectronicaYControl";
                juego->botones = true;
                juego->instrucciones = "Electronica y control (P10)...";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P10
            case 3:
                juego->cambiarAPrograma = 11;
                juego->seleccionado = "minijuegoRedes";
                juego->botones = true;
                juego->instrucciones = "Redes electricas (P11)...";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P11
        }
    }
}

// =========================
// LÓGICA
// =========================
void Electricidad::actualizar()
{
    jugador.update(sf::VideoMode::getDesktopMode());

    int nuevaPuerta = -1;
    sf::FloatRect jBounds = jugador.getBounds();

    for (std::size_t i = 0; i < puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();
        const float expand = std::max(3.f, b.width * 0.02f);
        b.left -= expand;
        b.top -= expand;
        b.width += expand * 2.f;
        b.height += expand * 2.f;

        if (jBounds.intersects(b)) {
            nuevaPuerta = static_cast<int>(i);
            break;
        }
    }

    for (std::size_t i = 0; i < puertasSprites.size(); ++i)
        puertasSprites[i].setColor(i == static_cast<std::size_t>(nuevaPuerta) ? coloresBrillo[i] : sf::Color::White);

    puertaCercana = nuevaPuerta;
}

// =========================
// RENDER
// =========================
void Electricidad::renderizar(sf::RenderWindow& window)
{
    window.clear();
    window.draw(FondoElectricidad);

    std::vector<std::string> nombresTalleres = {
        "MECATRONICA",
        "AUTOTRONICA",
        "Electronica y control",
        "Redes electricas"
    };

    // Puertas + texto
    for (int i = 0; i < 4; ++i) {
        window.draw(puertasSprites[i]);

        // Texto encima de la "P"
        sf::Text nombreTaller;
        nombreTaller.setFont(fuente);
        nombreTaller.setString(nombresTalleres[i]);
        nombreTaller.setCharacterSize(30);
        nombreTaller.setFillColor(sf::Color::White);
        nombreTaller.setOutlineColor(sf::Color::Black);
        nombreTaller.setOutlineThickness(2.f);
        nombreTaller.setStyle(sf::Text::Bold);

        sf::FloatRect nombreBounds = nombreTaller.getLocalBounds();
        sf::FloatRect pBounds = textosPuertas[i].getGlobalBounds();
        nombreTaller.setPosition(
            pBounds.left + (pBounds.width / 2.f) - (nombreBounds.width / 2.f),
            pBounds.top - nombreBounds.height - 5.f
        );

        window.draw(nombreTaller);
        window.draw(textosPuertas[i]);  // P4, P7, P10, P11
    }

    window.draw(jugador);
}
