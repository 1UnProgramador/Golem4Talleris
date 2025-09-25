#include "../../include/minijuegoTangram/minijuegoTangram.h"
#include "../../include/logica/Juego.h"
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<std::vector<int>> posicionesObjetivos = {
    {{200, 200}},
    {{0, 0}},
    {{0, 0}},
    {{0, 0}},
    {{0, 0}},
    {{0, 0}},
    {{0, 0}}
};

minijuegoTangram::minijuegoTangram(Juego* juego) : Pantalla(juego){
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
    tG1.formaFigura.setFillColor(sf::Color::Red);
    tG1.formaFigura.setPosition(sf::Vector2f(200, 200));
    tG1.formaFigura.setOrigin(tG1.formaFigura.getGlobalBounds().width / 2, tG1.formaFigura.getGlobalBounds().height / 2);

    tG2.formaFigura.setPointCount(3);
    tG2.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tG2.formaFigura.setPoint(1, sf::Vector2f(200, 0));
    tG2.formaFigura.setPoint(2, sf::Vector2f(0, 200));
    tG2.formaFigura.setFillColor(sf::Color::Red);
    tG2.formaFigura.setPosition(sf::Vector2f(400, 200));
    tG2.formaFigura.setOrigin(tG2.formaFigura.getGlobalBounds().width / 2, tG2.formaFigura.getGlobalBounds().height / 2);

    tM1.formaFigura.setPointCount(3);
    tM1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tM1.formaFigura.setPoint(1, sf::Vector2f(141, 0));
    tM1.formaFigura.setPoint(2, sf::Vector2f(0, 141));
    tM1.formaFigura.setFillColor(sf::Color::Green);
    tM1.formaFigura.setPosition(sf::Vector2f(541, 141));
    tM1.formaFigura.setOrigin(tM1.formaFigura.getGlobalBounds().width / 2, tM1.formaFigura.getGlobalBounds().height / 2);

    tP1.formaFigura.setPointCount(3);
    tP1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tP1.formaFigura.setPoint(1, sf::Vector2f(100, 0));
    tP1.formaFigura.setPoint(2, sf::Vector2f(0, 100));
    tP1.formaFigura.setFillColor(sf::Color::Yellow);
    tP1.formaFigura.setPosition(sf::Vector2f(641, 100));
    tP1.formaFigura.setOrigin(tP1.formaFigura.getGlobalBounds().width / 2, tP1.formaFigura.getGlobalBounds().height / 2);

    tP2.formaFigura.setPointCount(3);
    tP2.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    tP2.formaFigura.setPoint(1, sf::Vector2f(100, 0));
    tP2.formaFigura.setPoint(2, sf::Vector2f(0, 100));
    tP2.formaFigura.setFillColor(sf::Color::Yellow);
    tP2.formaFigura.setPosition(sf::Vector2f(741, 100));
    tP2.formaFigura.setOrigin(tP2.formaFigura.getGlobalBounds().width / 2, tP2.formaFigura.getGlobalBounds().height / 2);

    c1.formaFigura.setPointCount(4);
    c1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    c1.formaFigura.setPoint(1, sf::Vector2f(100, 0));
    c1.formaFigura.setPoint(2, sf::Vector2f(100, 100));
    c1.formaFigura.setPoint(3, sf::Vector2f(0, 100));
    c1.formaFigura.setFillColor(sf::Color::Blue);
    c1.formaFigura.setPosition(sf::Vector2f(841, 100));
    c1.formaFigura.setOrigin(c1.formaFigura.getGlobalBounds().width / 2, c1.formaFigura.getGlobalBounds().height / 2);

    p1.formaFigura.setPointCount(4);
    p1.formaFigura.setPoint(0, sf::Vector2f(0, 0));
    p1.formaFigura.setPoint(1, sf::Vector2f(141, 0));
    p1.formaFigura.setPoint(2, sf::Vector2f(212, 71));
    p1.formaFigura.setPoint(3, sf::Vector2f(71, 71));
    p1.formaFigura.setFillColor(sf::Color::White);
    p1.formaFigura.setPosition(sf::Vector2f(1000, 71));
    p1.formaFigura.setOrigin(p1.formaFigura.getGlobalBounds().width / 2, p1.formaFigura.getGlobalBounds().height / 2);

    figuras.push_back(tG1);
    figuras.push_back(tG2);
    figuras.push_back(tM1);
    figuras.push_back(tP1);
    figuras.push_back(tP2);
    figuras.push_back(c1);
    figuras.push_back(p1);
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

// 🔹 Devuelve true si colisionan y además calcula el MTV
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
    if (evento.type == sf::Event::MouseButtonPressed) {
        for (auto &figura : figuras)
        {
            (figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)) ? figura.arrastrando = true : figura.arrastrando = false;
        }
    } else if (evento.type == sf::Event::MouseMoved) {
        for (auto &figura : figuras)
        {
            if (figura.arrastrando == true) {
                figura.formaFigura.setPosition(posicionEnVentana);
            }
        }

    } else if (evento.type == sf::Event::MouseButtonReleased){
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
        for (auto &figura : figuras)
        {
            if(evento.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel && figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)){
                if (evento.mouseWheelScroll.delta > 0){
                    figura.formaFigura.rotate(1);
                } else if (evento.mouseWheelScroll.delta < 0){
                    figura.formaFigura.rotate(-1);
                }
            }
        }
    } else if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::G){
        for (auto &figura : figuras)
        {
            if (figura.orientacion == 1){
                if (figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)) figura.formaFigura.setScale(1, -1);
                figura.orientacion = 2;
            } else {
                if (figura.formaFigura.getGlobalBounds().contains(posicionEnVentana)) figura.formaFigura.setScale(1, 1);
                figura.orientacion = 1;
            }
        }
    }
}

void minijuegoTangram::actualizar(){
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);


}

void minijuegoTangram::renderizar(sf::RenderWindow& window){
    window.draw(figuras.at(0).formaFigura);
    window.draw(figuras.at(1).formaFigura);
    window.draw(figuras.at(2).formaFigura);
    window.draw(figuras.at(3).formaFigura);
    window.draw(figuras.at(4).formaFigura);
    window.draw(figuras.at(5).formaFigura);
    window.draw(figuras.at(6).formaFigura);
}