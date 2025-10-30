#include "../../include/pantallas/PantallaSeleccionar.h"
/* #include "../../include/pantallas/informatica.h"
#include "../../include/pantallas/electricidad.h"
#include "../../include/pantallas/DiseñoTecnico.h"
#include "../../include/pantallas/Metalmecanica.h" */
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/logica/Juego.h"

#include <iostream>
#include <cmath>

PantallaSeleccionar::PantallaSeleccionar(Juego* juego)
    : Pantalla(juego), jugador(0, 0)
{
    // Fondo (usa la misma ruta que usas en otras pantallas)
    if (!tFondoNexus.loadFromFile("../assets/nexusxd/fondo nexus chatgpt1.png")) {
        std::cerr << "Error al cargar fondo nexus\n";
    } else {
        FondoNexus.setTexture(tFondoNexus);
        float fX = sf::VideoMode::getDesktopMode().width / FondoNexus.getGlobalBounds().width;
        float fY = sf::VideoMode::getDesktopMode().height / FondoNexus.getGlobalBounds().height;
        FondoNexus.setScale(fX, fY);
    }

    // Posición inicial del jugador al centro de la pantalla
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;

    jugador.setPosition((width / 2) - jugador.getBounds().width / 2,
                        (height / 2) - jugador.getBounds().height / 2);

    // Rutas de las texturas EXACTAS que dijiste
    std::vector<std::string> rutas = {
        "../assets/nexusxd/puerta informatica1.png",   // Informática
        "../assets/nexusxd/puerta electricidad2.png",  // Electricidad
        "../assets/nexusxd/puerta diseno3.png",  // Diseño Técnico (mismo archivo según tu repo)
        "../assets/nexusxd/puerta metalmecanica4.png"  // Metalmecánica
    };

    // Colores de brillo (1: cyan, 2: amarillo, 3: verde, 4: azul)
    coloresBrillo = {
        sf::Color(0, 200, 255, 220),   // Cian (bonito)
        sf::Color(255, 220, 80, 220),  // Amarillo suave
        sf::Color(0, 200, 120, 220),   // Verde menta
        sf::Color(80, 140, 255, 220)   // Azul eléctrico
    };

    // Tamaño base y factor: +50% (1.50f)
    const float factorAumento = 1.50f;
    const float baseW = 120.f;
    const float baseH = 200.f;
    const float puertaW = baseW * factorAumento;
    const float puertaH = baseH * factorAumento;

    // Separación / posición (ajustado como en tus otros archivos)
    const float separacion = 210.f;
    const float startX = (width / 2) - ((puertaW * 4 + separacion * 3) / 2);
    const float posY = 120.f;

    // Reservar y cargar
    puertasTextures.resize(4);
    puertasSprites.resize(4);

    for (int i = 0; i < 4; ++i) {
        if (!puertasTextures[i].loadFromFile(rutas[i])) {
            std::cerr << "Warning: no se pudo cargar " << rutas[i] << "\n";
            // fallback para evitar crash con texturas vacías
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

    // Evitar entrada pegada al entrar a la pantalla
    ignoreInput = true;
}

void PantallaSeleccionar::ManejarEvento(sf::Event evento) {
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
        exit(0);
    }

    if (ignoreInput) {
        if (evento.type == sf::Event::KeyReleased) {
            ignoreInput = false;
            std::cout << "[PantallaSeleccionar] input habilitado\n";
        }
        return;
    }

    // Usamos KeyReleased para Enter como en tu Informatica
    if (evento.type == sf::Event::KeyReleased && evento.key.code == sf::Keyboard::Enter) {
        std::cout << "[PantallaSeleccionar] Enter released; puertaCercana = " << puertaCercana << std::endl;
        fflush(stdout);

        if (puertaCercana != -1) {
            switch (puertaCercana) {
                case 0:
                    juego->cambiarAPrograma = 14;
                    juego->seleccionado = "imagenInformatica";
                    juego->instrucciones =  "Bienvenido a la especialidad de informatica, aca se extiende durante 3 programas: Mantenimiento electronico y de computadores (P1), diseño de paginas Web (P2) y diseno grafico asistido por computador (P3). El elemento central de este taller es la tecnologia, te aseguramos que te encantara, Suerte!";
                    break;
                case 1:
                    juego->cambiarAPrograma = 15;
                    juego->seleccionado = "imagenElectricidad";
                    juego->instrucciones =  "Bienvenido a la especialidad de Electricidad, aca se extiende durante 4 programas: Mecatrónica (P4), Autotrónica (P7), Electrónica y control (P10) y Redes Eléctricas (P11). El elemento central de este taller es La conversión, distribución y control inteligente de la energía eléctrica. ¡Aprende de él mientras desarrollas tu razonamiento lógico!";
                    break;
                case 2:
                    juego->cambiarAPrograma = 16;
                    juego->seleccionado = "imagenDiseno";
                    juego->instrucciones =  "Bienvenido a la especialidad de Metalmecánica, aca se extiende durante 3 programas: Diseño Arquitectónico (P6), Topografía (P8) y Diseño asistido por computador  (P9). El elemento central de este taller es la representación y materialización del espacio mediante herramientas tecnológicas y análisis del territorio.";
                    break;
                case 3:
                    juego->cambiarAPrograma = 17;
                    juego->seleccionado = "imagenMetalmecanica";
                    juego->instrucciones =  "Bienvenido a la especialidad de Metalmecánica, aca se extiende durante 2 programas: Mecánica industrial (P5), y Soldadura (P12). El elemento central de este taller es el dominio de los procesos que permiten dar forma, unir y optimizar componentes metálicos.";
                    break;
                default:
                    break;
            }
            juego->botones = false;
            juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
        } else {
            std::cout << "[PantallaSeleccionar] Enter pero sin puerta cercana\n";
        }
    }
}

void PantallaSeleccionar::actualizar() {
    // Actualiza el jugador tal como en Informatica
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
        std::cout << "[PantallaSeleccionar] puertaCercana cambio: " << puertaCercana << " -> " << nuevaPuerta << std::endl;
        fflush(stdout);
    }

    puertaCercana = nuevaPuerta;
}

void PantallaSeleccionar::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(FondoNexus);

    for (auto& s : puertasSprites) window.draw(s);

    window.draw(jugador);
}
