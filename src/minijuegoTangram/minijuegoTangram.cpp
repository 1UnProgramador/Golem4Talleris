#include "../../include/minijuegoTangram/minijuegoTangram.h"
#include "../../include/minijuegoAutotronica/minijuegoAutotronica.h"
#include "../../include/logica/Juego.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

std::vector<sf::Vector2f> posicionesObjetivos;
std::vector<float> rotacionObjetivos;

std::vector<sf::Vector2f> posicionesObjetivos2;
std::vector<float> rotacionObjetivos2;

minijuegoTangram::minijuegoTangram(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoInformatica.png");
    fondo.setTexture(tFondo);

    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    figura tG1;
    figura tG2;
    figura tM1;
    figura tP1;
    figura tP2;
    figura c1;
    figura p1;

    tG1.formaFigura.setPointCount(3);
    tG1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tG1.formaFigura.setPoint(1, sf::Vector2f(200, 0));
    tG1.formaFigura.setPoint(2, sf::Vector2f(0, 200));
    tG1.colorOriginal = sf::Color(255, 85, 0);
    tG1.formaFigura.setPosition(sf::Vector2f(200, 200));
    tG1.formaFigura.setOrigin(tG1.formaFigura.getGlobalBounds().width / 2, tG1.formaFigura.getGlobalBounds().height / 2);

    tG2.formaFigura.setPointCount(3);
    tG2.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tG2.formaFigura.setPoint(1, sf::Vector2f(200, 0));
    tG2.formaFigura.setPoint(2, sf::Vector2f(0, 200));
    tG2.colorOriginal = sf::Color::Red;
    tG2.formaFigura.setPosition(sf::Vector2f(400, 200));
    tG2.formaFigura.setOrigin(tG2.formaFigura.getGlobalBounds().width / 2, tG2.formaFigura.getGlobalBounds().height / 2);

    tM1.formaFigura.setPointCount(3);
    tM1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tM1.formaFigura.setPoint(1, sf::Vector2f(141, 0));
    tM1.formaFigura.setPoint(2, sf::Vector2f(0, 141));
    tM1.colorOriginal = sf::Color::Green;
    tM1.formaFigura.setPosition(sf::Vector2f(541, 141));
    tM1.formaFigura.setOrigin(tM1.formaFigura.getGlobalBounds().width / 2, tM1.formaFigura.getGlobalBounds().height / 2);

    tP1.formaFigura.setPointCount(3);
    tP1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tP1.formaFigura.setPoint(1, sf::Vector2f(100, 0));
    tP1.formaFigura.setPoint(2, sf::Vector2f(0, 100));
    tP1.colorOriginal = sf::Color(76, 0, 255);
    tP1.formaFigura.setPosition(sf::Vector2f(641, 100));
    tP1.formaFigura.setOrigin(tP1.formaFigura.getGlobalBounds().width / 2, tP1.formaFigura.getGlobalBounds().height / 2);

    tP2.formaFigura.setPointCount(3);
    tP2.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tP2.formaFigura.setPoint(1, sf::Vector2f(100, 0));
    tP2.formaFigura.setPoint(2, sf::Vector2f(0, 100));
    tP2.colorOriginal = sf::Color::Yellow;
    tP2.formaFigura.setPosition(sf::Vector2f(741, 100));
    tP2.formaFigura.setOrigin(tP2.formaFigura.getGlobalBounds().width / 2, tP2.formaFigura.getGlobalBounds().height / 2);

    c1.formaFigura.setPointCount(4);
    c1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    c1.formaFigura.setPoint(1, sf::Vector2f(100, 0));
    c1.formaFigura.setPoint(2, sf::Vector2f(100, 100));
    c1.formaFigura.setPoint(3, sf::Vector2f(0, 100));
    c1.colorOriginal = sf::Color::Blue;
    c1.formaFigura.setPosition(sf::Vector2f(841, 100));
    c1.formaFigura.setOrigin(c1.formaFigura.getGlobalBounds().width / 2, c1.formaFigura.getGlobalBounds().height / 2);

    p1.formaFigura.setPointCount(4);
    p1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    p1.formaFigura.setPoint(1, sf::Vector2f(141, 0));
    p1.formaFigura.setPoint(2, sf::Vector2f(212, 71));
    p1.formaFigura.setPoint(3, sf::Vector2f(71, 71));
    p1.colorOriginal = sf::Color::Magenta;
    p1.formaFigura.setPosition(sf::Vector2f(1000, 71));
    p1.formaFigura.setOrigin(p1.formaFigura.getGlobalBounds().width / 2, p1.formaFigura.getGlobalBounds().height / 2);

    figuras.push_back(tG1);
    figuras.push_back(tG2);
    figuras.push_back(tM1);
    figuras.push_back(tP1);
    figuras.push_back(tP2);
    figuras.push_back(c1);
    figuras.push_back(p1);

    figurasObjetivo = figuras;
    figurasObjetivo[0].formaFigura.setPosition(sf::Vector2f(229.5, 441.4));
    figurasObjetivo[0].formaFigura.setRotation(135);
    figurasObjetivo[0].formaFigura.setFillColor(sf::Color(34, 113,179));
    posicionesObjetivos.push_back(figurasObjetivo[0].formaFigura.getPosition());
    rotacionObjetivos.push_back(figurasObjetivo[0].formaFigura.getRotation());
    posicionesObjetivos2.push_back(sf::Vector2f(370, 442));
    rotacionObjetivos2.push_back(315);

    figurasObjetivo[1].formaFigura.setPosition(sf::Vector2f(370.5, 582));
    figurasObjetivo[1].formaFigura.setRotation(315);
    figurasObjetivo[1].formaFigura.setFillColor(sf::Color(34, 113,179));
    posicionesObjetivos.push_back(figurasObjetivo[1].formaFigura.getPosition());
    rotacionObjetivos.push_back(figurasObjetivo[1].formaFigura.getRotation());
    posicionesObjetivos2.push_back(sf::Vector2f(229, 584));
    rotacionObjetivos2.push_back(135);

    figurasObjetivo[2].formaFigura.setPosition(sf::Vector2f(300, 370.5)); /* */
    figurasObjetivo[2].formaFigura.setRotation(90);
    figurasObjetivo[2].formaFigura.setFillColor(sf::Color(34, 113,179));
    posicionesObjetivos.push_back(figurasObjetivo[2].formaFigura.getPosition());
    rotacionObjetivos.push_back(figurasObjetivo[2].formaFigura.getRotation());
    posicionesObjetivos2.push_back(sf::Vector2f(300, 371));
    rotacionObjetivos2.push_back(0);

    figurasObjetivo[3].formaFigura.setPosition(sf::Vector2f(300, 300)); /* */
    figurasObjetivo[3].formaFigura.setRotation(45);
    figurasObjetivo[3].formaFigura.setFillColor(sf::Color(34, 113,179));
    posicionesObjetivos.push_back(figurasObjetivo[3].formaFigura.getPosition());
    rotacionObjetivos.push_back(figurasObjetivo[3].formaFigura.getRotation());
    posicionesObjetivos2.push_back(sf::Vector2f(300, 300.5));
    rotacionObjetivos2.push_back(45);

    figurasObjetivo[4].formaFigura.setPosition(sf::Vector2f(158.7, 723.8));
    figurasObjetivo[4].formaFigura.setRotation(135);
    figurasObjetivo[4].formaFigura.setFillColor(sf::Color(34, 113,179));
    posicionesObjetivos.push_back(figurasObjetivo[4].formaFigura.getPosition());
    rotacionObjetivos.push_back(figurasObjetivo[4].formaFigura.getRotation());
    posicionesObjetivos2.push_back(sf::Vector2f(441.64, 724.64));
    rotacionObjetivos2.push_back(315);

    figurasObjetivo[5].formaFigura.setPosition(sf::Vector2f(229.5, 653));
    figurasObjetivo[5].formaFigura.setRotation(45);
    figurasObjetivo[5].formaFigura.setFillColor(sf::Color(34, 113,179));
    posicionesObjetivos.push_back(figurasObjetivo[5].formaFigura.getPosition());
    rotacionObjetivos.push_back(figurasObjetivo[5].formaFigura.getRotation());
    posicionesObjetivos2.push_back(sf::Vector2f(371.9, 652.9));
    rotacionObjetivos2.push_back(45);

    figurasObjetivo[6].formaFigura.setPosition(sf::Vector2f(406, 688));
    figurasObjetivo[6].formaFigura.setScale(1, -1);
    figurasObjetivo[6].formaFigura.setRotation(90);
    figurasObjetivo[6].formaFigura.setFillColor(sf::Color(34, 113,179));
    posicionesObjetivos.push_back(figurasObjetivo[6].formaFigura.getPosition());
    rotacionObjetivos.push_back(figurasObjetivo[6].formaFigura.getRotation());
    posicionesObjetivos2.push_back(sf::Vector2f(195, 689));
    rotacionObjetivos2.push_back(90);
}


