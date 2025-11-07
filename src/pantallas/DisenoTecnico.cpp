#include "../../include/pantallas/DisenoTecnico.h"
/* #include "../../include/minijuegoTopografia/minijuegoTopografia.h"
#include "../../include/minijuegorandomxd/minijuegorandomxd.h" */
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"
#include "../../src/logica/assetManager.h"
#include <iostream>
#include <cmath>

DisenoTecnico::DisenoTecnico(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    float width  = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // =========================
    // Fondo
    // =========================
    if (!tFondoDiseno.loadFromMemory(fondoNexus_png, fondoNexus_png_len)) {
        std::cerr << "Error al cargar fondo de Diseño Técnico\n";
    } else {
        FondoDiseno.setTexture(tFondoDiseno);
        FondoDiseno.setScale(
            width / FondoDiseno.getGlobalBounds().width,
            height / FondoDiseno.getGlobalBounds().height
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
    std::string rutaPuerta = "../assets/nexusxd/puerta diseno3.png";

    coloresBrillo = {
        sf::Color(0, 200, 255, 220),   // Azul claro
        sf::Color(255, 220, 80, 220),  // Amarillo
        sf::Color(0, 255, 150, 220)    // Verde-agua
    };

    const float factorAncho = 0.15f;
    const float factorSeparacion = 0.10f;

    float puertaW = width * factorAncho;
    float puertaH = puertaW * (200.f / 120.f);
    float separacion = width * factorSeparacion;
    float startX = (width - (puertaW * 3 + separacion * 2)) / 2.f;
    float posY = height * 0.15f;

    puertasTextures.resize(3);
    puertasSprites.resize(3);

    for (std::size_t i = 0; i < puertasSprites.size(); ++i) {
        if (!puertasTextures[i].loadFromMemory(puertaDiseno3_png, puertaDiseno3_png_len))
            std::cerr << "No se pudo cargar puerta diseño " << i << "\n";

        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        puertasSprites[i].setScale(puertaW / texSize.x, puertaH / texSize.y);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
    }

    // =========================
    // Fuente y textos sobre las puertas
    // =========================
    if (!fuente.loadFromMemory(Bangers_Regular_ttf, Bangers_Regular_ttf_len))
        std::cerr << "No se pudo cargar la fuente para los textos de puertas\n";

    std::vector<std::string> nombresPuertas = { "P6", "P8", "P9" };
    textosPuertas.resize(3);

    for (int i = 0; i < 3; ++i) {
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
void DisenoTecnico::ManejarEvento(sf::Event evento)
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
                juego->cambiarAPrograma = 6;

                juego->backspace = false;
                juego->enter = false;
                juego->esc = true;
                juego->flechas = false;
                juego->mouse = true;
                juego->space = false;
                juego->wasd = false;

                juego->seleccionado = "minijuegoDisenoArquitectonico";
                juego->botones= true;
                juego->instrucciones = "En el diseño arquitectónico, aprenderas que tienes que desarrollar un pensamiento espacial tanto mental como físicamente para desarrollar planos. ¡Adentrate en P6 mientras construyes el rompecabezas de una casa!";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P6
            case 1:
                juego->cambiarAPrograma = 8;

                juego->backspace = false;
                juego->enter = true;
                juego->esc = true;
                juego->flechas = false;
                juego->mouse = false;
                juego->space = false;
                juego->wasd = false;

                juego->seleccionado = "minijuegoTopografia";
                juego->botones= true;
                juego->instrucciones = "En el minijuego del programa de topografía (P8), vas a tener que posicionar exzactamente en las líneas guías, los elementos de nivelación para preparar el terreno.";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P8
            case 2:
                juego->cambiarAPrograma = 9;

                juego->backspace = true;
                juego->enter = true;
                juego->esc = true;
                juego->flechas = true;
                juego->mouse = false;
                juego->space = false;
                juego->wasd = true;

                juego->seleccionado = "minijuegoDisenoComputador";
                juego->botones= true;
                juego->instrucciones = "En el diseño asistido por computador (P9), tendrás que diseñar a través de una pantalla, una forma determinada que se te pida en la pantalla de al lado. ¡Usa todos los conocimientos que lleves hasta ahora!";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P9
        }
    }
}

// =========================
// LÓGICA
// =========================
void DisenoTecnico::actualizar()
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
void DisenoTecnico::renderizar(sf::RenderWindow& window)
{
    window.clear();
    window.draw(FondoDiseno);

    std::vector<std::string> nombresTalleres = {
        "Diseño arquitectónico",
        "Topografía",
        "Diseño asistido por computador"
    };

    // Puertas + texto
    for (int i = 0; i < 3; ++i) {
        window.draw(puertasSprites[i]);

        // Texto encima de la "P"
        sf::Text nombreTaller;
        nombreTaller.setFont(fuente);
        nombreTaller.setString(utf8_to_wstring(wrapTextString(nombresTalleres[i], fuente, 30, 500)));
        nombreTaller.setCharacterSize(30);

        if (juego->minijuegosPasados[5] && i == 0)
        {
            nombreTaller.setFillColor(sf::Color(204, 51, 153));
        } else if (juego->minijuegosPasados[7] && i == 1)
        {
            nombreTaller.setFillColor(sf::Color(204, 51, 153));
        } else if (juego->minijuegosPasados[8] && i == 2)
        {
            nombreTaller.setFillColor(sf::Color(204, 51, 153));
        }


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
        window.draw(textosPuertas[i]);
    }

    window.draw(jugador);
}
