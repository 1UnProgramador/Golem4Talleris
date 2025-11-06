#include "../../include/pantallas/informatica.h"
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>

#include "../../src/logica/assetManager.h"

Informatica::Informatica(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // =========================
    // Fondo
    // =========================
    if (!tFondoInformatica.loadFromMemory(fondoNexus_png, fondoNexus_png_len)) {
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
    /* std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta informatica1.png",
        "../assets/nexusxd/puerta informatica1.png",
        "../assets/nexusxd/puerta informatica1.png"
    }; */

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
        if (i == 0)
        {
            if (!puertasTextures[i].loadFromMemory(puertaInformatica1_png, puertaInformatica1_png_len))
                std::cerr << "No se pudo cargar puerta de informática " << i << "\n";
        } else if(i == 1){
            if (!puertasTextures[i].loadFromMemory(puertaInformatica1_png, puertaInformatica1_png_len))
                std::cerr << "No se pudo cargar puerta de informática " << i << "\n";
        } else if (i == 2){
            if (!puertasTextures[i].loadFromMemory(puertaInformatica1_png, puertaInformatica1_png_len))
                std::cerr << "No se pudo cargar puerta de informática " << i << "\n";
        }



        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        puertasSprites[i].setScale(puertaW / texSize.x, puertaH / texSize.y);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
    }

    // =========================
    // Fuente y textos de puertas (P1, P2, P3)
    // =========================
    if (!fuente.loadFromMemory(Bangers_Regular_ttf, Bangers_Regular_ttf_len)) {
        std::cerr << "No se pudo cargar la fuente para los textos de puertas\n";
    }

    std::vector<std::string> nombresPuertas = { "P1", "P2", "P3" };
    std::vector<std::string> nombresTalleres = {
        "Mantenimiento",
        "Diseno de paginas web",
        "Diseno grafico"
    };

    textosPuertas.resize(3);

    for (int i = 0; i < 3; ++i) {
        // --- Texto "P" ---
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
                juego->instrucciones = "Bienvenido al programa mantenimiento electronico y de computadores , P1. En este minijuego tendras que memorizar la imagen de arriba que es la normativa de como conectar un cable UTP segun la norma T568B, ¡Acuerdate muy bien de donde va cada cable para que no tengas fugas de datos!";
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
                juego->instrucciones = "Ahora mismo estamos entrando a Diseno grafico por computador, P3. Agudiza tu comprension espacial para pasar el siguiente minijuego: Un Tangram. Vas a tener que organizar las piezas de tal manera que abarquen toda la figura azul sin salirse del contorno. Suerte!";
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

        // --- Texto encima de la P ---
        sf::Text nombreTaller;
        nombreTaller.setFont(fuente);
        std::vector<std::string> nombresTalleres = { "Mantenimiento", "Diseno de paginas web", "Diseno grafico" };
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
        window.draw(textosPuertas[i]);  // P1, P2, P3
    }

    window.draw(jugador);
}