struct Vector2 {
    float x, y;

    Vector2 operator-(const Vector2& other) const { return {x - other.x, y - other.y}; }
    Vector2 operator+(const Vector2& other) const { return {x + other.x, y + other.y}; }
    Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }

    float dot(const Vector2& other) const { return x * other.x + y * other.y; }
    float length() const { return std::sqrt(x * x + y * y); }

    Vector2 normalize() const {
        float len = length();
        if (len == 0) return {0, 0}; // evitar división por cero
        return {x / len, y / len};
    }
    Vector2 perpendicular() const { return {-y, x}; }
};

std::vector<Vector2> getVertices(const sf::ConvexShape& shape) {
    std::vector<Vector2> vertices;
    for (unsigned int i = 0; i < shape.getPointCount(); ++i) {
        sf::Vector2f p = shape.getTransform().transformPoint(shape.getPoint(i));
        vertices.push_back({p.x, p.y});
    }
    return vertices;
}

std::pair<float, float> projectPolygon(const std::vector<Vector2>& vertices, const Vector2& axis) {
    float minProjection = std::numeric_limits<float>::max();
    float maxProjection = std::numeric_limits<float>::lowest();

    for (const auto& vertex : vertices) {
        float projection = vertex.dot(axis);
        minProjection = std::min(minProjection, projection);
        maxProjection = std::max(maxProjection, projection);
    }
    return {minProjection, maxProjection};
}

