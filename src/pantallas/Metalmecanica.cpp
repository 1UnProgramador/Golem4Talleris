#include "../../include/pantallas/metalmecanica.h"
/* #include "../../include/minijuegoMecanicaIndustrial/minijuegoMecanicaIndustrial.h"
#include "../../include/minijuegoSoldadura/minijuegoSoldadura.h" */
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>

#include "../../src/logica/assetManager.h"

Metalmecanica::Metalmecanica(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    MusicManager::getInstancia().reproducir(musicaMetalmecanica_wav, musicaMetalmecanica_wav_len, "metalmecanica", true, 70.f);
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    // =========================
    // Fondo
    // =========================
    if (!tFondoMetalmecanica.loadFromMemory(fondoNexus_png, fondoNexus_png_len)){
        std::cerr << "Error al cargar fondo de metalmecanica\n";
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
    /* std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta metalmecanica4.png",
        "../assets/nexusxd/puerta metalmecanica4.png"
    }; */

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
        if (i == 0)
        {
            if (!puertasTextures[i].loadFromMemory(puertaMetalmecanica4_png, puertaMetalmecanica4_png_len)) {
                std::cerr << "Warning: No se pudo cargar Imagen\n";
                sf::Image img;
                img.create(120, 200, sf::Color(150,150,150));
                puertasTextures[i].loadFromImage(img);
            }
        } else if (i == 1)
        {
            if (!puertasTextures[i].loadFromMemory(puertaMetalmecanica4_png, puertaMetalmecanica4_png_len)) {
                std::cerr << "Warning: No se pudo cargar Imagen\n";
                sf::Image img;
                img.create(120, 200, sf::Color(150,150,150));
                puertasTextures[i].loadFromImage(img);
            }
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
    if (!fuente.loadFromMemory(Bangers_Regular_ttf, Bangers_Regular_ttf_len)) {
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

                juego->backspace = false;
                juego->enter = false;
                juego->esc = true;
                juego->flechas = true;
                juego->mouse = false;
                juego->space = true;
                juego->wasd = true;

                juego->seleccionado = "minijuegoMecanicaIndustrial";
                juego->instrucciones = "Binevenido al hogar de las máquinas, aquí como buen mecánico industrial (P5), vas a tener que desechar al contenedor las piezas que no coincidan con la que se muestran en la pantalla. Demuestrale a los demás tu percepción e intuición visual.";
                juego->botones = true;
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P5
            case 1:
                juego->cambiarAPrograma = 12;

                juego->backspace = false;
                juego->enter = false;
                juego->esc = true;
                juego->flechas = false;
                juego->mouse = true;
                juego->space = false;
                juego->wasd = false;

                juego->seleccionado = "minijuegoSoldadura";
                juego->instrucciones = "Acá nos vamos a poner un poco más calientes, porqué en el siguiente vamos a explorar los arcos eléctricos para permitirno unir piezas de metal en el programa de soldadura (P12). Ten mucho cuidado en dejar soldaduras sin pulir, a parte de que es un trabajo mal hecho no es estético";
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

    int nuevaPuerta = -1;
    sf::FloatRect jugadorBounds = jugador.getBounds();

    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();
        const float expand = std::max(3.f, b.width * 0.02f);
        b.left -= expand;
        b.top -= expand;
        b.width += expand * 2.f;
        b.height += expand * 2.f;

        if (jugadorBounds.intersects(b)) {
            nuevaPuerta = i;
        }

        puertasSprites[i].setColor(i == nuevaPuerta ? coloresBrillo[i] : sf::Color::White);
    }

    puertaCercana = nuevaPuerta;
}

// =========================
// RENDERIZAR
// =========================
void Metalmecanica::renderizar(sf::RenderWindow& window)
{
    window.clear();
    window.draw(FondoMetalmecanica);

    std::vector<std::string> nombresTalleres = {
        "Mecánica industrial",
        "Soldadura"
    };

    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        window.draw(puertasSprites[i]);

        // Texto encima de la "P"
        sf::Text nombreTaller;
        nombreTaller.setFont(fuente);
        nombreTaller.setString(utf8_to_wstring(wrapTextString(nombresTalleres[i], fuente, 30, 500)));
        nombreTaller.setCharacterSize(30);

        if (juego->minijuegosPasados[4] && i == 0)
        {
            nombreTaller.setFillColor(sf::Color(96, 96, 96));
        } else if (juego->minijuegosPasados[11] && i == 1)
        {
            nombreTaller.setFillColor(sf::Color(96, 96, 96));
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
