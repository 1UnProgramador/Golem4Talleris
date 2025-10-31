#include "../../include/minijuegorandomxd/minijuegorandomxd.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/pantallas/DisenoTecnico.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cmath>

minijuegorandomxd::minijuegorandomxd(Juego* juego, Dificultad d)
    : Pantalla(juego),
      jugador(0, 0),
      dificultad(d),
      fadeActivo(false),
      fadeAlpha(0.f),
      victoria(false),
      mostrarBien(false),
      mostrarTiempoAgotado(false),
      timerBien(0.f)
{
    rows = 20;
    cols = 20;

    // tiempos según dificultad
    if (dificultad == FACIL) tiempoRestante = 30.0f;
    else tiempoRestante = 80.0f;

    // cargar fondo diseño técnico
    if (!fondoTextura.loadFromFile("../assets/fondoDiseno.png")) {
        std::cerr << "Error al cargar fondo diseño técnico\n";
    } else {
        fondo.setTexture(fondoTextura);
        float width  = (float)sf::VideoMode::getDesktopMode().width;
        float height = (float)sf::VideoMode::getDesktopMode().height;
        fondo.setScale(width / fondo.getGlobalBounds().width, height / fondo.getGlobalBounds().height);
        fondo.setPosition(0.f, 0.f);
    }

    // fuente
    if (!font.loadFromFile("../assets/textos/Bangers-Regular.ttf")) {
        std::cerr << "Warning: no se pudo cargar fuente ../assets/textos/Bangers-Regular.ttf.\n";
    } else {
        textoNivel.setFont(font);
        textoNivel.setCharacterSize(36);
        textoNivel.setStyle(sf::Text::Bold);

        textoCrono.setFont(font);
        textoCrono.setCharacterSize(32);
        textoCrono.setStyle(sf::Text::Bold);
    }

    // shapes base
    pixelShape.setOrigin(0, 0);
    cursorShape.setSize(sf::Vector2f((float)movimiento, (float)movimiento));
    cursorShape.setFillColor(sf::Color(0, 0, 0, 0));
    cursorShape.setOutlineThickness(2);
    cursorShape.setOutlineColor(sf::Color::Yellow);

    // overlay fade
    fadeRect.setSize(sf::Vector2f((float)sf::VideoMode::getDesktopMode().width,
                                  (float)sf::VideoMode::getDesktopMode().height));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    // crear patrón y grids
    generarPatron(dificultad);
    iniciarGrids();
    badCutTimer.assign(rows, std::vector<float>(cols, 0.0f));

    deltaClock.restart();
    cronoActivo = true;
}

/* ---------------- PATTERNS ---------------- */
void minijuegorandomxd::generarPatron(Dificultad d) {
    targetGrid.assign(rows, std::vector<bool>(cols, false));
    if (d == FACIL) generarScrewPattern();
    else generarRimPattern();
}

void minijuegorandomxd::generarScrewPattern() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            targetGrid[r][c] = false;

    int cx = cols / 2;
    int headR = 3;

    for (int c = cx - 3; c <= cx + 3; ++c) {
        if (c >= 0 && c < cols) {
            targetGrid[headR][c] = true;
            targetGrid[headR + 1][c] = true;
        }
    }

    if (cx >= 0 && cx + 1 < cols) {
        targetGrid[headR][cx] = false;
    }

    int start = headR + 2;
    int len = 8;
    for (int i = 0; i < len; ++i) {
        int r = start + i;
        if (r < 0 || r >= rows) continue;
        int offset = (i % 2 == 0) ? 0 : 1;
        if (cx - 1 + offset >= 0 && cx + offset < cols) {
            targetGrid[r][cx - 1 + offset] = true;
            targetGrid[r][cx + offset] = true;
        }
    }

    int tipR = start + len;
    if (tipR < rows) {
        targetGrid[tipR][cx] = true;
        if (tipR + 1 < rows) targetGrid[tipR + 1][cx] = true;
    }
}

