#include "../../include/minijuegoTopografia/minijuegoTopografia.h"
#include "../../include/pantallas/DisenoTecnico.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "../../src/logica/assetManager.h"

Topografia::Topografia(Juego* juego, DificultadTopo dif)
    : Pantalla(juego),
      jugador(0, 0),
      marcadorPosY(120.f),
      marcadorVelY(220.f),
      destelloTiempo(0.f),
      // Tiempos ajustados:
      tiempoLimite((dif == DificultadTopo::FACIL) ? 15.f : 20.f),
      tiempoTranscurrido(0.f),
      mostrarMensajeFinal(false),
      tiempoMensaje(0.f),
      puntosMedidos(0),
      dificultad(dif),
      // ATENCIÓN: victoria debe ir aquí si se declaró después de dificultad en el .h
      victoria(false), // <--- ¡AÑADIDO Y EN POSICIÓN CORRECTA!
      enterCooldown(0.5f),
      margenAcierto((dif == DificultadTopo::FACIL) ? 25.f : 15.f) // margenAcierto al final
{
    srand(static_cast<unsigned>(time(nullptr)));

    // --- fondo escalado a pantalla ---
    if (!fondoTextura.loadFromMemory(fondoDiseno_png, fondoDiseno_png_len)) {
        std::cerr << "Warning: no se pudo cargar ../assets/fondoDiseno.png\n";
    } else {
        fondo.setTexture(fondoTextura);
        float w = (float)sf::VideoMode::getDesktopMode().width;
        float h = (float)sf::VideoMode::getDesktopMode().height;
        fondo.setScale(w / fondo.getGlobalBounds().width, h / fondo.getGlobalBounds().height);
    }

    // --- zona de trabajo (rectángulo gris centrado) ---
    float screenW = (float)sf::VideoMode::getDesktopMode().width;
    float screenH = (float)sf::VideoMode::getDesktopMode().height;
    float zonaW = screenW * 0.85f;
    float zonaH = screenH * 0.60f;
    zonaTrabajo.setSize({zonaW, zonaH});
    zonaTrabajo.setFillColor(sf::Color(50, 50, 50, 200));
    zonaTrabajo.setOutlineColor(sf::Color(80, 80, 80, 220));
    zonaTrabajo.setOutlineThickness(3.f);
    zonaTrabajo.setOrigin(zonaW / 2.f, zonaH / 2.f);
    zonaTrabajo.setPosition(screenW / 2.f, screenH / 2.f);

    // --- generar terreno ---
    float leftStart = zonaTrabajo.getPosition().x - zonaW / 2.f;
    float rightEnd = zonaTrabajo.getPosition().x + zonaW / 2.f;

    if (dificultad == DificultadTopo::FACIL) {
        generarTerreno(terrenoPuntos1, leftStart, rightEnd, zonaTrabajo.getPosition().y, 60.f, 18);
    } else {
        generarTerreno(terrenoPuntos1, leftStart, rightEnd, zonaTrabajo.getPosition().y, 80.f, 10);
    }

    // --- marcador (Binye topo) ---
    if (!marcadorTextura.loadFromMemory(binyeTopo_png, binyeTopo_png_len)) {
        std::cerr << "Warning: no se pudo cargar ../assets/Topografia/binye topo.png\n";
    }
    inicializarMarcadores();

    // sprite más pequeño
    for (auto &m : marcadores) {
        sf::FloatRect b = m.sprite.getLocalBounds();
        float scale = (zonaH * 0.06f) / b.height;
        m.sprite.setScale(scale, scale);
        b = m.sprite.getLocalBounds();
        m.sprite.setOrigin(b.width / 2.f, b.height / 2.f);
    }

    // --- destello / oscurecer ---
    destello.setSize({screenW, screenH});
    destello.setFillColor(sf::Color(0, 0, 0, 0));

    // --- cronómetro texto ---
    if (!fuente.loadFromMemory(Bangers_Regular_ttf, Bangers_Regular_ttf_len)) {
        std::cerr << "Warning: no se pudo cargar ../assets/textos/Bangers-Regular.ttf\n";
    }
    textoCrono.setFont(fuente);
    textoCrono.setCharacterSize(28);
    textoCrono.setFillColor(sf::Color::White);
    textoCrono.setOutlineThickness(1.f);
    textoCrono.setOutlineColor(sf::Color::Black);
    textoCrono.setPosition(30.f, 20.f);

    // --- mensaje final (perder/ganar) ---
    mensajeFinal.setFont(fuente);
    mensajeFinal.setCharacterSize(56);
    mensajeFinal.setFillColor(sf::Color::White);
    sf::FloatRect mb = mensajeFinal.getLocalBounds();
    mensajeFinal.setOrigin(mb.width / 2.f, mb.height / 2.f);
    mensajeFinal.setPosition(screenW / 2.f, screenH / 2.f);

    clockEnter.restart();
}

