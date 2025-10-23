#include "../../include/pantallas/informatica.h"
#include "../../include/minijuegoPonchar/minijuegoPonchar.h"
#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/minijuegoTangram/minijuegoTangram.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"

#include <iostream>
#include <cmath>

Informatica::Informatica(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    // Fondo (ruta según tu repo)
    if (!tFondoInformatica.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png")) {
        std::cerr << "Error al cargar fondo de informática\n";
    } else {
        FondoInformatica.setTexture(tFondoInformatica);
        float fX = sf::VideoMode::getDesktopMode().width / FondoInformatica.getGlobalBounds().width;
        float fY = sf::VideoMode::getDesktopMode().height / FondoInformatica.getGlobalBounds().height;
        FondoInformatica.setScale(fX, fY);
    }

    // Posición inicial del jugador (centro)
    float width = (float)sf::VideoMode::getDesktopMode().width;
    float height = (float)sf::VideoMode::getDesktopMode().height;
    jugador.setPosition((width / 2) - jugador.getBounds().width / 2,
                        (height / 2) - jugador.getBounds().height / 2);

    // Textura de las puertas (todas iguales)
    std::string rutaPuerta = "../assets/nexusxd/puerta informatica1.png";

    // Colores de brillo (1:Cyan, 2:Amarillo, 3:Verde)
    coloresBrillo = {
        sf::Color(0, 200, 255, 220),   // Cian (bonito)
        sf::Color(255, 220, 80, 220),  // Amarillo suave
        sf::Color(0, 200, 120, 220)    // Verde menta
    };

    // Tamaño base y factor (usa 1.2 para +20%)
    const float factorAumento = 1.50f;
    const float baseW = 120.f;
    const float baseH = 200.f;
    const float puertaW = baseW * factorAumento;
    const float puertaH = baseH * factorAumento;

    const float separacion = 250.f;
    const float startX = (width / 2) - ((puertaW * 3 + separacion * 2) / 2);
    const float posY = 120.f;

    // Cargar texturas y crear sprites
    puertasTextures.resize(3);
    puertasSprites.resize(3);

    for (int i = 0; i < 3; ++i) {
        if (!puertasTextures[i].loadFromFile(rutaPuerta)) {
            std::cerr << "Warning: No se pudo cargar " << rutaPuerta << " (puerta " << i << ")\n";
            // fallback
            sf::Image img; img.create((unsigned)baseW, (unsigned)baseH, sf::Color(150,150,150));
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

void Informatica::ManejarEvento(sf::Event evento) {
    // ESC siempre sale
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
    }

    // Si estamos ignorando inputs, levantamos el flag cuando hay KeyReleased (cualquier tecla)
    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased) {
            ignoreInput = false;
            std::cout << "[Informatica] input habilitado\n";
        }
        return;
    }

    // Usar KeyReleased para Enter para evitar pulsaciones "pegadas"
    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter) {
        std::cout << "[Informatica] Enter released; puertaCercana = " << puertaCercana << std::endl;
        fflush(stdout);

        if (puertaCercana != -1) {
            // Debug antes del cambio
            std::cout << "[Informatica] intentamos cambiar desde puerta " << puertaCercana << std::endl;
            fflush(stdout);

            switch (puertaCercana) {
                case 0:
                    juego->cambiarPantalla(std::make_unique<minijuegoPonchar>(juego));
                    break;
                case 1:
                    juego->cambiarPantalla(std::make_unique<minijuegoPaginaWeb>(juego));
                    break;
                case 2:
                    juego->cambiarPantalla(std::make_unique<minijuegoTangram>(juego));
                    break;
                default:
                    std::cout << "[Informatica] puertaCercana fuera de rango\n";
                    break;
            }
        } else {
            std::cout << "[Informatica] Enter pero sin puerta cercana\n";
        }
    }
}

void Informatica::actualizar() {
    // Actualiza el jugador (tu método existente)
    jugador.update(sf::VideoMode::getDesktopMode());

    // Buscamos la puerta más cercana válida
    int nuevaPuerta = -1;
    float mejorDist = 1e9f;

    sf::FloatRect jugadorBounds = jugador.getBounds();
    float jCenterX = jugadorBounds.left + jugadorBounds.width * 0.5f;
    float jCenterY = jugadorBounds.top  + jugadorBounds.height * 0.5f;

    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        sf::FloatRect b = puertasSprites[i].getGlobalBounds();

        // expandimos bounds para detección más permisiva
        const float expand = std::max(30.f, b.width * 0.18f);
        b.left   -= expand;
        b.top    -= expand;
        b.width  += expand * 2.f;
        b.height += expand * 2.f;

        // primer filtro: intersects con bounds ampliado
        if (!jugadorBounds.intersects(b)) {
            // restaurar color si no intersecta
            puertasSprites[i].setColor(sf::Color::White);
            continue;
        }

        // si intersecta, medimos distancia euclidiana entre centros (más precisa)
        float pCenterX = b.left + b.width * 0.5f;
        float pCenterY = b.top  + b.height * 0.5f;
        float dx = pCenterX - jCenterX;
        float dy = pCenterY - jCenterY;
        float dist = std::sqrt(dx*dx + dy*dy);

        // elegir la más cercana
        if (dist < mejorDist) {
            mejorDist = dist;
            nuevaPuerta = i;
        }
    }

    // aplicar color y debug
    for (int i = 0; i < (int)puertasSprites.size(); ++i) {
        if (i == nuevaPuerta) {
            puertasSprites[i].setColor(coloresBrillo[i]);
        } else {
            puertasSprites[i].setColor(sf::Color::White);
        }
    }

    if (nuevaPuerta != puertaCercana) {
        std::cout << "[Informatica] puertaCercana cambio: " << puertaCercana << " -> " << nuevaPuerta << std::endl;
        fflush(stdout);
    }

    puertaCercana = nuevaPuerta;
}

void Informatica::renderizar(sf::RenderWindow& window) {
    // dibujar fondo y puertas y jugador
    window.clear();
    window.draw(FondoInformatica);

    for (auto& s : puertasSprites) window.draw(s);
    window.draw(jugador);
}