void minijuegorandomxd::generarRimPattern() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            targetGrid[r][c] = false;

    int cx = cols / 2;
    int cy = rows / 2;
    int outer = 7;
    int inner = 3;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int dr = r - cy;
            int dc = c - cx;
            float dist = std::sqrt((float)(dr * dr + dc * dc));
            if (dist <= outer + 0.4f && dist >= inner - 0.4f)
                targetGrid[r][c] = true;
        }
    }

    for (int i = 0; i < 6; ++i) {
        float ang = (float)i * (2.0f * 3.14159265f / 6.0f);
        int rr = cy + (int)((inner + outer) * 0.5f * std::sin(ang));
        int cc = cx + (int)((inner + outer) * 0.5f * std::cos(ang));
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc) {
                int rr2 = rr + dr;
                int cc2 = cc + dc;
                if (rr2 >= 0 && rr2 < rows && cc2 >= 0 && cc2 < cols)
                    targetGrid[rr2][cc2] = false;
            }
    }
}

/* ---------------- INITS ---------------- */
void minijuegorandomxd::iniciarGrids() {
    metalGrid.assign(rows, std::vector<bool>(cols, true));
    cursorCol = cols / 2;
    cursorRow = rows / 2;
}

/* ---------------- EVENTOS ---------------- */
void minijuegorandomxd::ManejarEvento(sf::Event event) {
    if (fadeActivo) return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
            return;
        }

        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
            if (cursorCol > 0) cursorCol--;
        }
        else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
            if (cursorCol < cols - 1) cursorCol++;
        }
        else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
            if (cursorRow > 0) cursorRow--;
        }
        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
            if (cursorRow < rows - 1) cursorRow++;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (metalGrid[cursorRow][cursorCol]) {
                metalGrid[cursorRow][cursorCol] = false;
                badCutTimer[cursorRow][cursorCol] = 0.8f;
            }
        }
        else if (event.key.code == sf::Keyboard::BackSpace) {
            metalGrid[cursorRow][cursorCol] = true;
        }
    }
}

/* ---------------- ACTUALIZACIÓN ---------------- */
void minijuegorandomxd::actualizar() {
    float delta = deltaClock.restart().asSeconds();

    // cronómetro
    if (!fadeActivo && cronoActivo) {
        tiempoRestante -= delta;
        if (tiempoRestante <= 0.0f && !mostrarTiempoAgotado) {
            mostrarTiempoAgotado = true;
            timerBien = 2.0f;
            cronoActivo = false;
            fadeActivo = true;
            fadeAlpha = 0.f;
        }
    }

    // destellos
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (badCutTimer[r][c] > 0.0f) {
                badCutTimer[r][c] -= delta;
                if (badCutTimer[r][c] < 0.0f) badCutTimer[r][c] = 0.0f;
            }

    // victoria
    if (!victoria && verificarVictoria()) {
        victoria = true;
        mostrarBien = true;
        timerBien = 2.0f;
        fadeActivo = true;
        fadeAlpha = 0.f;
    }

    if (mostrarBien || mostrarTiempoAgotado) {
        timerBien -= delta;
        if (timerBien < 0.0f) timerBien = 0.0f;
    }

    // fade
    if (fadeActivo) {
        fadeAlpha += delta * 180.0f;
        if (fadeAlpha > 255.f) fadeAlpha = 255.f;
        fadeRect.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)fadeAlpha));

        if (fadeAlpha >= 255.f) {
            juego->minijuegosPasados[8] = true;
            juego->cambiarPantalla(std::make_unique<DisenoTecnico>(juego));
            return;
        }
    }
}

/* ---------------- VICTORIA ---------------- */
bool minijuegorandomxd::verificarVictoria() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (targetGrid[r][c] != !metalGrid[r][c])
                return false;
    return true;
}