/* --- Genera puntos para terreno (sin cambios) --- */
void Topografia::generarTerreno(std::vector<sf::Vector2f> &puntos, float xStart, float xEnd, float baseY, float amplitude, int nPoints) {
    puntos.clear();
    if (nPoints < 3) nPoints = 3;
    float span = xEnd - xStart;
    for (int i = 0; i < nPoints; ++i) {
        float t = (float)i / (nPoints - 1);
        float x = xStart + t * span;
        float noise = (std::rand() % 1000 / 1000.f - 0.5f) * 0.6f;
        float sine = std::sin(t * 3.1415f * (1.0f + (std::rand() % 3) / 2.0f));
        float y = baseY + sine * amplitude + noise * amplitude;
        puntos.emplace_back(x, y);
    }
}

/* --- muestreo lineal (sin cambios) --- */
float Topografia::muestrearTerreno(const std::vector<sf::Vector2f> &puntos, float x) const {
    if (puntos.empty()) return 0.f;
    if (x <= puntos.front().x) return puntos.front().y;
    if (x >= puntos.back().x) return puntos.back().y;
    for (size_t i = 0; i + 1 < puntos.size(); ++i) {
        const auto &a = puntos[i];
        const auto &b = puntos[i + 1];
        if (x >= a.x && x <= b.x) {
            float t = (x - a.x) / (b.x - a.x);
            return a.y + t * (b.y - a.y);
        }
    }
    return puntos.back().y;
}

/* --- inicializa los marcadores (sin cambios) --- */
void Topografia::inicializarMarcadores() {
    marcadores.clear();
    float zonaLeft = zonaTrabajo.getPosition().x - zonaTrabajo.getSize().x / 2.f;
    float zonaRight = zonaTrabajo.getPosition().x + zonaTrabajo.getSize().x / 2.f;
    float span = zonaRight - zonaLeft;

    int numMarcadores = (dificultad == DificultadTopo::FACIL) ? 5 : 10;

    float step = span / (numMarcadores + 1);

    for (int i = 0; i < numMarcadores; ++i) {
        MarcadorTopo m;
        m.sprite.setTexture(marcadorTextura);
        float x = zonaLeft + (i + 1) * step;
        m.sprite.setPosition(x, marcadorPosY);
        marcadores.push_back(m);
    }
}

/* --- Manejo de eventos (sin cambios) --- */
void Topografia::ManejarEvento(sf::Event event) {
    if (mostrarMensajeFinal) return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
            return;
        }

        if (event.key.code == sf::Keyboard::Enter && puntosMedidos < (int)marcadores.size()) {
            if (clockEnter.getElapsedTime().asSeconds() < enterCooldown) return;
            clockEnter.restart();

            MarcadorTopo &m = marcadores[puntosMedidos];
            float spriteCentroY = m.sprite.getPosition().y;
            float x = m.sprite.getPosition().x;
            float terrenoY = muestrearTerreno(terrenoPuntos1, x);

            if (std::abs(spriteCentroY - terrenoY) <= margenAcierto) {
                m.correcto = true;
                destello.setFillColor(sf::Color(0, 255, 0, 110));
                puntosMedidos++;
            } else {
                m.correcto = false;
                destello.setFillColor(sf::Color(255, 0, 0, 120));
            }
            m.medido = true;
            destelloTiempo = 0.18f;
        }
    }
}

