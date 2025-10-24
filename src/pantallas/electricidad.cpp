#include "../../include/pantallas/electricidad.h"
/* #include "../../include/minijuegoElectronicaYControl/minijuegoElectronicaYControl.h"
#include "../../include/minijuegoAutotronica/minijuegoAutotronica.h"
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"
#include "../../include/minijuegoRedes/minijuegoRedes.h" */
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"

#include <iostream>
#include <cmath>

Electricidad::Electricidad(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    // Fondo (ruta según tu repo)
    if (!tFondoElectricidad.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png")) {
        std::cerr << "Error al cargar fondo de Electricidad\n";
    } else {
        FondoElectricidad.setTexture(tFondoElectricidad);
        float fX = sf::VideoMode::getDesktopMode().width / FondoElectricidad.getGlobalBounds().width;
        float fY = sf::VideoMode::getDesktopMode().height / FondoElectricidad.getGlobalBounds().height;
        FondoElectricidad.setScale(fX, fY);
    }

    // Posición inicial del jugador (centro)
    float width = (float)sf::VideoMode::getDesktopMode().width;
    float height = (float)sf::VideoMode::getDesktopMode().height;
    jugador.setPosition((width / 2) - jugador.getBounds().width / 2,
                        (height / 2) - jugador.getBounds().height / 2);

    // Textura de las puertas
    std::string rutaPuerta = "../assets/nexusxd/puerta electricidad2.png";

    // Colores de brillo (1: cyan, 2: amarillo, 3: verde, 4: azul)
    coloresBrillo = {
        sf::Color(0, 200, 255, 220),   // Cian (bonito)
        sf::Color(255, 220, 80, 220),  // Amarillo suave
        sf::Color(0, 200, 120, 220),   // Verde menta
        sf::Color(80, 140, 255, 220)   // Azul eléctrico
    };

    // Tamaño base y factor (usa 1.2 para +20%)
    const float factorAumento = 1.50f;
    const float baseW = 120.f;
    const float baseH = 200.f;
    const float puertaW = baseW * factorAumento;
    const float puertaH = baseH * factorAumento;

    const float separacion = 220.f;
    const float totalAncho = (puertaW * 4) + (separacion * 3);
    const float startX = (width / 2) - (totalAncho / 2);
    const float posY = 120.f;

    // Cargar texturas y crear sprites
    puertasTextures.resize(4);
    puertasSprites.resize(4);

    for (int i = 0; i < 4; ++i) {
        if (!puertasTextures[i].loadFromFile(rutaPuerta)) {
            std::cerr << "Warning: No se pudo cargar " << rutaPuerta << " (puerta " << i << ")\n";
            // fallback por si no carga
            sf::Image img; img.create((unsigned)baseW, (unsigned)baseH, sf::Color(180,180,180));
            puertasTextures[i].loadFromImage(img);
        }

        puertasSprites[i].setTexture(puertasTextures[i]);
        sf::Vector2u texSize = puertasTextures[i].getSize();
        float scaleX = 1.f, scaleY = 1.f;
        if (texSize.x > 0 && texSize.y > 0) {
            scaleX = puertaW / (float)texSize.x;
            scaleY = puertaH / (float)texSize.y;
        }
        puertasSprites[i].setScale(scaleX, scaleY);
        puertasSprites[i].setPosition(startX + i * (puertaW + separacion), posY);
        puertasSprites[i].setColor(sf::Color::White);
    }

    // Al entrar a la pantalla, ignorar inputs hasta que el usuario suelte la tecla
    ignoreInput = true;
}

void Electricidad::ManejarEvento(sf::Event evento) {
    // ESC siempre sale
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
    }

    // Si estamos ignorando inputs, levantamos el flag cuando hay KeyReleased
    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased) {
            ignoreInput = false;
            std::cout << "[Electricidad] input habilitado\n";
        }
        return;
    }

    // Enter → cambia de pantalla según la puerta
    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter) {
        std::cout << "[Electricidad] Enter released; puertaCercana = " << puertaCercana << std::endl;
        fflush(stdout);

        if (puertaCercana != -1) {
            std::cout << "[Electricidad] intentamos cambiar desde puerta " << puertaCercana << std::endl;
            fflush(stdout);

            switch (puertaCercana) {
                case 0:
                    juego->cambiarAPrograma = 10;
                    break;
                case 1:
                    juego->cambiarAPrograma = 7;
                    break;
                case 2:
                    juego->cambiarAPrograma = 4;
                    break;
                case 3:
                    juego->cambiarAPrograma = 11;
                    break;
                default:
                    std::cout << "[Electricidad] puertaCercana fuera de rango\n";
                    break;
            }
            juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
        } else {
            std::cout << "[Electricidad] Enter pero sin puerta cercana\n";
        }
    }
}

void Electricidad::actualizar() {
    jugador.update(sf::VideoMode::getDesktopMode());

    // Buscamos la puerta más cercana
    int nuevaPuerta = -1;
    float mejorDist = 1e9f;

    sf::FloatRect jugadorBounds = jugador.getBounds();
    float jCenterX = jugadorBounds.left + jugadorBounds.width * 0.5f;
    float jCenterY = jugadorBounds.top  + jugadorBounds.height * 0.5f;

    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();

        // Expandimos área de detección
        const float expand = std::max(30.f, b.width * 0.18f);
        b.left   -= expand;
        b.top    -= expand;
        b.width  += expand * 2.f;
        b.height += expand * 2.f;

        if (!jugadorBounds.intersects(b)) {
            puertasSprites[i].setColor(sf::Color::White);
            continue;
        }

        float pCenterX = b.left + b.width * 0.5f;
        float pCenterY = b.top  + b.height * 0.5f;
        float dx = pCenterX - jCenterX;
        float dy = pCenterY - jCenterY;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dist < mejorDist) {
            mejorDist = dist;
            nuevaPuerta = i;
        }
    }

    // Aplicar brillo o restaurar color
    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        if (i == nuevaPuerta)
            puertasSprites[i].setColor(coloresBrillo[i]);
        else
            puertasSprites[i].setColor(sf::Color::White);
    }

    puertaCercana = nuevaPuerta;
}

void Electricidad::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(FondoElectricidad);

    for (auto& s : puertasSprites)
        window.draw(s);

    window.draw(jugador);
}