/* ---------------- RENDER ---------------- */
void minijuegorandomxd::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(fondo);

    float screenW = (float)sf::VideoMode::getDesktopMode().width;
    float screenH = (float)sf::VideoMode::getDesktopMode().height;

    float marginX = 60.0f;
    float marginY = 100.0f;
    float usableW = screenW - marginX * 2;
    float usableH = screenH - marginY * 2;
    float halfW = usableW / 2.0f;
    float cellW = (halfW) / (float)cols;
    float cellH = usableH / (float)rows;
    float cellSize = std::min(cellW, cellH);
    float leftX = marginX;
    float rightX = marginX + halfW + cellSize * 1.0f;
    float topY = marginY;

    // texto
    if (font.getInfo().family != "") {
        std::string nivelStr = (dificultad == FACIL) ? "NIVEL: FACIL" : "NIVEL: DIFICIL";
        textoNivel.setString(nivelStr);
        textoNivel.setPosition(screenW / 2 - textoNivel.getGlobalBounds().width / 2, 20);
        window.draw(textoNivel);

        int segundos = (int)std::ceil(tiempoRestante);
        textoCrono.setString(std::to_string(segundos) + "s");
        textoCrono.setPosition(20, 20);
        window.draw(textoCrono);
    }

    pixelShape.setSize(sf::Vector2f(cellSize, cellSize));

    sf::Color screenFill(15, 60, 30);
    sf::Color screenPixel(80, 200, 160);
    sf::Color metalNormal(90, 90, 90);
    sf::Color metalSelected(160, 160, 160);
    sf::Color metalCorrect(0, 200, 0);
    sf::Color metalWrong(200, 0, 0);

    // bordes
    sf::RectangleShape borderLeft(sf::Vector2f(cellSize*cols, cellSize*rows));
    borderLeft.setPosition(leftX, topY);
    borderLeft.setOutlineThickness(2.f);
    borderLeft.setOutlineColor(sf::Color::White);
    borderLeft.setFillColor(sf::Color::Transparent);
    borderLeft.setOutlineColor(sf::Color(200,200,255));
    window.draw(borderLeft);

    sf::RectangleShape borderRight(sf::Vector2f(cellSize*cols, cellSize*rows));
    borderRight.setPosition(rightX, topY);
    borderRight.setOutlineThickness(2.f);
    borderRight.setOutlineColor(sf::Color::White);
    borderRight.setFillColor(sf::Color::Transparent);
    borderRight.setOutlineColor(sf::Color(200,200,255));
    window.draw(borderRight);

    // izquierda
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c) {
            float x = leftX + c * cellSize;
            float y = topY + r * cellSize;
            pixelShape.setPosition(x, y);
            pixelShape.setFillColor(targetGrid[r][c] ? screenPixel : screenFill);
            window.draw(pixelShape);
        }

    // derecha
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c) {
            float x = rightX + c * cellSize;
            float y = topY + r * cellSize;
            pixelShape.setPosition(x, y);
            pixelShape.setFillColor(metalGrid[r][c] ? metalNormal : metalSelected);
            window.draw(pixelShape);

            if (badCutTimer[r][c] > 0.0f) {
                sf::RectangleShape flash(sf::Vector2f(cellSize, cellSize));
                flash.setPosition(x, y);
                flash.setFillColor(targetGrid[r][c] ? metalCorrect : metalWrong);
                window.draw(flash);
            }
        }

    // líneas cuadrícula (izquierda y derecha completas)
    sf::RectangleShape line;
    line.setFillColor(sf::Color(0, 0, 0, 100));

    // verticales
    for (int c = 0; c <= cols; ++c) {
        float lx = leftX + c * cellSize;
        float rx = rightX + c * cellSize;
        line.setSize(sf::Vector2f(1.0f, cellSize * rows));
        line.setPosition(lx, topY);
        window.draw(line);
        line.setPosition(rx, topY);
        window.draw(line);
    }

    // horizontales
    for (int r = 0; r <= rows; ++r) {
        float ly = topY + r * cellSize;
        line.setSize(sf::Vector2f(cellSize * cols, 1.0f));
        line.setPosition(leftX, ly);
        window.draw(line);
        line.setPosition(rightX, ly);
        window.draw(line);
    }

    // cursor
    float cursorX = rightX + cursorCol * cellSize;
    float cursorY = topY + cursorRow * cellSize;
    cursorShape.setSize(sf::Vector2f(cellSize, cellSize));
    cursorShape.setPosition(cursorX, cursorY);
    window.draw(cursorShape);

    // mensajes
    if ((mostrarBien || mostrarTiempoAgotado) && font.getInfo().family != "") {
        std::string mensaje = mostrarBien ? "Bien hecho!" : "Mejor suerte la proxima";
        sf::Text text(mensaje, font, 48);
        text.setStyle(sf::Text::Bold);
        text.setPosition(screenW / 2.f - text.getGlobalBounds().width / 2.f,
                         screenH / 2.f - text.getGlobalBounds().height / 2.f);
        window.draw(text);
    }

    if (fadeActivo)
        window.draw(fadeRect);

    window.draw(jugador);
}