/* --- actualizar (MODIFICADO) --- */
void Topografia::actualizar() {
    float dt = reloj.restart().asSeconds();

    // --- LÓGICA DE MENSAJE FINAL (Ganar/Perder) ---
    if (mostrarMensajeFinal) {
        tiempoMensaje += dt;
        // Esperar 2.0 segundos antes de cambiar de pantalla
        if (tiempoMensaje >= 2.0f) {
            juego->minijuegosPasados[7] = true;
            juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
        }
        return;
    }

    tiempoTranscurrido += dt;

    // 1. Condición de Victoria
    if (puntosMedidos >= (int)marcadores.size()) {
        mostrarMensajeGanar(); // Llama a la nueva función de victoria
        return;
    }

    // 2. Condición de Derrota por Tiempo
    if (tiempoTranscurrido >= tiempoLimite) {
        mostrarMensajePerder();
        return;
    }
    // --- FIN LÓGICA DE MENSAJE FINAL ---

    // 3. Movimiento normal del marcador
    MarcadorTopo &m = marcadores[puntosMedidos];
    marcadorPosY += marcadorVelY * dt;
    float topLimit = zonaTrabajo.getPosition().y - zonaTrabajo.getSize().y / 2.f + 40.f;
    float bottomLimit = zonaTrabajo.getPosition().y + zonaTrabajo.getSize().y / 2.f - 40.f;
    if (marcadorPosY < topLimit || marcadorPosY > bottomLimit) {
        marcadorVelY = -marcadorVelY;
        marcadorPosY = std::max(topLimit, std::min(bottomLimit, marcadorPosY));
    }
    m.sprite.setPosition(m.sprite.getPosition().x, marcadorPosY);

    // 4. Lógica del destello (flash)
    if (destelloTiempo > 0.f) {
        destelloTiempo -= dt;
        if (destelloTiempo <= 0.f) destello.setFillColor(sf::Color(0, 0, 0, 0));
    }

    // 5. Actualización del cronómetro
    float restante = std::max(0.f, tiempoLimite - tiempoTranscurrido);
    int segs = (int)std::ceil(restante);
    textoCrono.setString("Tiempo: " + std::to_string(segs) + "s");
}

/* --- renderizar (sin cambios) --- */
void Topografia::renderizar(sf::RenderWindow &window) {
    window.clear();
    window.draw(fondo);
    window.draw(zonaTrabajo);

    if (!terrenoPuntos1.empty()) {
        sf::VertexArray va(sf::LineStrip, terrenoPuntos1.size());
        for (size_t i = 0; i < terrenoPuntos1.size(); ++i) {
            va[i].position = terrenoPuntos1[i];
            va[i].color = sf::Color::White;
        }
        window.draw(va);
    }

    for (auto &m : marcadores) {
        sf::Sprite s = m.sprite;
        if (m.medido && m.correcto)
            s.setColor(sf::Color(180, 255, 180));
        else if (m.medido && !m.correcto)
            s.setColor(sf::Color(255, 180, 180));
        window.draw(s);
    }

    window.draw(textoCrono);
    if (destello.getFillColor().a > 0) window.draw(destello);

    if (mostrarMensajeFinal) window.draw(mensajeFinal);
}

/* --- mostrar mensaje perder (MODIFICADO) --- */
void Topografia::mostrarMensajePerder() {
    mostrarMensajeFinal = true;
    victoria = false; // Estado de derrota
    tiempoMensaje = 0.f;
    destello.setFillColor(sf::Color(0, 0, 0, 180));
    mensajeFinal.setString("Mejor suerte la proxima");
    sf::FloatRect mb = mensajeFinal.getLocalBounds();
    mensajeFinal.setOrigin(mb.width / 2.f, mb.height / 2.f);
}

/* --- NUEVA FUNCIÓN PARA MOSTRAR MENSAJE DE VICTORIA --- */
void Topografia::mostrarMensajeGanar() {
    mostrarMensajeFinal = true;
    victoria = true; // Estado de victoria
    tiempoMensaje = 0.f;
    // Oscurecimiento con un tinte verde claro para celebrar
    destello.setFillColor(sf::Color(50, 200, 50, 180));
    mensajeFinal.setString("Bien hecho");
    sf::FloatRect mb = mensajeFinal.getLocalBounds();
    mensajeFinal.setOrigin(mb.width / 2.f, mb.height / 2.f);
}