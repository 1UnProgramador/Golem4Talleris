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
    MusicManager::getInstancia().reproducir(musicaElectricidad_wav, musicaElectricidad_wav_len, "electricidad", true, 70.f);
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

                juego->backspace = false;
                juego->enter = false;
                juego->esc = true;
                juego->flechas = false;
                juego->mouse = true;
                juego->space = false;
                juego->wasd = false;

                juego->seleccionado = "minijuegoMecatronica";
                juego->botones = true;
                juego->instrucciones = "Algunas cosas de mecatrónica (P4) se pueden aplicar muy bien a la vida cotidiana, ¿Sabías? El siguiente minijuego consiste en pasar por un lente algún objeto para decidir en que contenedor de reciclaje va. ¡Aprende a reciclar mientras juegas, todo por un mundo mejor!";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P4
            case 1:
                juego->cambiarAPrograma = 7;

                juego->backspace = false;
                juego->enter = true;
                juego->esc = true;
                juego->flechas = false;
                juego->mouse = true;
                juego->space = false;
                juego->wasd = false;

                juego->seleccionado = "minijuegoAutotronica";
                juego->botones = true;
                juego->instrucciones = "Vamos con una trivia, ¿Con qué reparo qué componente? Piensa muy bien tus opciones de respuesta, demuéstrate a ti mismo de que eres capaz de pensar como un estudiante del programa de Autotrónica, P7. Para reparar un componente le das click a el y a la opción que creas correcta, y le das enter.";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P7
            case 2:
                juego->cambiarAPrograma = 10;

                juego->backspace = false;
                juego->enter = true;
                juego->esc = true;
                juego->flechas = true;
                juego->mouse = false;
                juego->space = false;
                juego->wasd = true;

                juego->seleccionado = "minijuegoElectronicaYControl";
                juego->botones = true;
                juego->instrucciones = "¿Alguna vez has usado una impresora 3D? En este minijuego vas a tener que usar el puntero de la impresora para crear un modelo pre-definido (el modelo esta sombreado), y mucho cuidado, tienes que dejar la pieza tal cuál como esta, si no no estariamos en  el programa de electrónica y control, P10.";
                juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
                break; // P10
            case 3:
                juego->cambiarAPrograma = 11;
                juego->seleccionado = "minijuegoRedes";

                juego->backspace = false;
                juego->enter = false;
                juego->esc = true;
                juego->flechas = false;
                juego->mouse = true;
                juego->space = false;
                juego->wasd = false;

                juego->botones = true;
                juego->instrucciones = "El siguiente minijuego de redes eléctricas (P11), puede ser un poco complicado así que presta atención: Va a fluir electricidad por los cables amarillos (así que cómo no pueden haber fugas de electricidad TODOS tienen que estar conectados), inicia por abajo y sale por arriba en la dirección que indica las flechas. ¡Ánimo!";
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
        "Mecatrónica",
        "Autotrónica",
        "Electrónica y control",
        "Redes electricas"
    };

    // Puertas + texto
    for (int i = 0; i < 4; ++i) {
        window.draw(puertasSprites[i]);

        // Texto encima de la "P"
        sf::Text nombreTaller;
        nombreTaller.setFont(fuente);
        nombreTaller.setString(utf8_to_wstring(wrapTextString(nombresTalleres[i], fuente, 30, 500)));
        nombreTaller.setCharacterSize(30);

        if (juego->minijuegosPasados[3] && i == 0)
        {
            nombreTaller.setFillColor(sf::Color(255, 204, 0));
        } else if (juego->minijuegosPasados[6] && i == 1)
        {
            nombreTaller.setFillColor(sf::Color(255, 204, 0));
        } else if (juego->minijuegosPasados[9] && i == 2)
        {
            nombreTaller.setFillColor(sf::Color(255, 204, 0));
        } else if (juego->minijuegosPasados[10] && i == 3)
        {
            nombreTaller.setFillColor(sf::Color(255, 204, 0));
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
        window.draw(textosPuertas[i]);  // P4, P7, P10, P11
    }

    window.draw(jugador);
}
