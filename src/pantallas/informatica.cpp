#include "../../include/pantallas/informatica.h"
#include "../../include/pantallas/PantallaCarga.h"
/* #include "../../include/minijuegoPonchar/minijuegoPonchar.h"
#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/minijuegoTangram/minijuegoTangram.h" */
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>

Informatica::Informatica(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // =========================
    // Fondo
    // =========================
    if (!tFondoInformatica.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png")) {
        std::cerr << "Error al cargar fondo de informática\n";
    } else {
        FondoInformatica.setTexture(tFondoInformatica);
        FondoInformatica.setScale(
            width / FondoInformatica.getGlobalBounds().width,
            height / FondoInformatica.getGlobalBounds().height
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
    std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta informatica1.png",
        "../assets/nexusxd/puerta informatica1.png",
        "../assets/nexusxd/puerta informatica1.png"
    };

    coloresBrillo = {
        sf::Color(0, 200, 255, 220),
        sf::Color(255, 220, 80, 220),
        sf::Color(0, 200, 120, 220)
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
        if (!puertasTextures[i].loadFromFile(rutas[i]))
            std::cerr << "No se pudo cargar puerta de informática " << i << "\n";

        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        puertasSprites[i].setScale(puertaW / texSize.x, puertaH / texSize.y);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
    }

    // =========================
    // Fuente y textos de puertas (P1, P2, P3)
    // =========================
    if (!fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf"))
        std::cerr << "No se pudo cargar la fuente para los textos de puertas\n";

    std::vector<std::string> nombresPuertas = { "P1", "P2", "P3" };
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
void Informatica::ManejarEvento(sf::Event evento)
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
                juego->cambiarAPrograma = 1;
                juego->seleccionado = "minijuegoPonchar";
                juego->botones = true;
                juego->instrucciones = "Bienvenido al programa mantenimiento electrónico y de computadores , P1. En este minijuego tendrás que memorizar la imágen de arriba que es la normativa de cómo conectar un cable UTP según la norma T568B, ¡Acuérdate muy bien de dónde va cada cable para que no tengas fugas de datos!";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P1
            case 1:
                juego->cambiarAPrograma = 2;
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P2
            case 2:
                juego->cambiarAPrograma = 3;
                juego->seleccionado = "minijuegoTangram";
                juego->botones = true;
                juego->instrucciones = "Ahora mismo estamos entrando a Diseño gráfico por computador, P3. Agudiza tu comprensión espacial para pasar el siguiente minijuego: Un Tangram. Vas a tener que organizar las piezas de tal manera que abarquen toda la figura azul sin salirse del contorno. Suerte!";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P3
        }
    }
}

// =========================
// LÓGICA
// =========================
void Informatica::actualizar()
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
void Informatica::renderizar(sf::RenderWindow& window)
{
    window.clear();
    window.draw(FondoInformatica);

    // Puertas + texto
    for (int i = 0; i < 3; ++i) {
        window.draw(puertasSprites[i]);
        window.draw(textosPuertas[i]);
    }

    window.draw(jugador);
}