bool overlap(float minA, float maxA, float minB, float maxB) {
    return maxA >= minB && maxB >= minA;
}

bool checkCollisionSAT(const sf::ConvexShape& shapeA, const sf::ConvexShape& shapeB, Vector2& mtv) {
    std::vector<Vector2> verticesA = getVertices(shapeA);
    std::vector<Vector2> verticesB = getVertices(shapeB);

    float minOverlap = std::numeric_limits<float>::max();
    Vector2 smallestAxis;

    auto testAxes = [&](const std::vector<Vector2>& verts1, const std::vector<Vector2>& verts2) {
        for (size_t i = 0; i < verts1.size(); ++i) {
            Vector2 p1 = verts1[i];
            Vector2 p2 = verts1[(i + 1) % verts1.size()];
            Vector2 edge = p2 - p1;
            Vector2 axis = edge.perpendicular().normalize();

            if (axis.length() == 0) continue;

            auto projA = projectPolygon(verts1, axis);
            auto projB = projectPolygon(verts2, axis);

            if (!overlap(projA.first, projA.second, projB.first, projB.second)) {
                return false; // Separados
            } else {
                float overlapAmt = std::min(projA.second, projB.second) - std::max(projA.first, projB.first);
                if (overlapAmt < minOverlap) {
                    minOverlap = overlapAmt;
                    smallestAxis = axis;
                }
            }
        }
        return true;
    };

    if (!testAxes(verticesA, verticesB)) return false;
    if (!testAxes(verticesB, verticesA)) return false;


    mtv = smallestAxis * minOverlap;
    return true;
}

