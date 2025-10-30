#include "../../include/minijuegoTopografia/minijuegoTopografia.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/pantallas/DisenoTecnico.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Topografia::Topografia(Juego* juego)
    : Pantalla(juego), jugador(0, 0), marcadorPosY(100), marcadorVelY(200),
      destelloTiempo(0), tiempoLimite(30.f), puntosMedidos(0)
{
    srand(static_cast<unsigned>(time(nullptr)));

    // Cargar fondo
    if (!fondoTextura.loadFromFile("../assets/fondoDiseno.png")) {
        std::cerr << "Error al cargar fondo Topografía\n";
    } else {
        fondo.setTexture(fondoTextura);
        float width  = sf::VideoMode::getDesktopMode().width;
        float height = sf::VideoMode::getDesktopMode().height;
        fondo.setScale(width / fondo.getGlobalBounds().width,
                       height / fondo.getGlobalBounds().height);
    }

    // Inicializar terreno y marcadores
    inicializarTerreno();

    if (!marcadorTextura.loadFromFile("../assets/Topografia/binye topo.png")) {
        std::cerr << "Error al cargar Marcador\n";
    }
    inicializarMarcadores();

    // Centrar el sprite del marcador
    for (auto& m : marcadores) {
        sf::FloatRect bounds = m.sprite.getLocalBounds();
        m.sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    // Destello
    destello.setSize(sf::Vector2f(sf::VideoMode::getDesktopMode().width,
                                  sf::VideoMode::getDesktopMode().height));
    destello.setFillColor(sf::Color(255, 0, 0, 0)); // transparente inicialmente
}

void Topografia::inicializarTerreno() {
    lineaTerreno.setPrimitiveType(sf::LinesStrip);
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;
    int puntos = 10;
    for (int i = 0; i < puntos; ++i) {
        float x = i * width / (puntos - 1);
        float y = height / 2 + (rand() % 200 - 100); // línea irregular
        lineaTerreno.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::White));
    }
}

void Topografia::inicializarMarcadores() {
    float width = sf::VideoMode::getDesktopMode().width;
    for (int i = 0; i < 5; ++i) {
        Marcador m;
        m.sprite.setTexture(marcadorTextura);
        float x = (i + 1) * width / 6; // distribuidos
        m.sprite.setPosition(x, marcadorPosY);
        marcadores.push_back(m);
    }
}

void Topografia::ManejarEvento(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
        }
        else if (event.key.code == sf::Keyboard::Enter && puntosMedidos < 5) {
            // Medir marcador actual
            Marcador& m = marcadores[puntosMedidos];
            float x = m.sprite.getPosition().x;

            // Encontrar altura del terreno más cercano
            float terrenoY = lineaTerreno[0].position.y;
            float minDist = std::abs(lineaTerreno[0].position.x - x);
            for (int i = 1; i < lineaTerreno.getVertexCount(); ++i) {
                float dist = std::abs(lineaTerreno[i].position.x - x);
                if (dist < minDist) {
                    minDist = dist;
                    terrenoY = lineaTerreno[i].position.y;
                }
            }

            // Usar el centro del sprite para comparar
            float spriteCentroY = m.sprite.getPosition().y;

            if (std::abs(spriteCentroY - terrenoY) < 15.f) {
                // ✅ acierto: pasa al siguiente punto
                m.correcto = true;
                m.medido = true;
                destello.setFillColor(sf::Color(0, 255, 0, 100));
                puntosMedidos++;
                destelloTiempo = 0.2f;
            } else {
                // ❌ fallo: puede volver a intentar
                destello.setFillColor(sf::Color(255, 0, 0, 100));
                destelloTiempo = 0.2f;
            }
        }
    }
}

void Topografia::actualizar() {
    float dt = reloj.restart().asSeconds();
    static float tiempoTranscurrido = 0.f;
    tiempoTranscurrido += dt;

    // Terminar si se acaba el tiempo
    if (tiempoTranscurrido >= tiempoLimite) {
        juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
        return;
    }

    // Actualizar marcador que está en movimiento
    if (puntosMedidos < 5) {
        Marcador& m = marcadores[puntosMedidos];
        marcadorPosY += marcadorVelY * dt;
        if (marcadorPosY < 50 || marcadorPosY > sf::VideoMode::getDesktopMode().height - 50)
            marcadorVelY = -marcadorVelY;
        m.sprite.setPosition(m.sprite.getPosition().x, marcadorPosY);
    }
    else {
        // Si ya logró los 5 antes del tiempo → volver a selección
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
        return;
    }

    // Destello
    if (destelloTiempo > 0) {
        destelloTiempo -= dt;
        if (destelloTiempo <= 0)
            destello.setFillColor(sf::Color(0, 0, 0, 0));
    }
}

void Topografia::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(fondo);
    window.draw(lineaTerreno);

    for (auto& m : marcadores)
        window.draw(m.sprite);

    window.draw(destello);
}