void minijuegoTangram::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
        for (auto &figura : figurasObjetivo)
        {
            figura.seleccionada = false;
        }

        for (auto &figura : figuras)
        {
            if (figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)){
                figura.arrastrando = true;
                figura.seleccionada = true;
            }else {
                figura.arrastrando = false;
                figura.seleccionada = false;
            }
        }
    } else if (evento.type == sf::Event::MouseMoved) {
        for (auto &figura : figuras)
        {
            if (figura.arrastrando == true) {
                figura.formaFigura.setPosition(posicionEnVentana);
                std::cout << "Posicion X: " << std::to_string(figura.formaFigura.getPosition().x) << std::endl;
                std::cout << "Posicion Y: " << std::to_string(figura.formaFigura.getPosition().y) << std::endl;
            }
        }

    } else if (evento.type == sf::Event::MouseButtonReleased && evento.mouseButton.button == sf::Mouse::Left){
        for (auto &figuraA : figuras)
        {
            if(figuraA.arrastrando == true){
                figuraA.arrastrando = false;

                for (auto &figuraB : figuras)
                {
                    if (&figuraA == &figuraB) continue;

                    Vector2 mtv;
                    if (checkCollisionSAT(figuraA.formaFigura, figuraB.formaFigura, mtv)) {
                        // Separamos usando el MTV
                        figuraA.formaFigura.move(mtv.x, mtv.y);
                    }

                }
            }
        }
    } else if(evento.type == sf::Event::MouseWheelScrolled){
        for(auto &figura : figuras)
        {
            figura.seleccionada = false;
        }
        for (auto &figura : figuras)
        {
            if(evento.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel && figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)){
                if (evento.mouseWheelScroll.delta > 0){
                    figura.formaFigura.rotate(5);
                } else if (evento.mouseWheelScroll.delta < 0){
                    figura.formaFigura.rotate(-5);
                }
                std::cout << "Rotacion: " << std::to_string(figura.formaFigura.getRotation()) << std::endl;
                figura.seleccionada = true;
            }
        }
    } else if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Right){
        for (auto &figura : figuras)
        {
            if (figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)) figura.formaFigura.rotate(90);
            figura.seleccionada = true;
        }
    } else if(evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Middle){
        for (auto &figura : figuras)
        {
            if (figura.orientacion == 1){
                if (figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)) {
                    figura.formaFigura.setScale(1, -1);
                    figura.seleccionada = true;
                }
                figura.orientacion = 2;
            } else {
                if (figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)) {
                    figura.formaFigura.setScale(1, 1);
                    figura.seleccionada = true;
                }
                figura.orientacion = 1;
            }
        }
    }
    if (evento.type == sf::Event::KeyPressed) {
        if(evento.key.code == sf::Keyboard::Enter){
            juego->cambiarPantalla(std::make_unique<minijuegoAutotronica>(juego));
        }
        for (auto &figura : figuras)
        {
            if (figura.seleccionada){
                if (evento.key.code == sf::Keyboard::Up) {
                    figura.formaFigura.move(0, -1);
                } else if (evento.key.code == sf::Keyboard::Down) {
                    figura.formaFigura.move(0, 1);
                } else if (evento.key.code == sf::Keyboard::Left) {
                    figura.formaFigura.move(-1, 0);
                } else if (evento.key.code == sf::Keyboard::Right) {
                    figura.formaFigura.move(1, 0);
                }
                std::cout << "Posicion X: " << std::to_string(figura.formaFigura.getPosition().x) << std::endl;
                std::cout << "Posicion Y: " << std::to_string(figura.formaFigura.getPosition().y) << std::endl;
            }
        }
    }
}

void minijuegoTangram::actualizar(){
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);

    for (auto& figura : figuras) {
        if (figura.seleccionada)
        {
            figura.formaFigura.setFillColor(sf::Color(255, 255, 255));
        } else {
            figura.formaFigura.setFillColor(figura.colorOriginal);
        }
    }
    for (int i = 0; i <= 6; i++)
    {

        if (i == 5 && (figuras[i].formaFigura.getRotation() == rotacionObjetivos[i] * 3 || figuras[i].formaFigura.getRotation() == rotacionObjetivos[i] * 5 || figuras[i].formaFigura.getRotation() == rotacionObjetivos[i] * 7)){
            figuras[i].formaFigura.setRotation(rotacionObjetivos[i]);
        } else if(i == 6 && (figuras[i].formaFigura.getRotation() == 270)){
            figuras[i].formaFigura.setRotation(90);
        }

        float diferenciaPosX  = std::abs(posicionesObjetivos[i].x - figuras[i].formaFigura.getPosition().x);
        float diferenciaPosY  = std::abs(posicionesObjetivos[i].y - figuras[i].formaFigura.getPosition().y);
        float diferenciaGrados = std::abs(rotacionObjetivos[i] - figuras[i].formaFigura.getRotation());

        if (i == 0){
            float diferenciaPosX  = std::abs(posicionesObjetivos[1].x - figuras[i].formaFigura.getPosition().x);
            float diferenciaPosY  = std::abs(posicionesObjetivos[1].y - figuras[i].formaFigura.getPosition().y);
            float diferenciaGrados = std::abs(rotacionObjetivos[1] - figuras[i].formaFigura.getRotation());
            if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
            {
                figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
            } else {
                figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
            }
        } else if (i == 1){
            float diferenciaPosX  = std::abs(posicionesObjetivos[0].x - figuras[i].formaFigura.getPosition().x);
            float diferenciaPosY  = std::abs(posicionesObjetivos[0].y - figuras[i].formaFigura.getPosition().y);
            float diferenciaGrados = std::abs(rotacionObjetivos[0] - figuras[i].formaFigura.getRotation());
            if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
            {
                figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
            } else {
                figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
            }
        } else if (i == 3){
            float diferenciaPosX  = std::abs(posicionesObjetivos[4].x - figuras[i].formaFigura.getPosition().x);
            float diferenciaPosY  = std::abs(posicionesObjetivos[4].y - figuras[i].formaFigura.getPosition().y);
            float diferenciaGrados = std::abs(rotacionObjetivos[4] - figuras[i].formaFigura.getRotation());
            if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
            {
                figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
            } else {
                figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
            }
        } else if (i == 4){
            float diferenciaPosX  = std::abs(posicionesObjetivos[3].x - figuras[i].formaFigura.getPosition().x);
            float diferenciaPosY  = std::abs(posicionesObjetivos[3].y - figuras[i].formaFigura.getPosition().y);
            float diferenciaGrados = std::abs(rotacionObjetivos[3] - figuras[i].formaFigura.getRotation());
            if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
            {
                figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
            } else {
                figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
            }
        }

        if (figuras[i].formaFigura.getFillColor() != sf::Color::Cyan)
        {
            if (((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0))
            {
                if(i == 6){
                    if (figuras[i].formaFigura.getScale() != sf::Vector2f(1.f, -1.f)){
                        figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                        continue;
                    }
                }
                figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
            } else {
                float diferenciaPosX  = std::abs(posicionesObjetivos2[i].x - figuras[i].formaFigura.getPosition().x);
                float diferenciaPosY  = std::abs(posicionesObjetivos2[i].y - figuras[i].formaFigura.getPosition().y);
                float diferenciaGrados = std::abs(rotacionObjetivos2[i] - figuras[i].formaFigura.getRotation());
                if (i == 0){
                    float diferenciaPosX  = std::abs(posicionesObjetivos2[1].x - figuras[i].formaFigura.getPosition().x);
                    float diferenciaPosY  = std::abs(posicionesObjetivos2[1].y - figuras[i].formaFigura.getPosition().y);
                    float diferenciaGrados = std::abs(rotacionObjetivos2[1] - figuras[i].formaFigura.getRotation());
                    if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
                    {
                        figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
                    } else {
                        figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                    }
                } else if (i == 1){
                    float diferenciaPosX  = std::abs(posicionesObjetivos2[0].x - figuras[i].formaFigura.getPosition().x);
                    float diferenciaPosY  = std::abs(posicionesObjetivos2[0].y - figuras[i].formaFigura.getPosition().y);
                    float diferenciaGrados = std::abs(rotacionObjetivos2[0] - figuras[i].formaFigura.getRotation());
                    if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
                    {
                        figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
                    } else {
                        figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                    }
                } else if (i == 3){
                    float diferenciaPosX  = std::abs(posicionesObjetivos2[4].x - figuras[i].formaFigura.getPosition().x);
                    float diferenciaPosY  = std::abs(posicionesObjetivos2[4].y - figuras[i].formaFigura.getPosition().y);
                    float diferenciaGrados = std::abs(rotacionObjetivos2[4] - figuras[i].formaFigura.getRotation());
                    if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
                    {
                        figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
                    } else {
                        figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                    }
                } else if (i == 4){
                    float diferenciaPosX  = std::abs(posicionesObjetivos2[3].x - figuras[i].formaFigura.getPosition().x);
                    float diferenciaPosY  = std::abs(posicionesObjetivos2[3].y - figuras[i].formaFigura.getPosition().y);
                    float diferenciaGrados = std::abs(rotacionObjetivos2[3] - figuras[i].formaFigura.getRotation());
                    if ((diferenciaPosX <= 2 && diferenciaPosY <= 2) && diferenciaGrados == 0)
                    {
                        figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
                    } else {
                        figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                    }
                }
                if (((diferenciaPosX <= 3 && diferenciaPosY <= 3) && diferenciaGrados == 0))
                {
                    figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
                } else {
                    figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                }
                if (((diferenciaPosX <= 3 && diferenciaPosY <= 3) && diferenciaGrados == 0))
                {
                    if(i == 6){
                        if (figuras[i].formaFigura.getScale() == sf::Vector2f(1.f, -1.f)){
                            figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                            continue;
                    }
                }
                    figuras[i].formaFigura.setFillColor(sf::Color::Cyan);
                } else {
                    figuras[i].formaFigura.setFillColor(figuras[i].colorOriginal);
                }
            }
        }
    }
}

void minijuegoTangram::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    for (const auto& figura : figurasObjetivo) {
        window.draw(figura.formaFigura);
    }
    for (const auto& figura : figuras) {
        window.draw(figura.formaFigura);
    }
}