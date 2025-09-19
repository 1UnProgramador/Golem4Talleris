#include "../../include/minijuegoTangram/minijuegoTangram.h"
#include "../../include/logica/Juego.h"


minijuegoTangram::minijuegoTangram(Juego* juego) : Pantalla(juego){
    tG1.setPointCount(3);
    tG1.setPoint(0, sf::Vector2f(0, 0));
    tG1.setPoint(1, sf::Vector2f(200, 0));
    tG1.setPoint(2, sf::Vector2f(0, 200));
    tG1.setFillColor(sf::Color::Red);

    tG2.setPointCount(3);
    tG2.setPoint(0, sf::Vector2f(0, 0));
    tG2.setPoint(1, sf::Vector2f(200, 0));
    tG2.setPoint(2, sf::Vector2f(0, 200));
    tG2.setFillColor(sf::Color::Red);
    tG2.setPosition(sf::Vector2f(200, 0));

    tM1.setPointCount(3);
    tM1.setPoint(0, sf::Vector2f(0, 0));
    tM1.setPoint(1, sf::Vector2f(141, 0));
    tM1.setPoint(2, sf::Vector2f(0, 141));
    tM1.setFillColor(sf::Color::Green);
    tM1.setPosition(sf::Vector2f(400, 0));

    tP1.setPointCount(3);
    tP1.setPoint(0, sf::Vector2f(0, 0));
    tP1.setPoint(1, sf::Vector2f(100, 0));
    tP1.setPoint(2, sf::Vector2f(0, 100));
    tP1.setFillColor(sf::Color::Yellow);
    tP1.setPosition(sf::Vector2f(600, 0));

    tP2.setPointCount(3);
    tP2.setPoint(0, sf::Vector2f(0, 0));
    tP2.setPoint(1, sf::Vector2f(100, 0));
    tP2.setPoint(2, sf::Vector2f(0, 100));
    tP2.setFillColor(sf::Color::Yellow);
    tP2.setPosition(sf::Vector2f(0, 300));

    c1.setPointCount(4);
    c1.setPoint(0, sf::Vector2f(0, 0));
    c1.setPoint(1, sf::Vector2f(100, 0));
    c1.setPoint(3, sf::Vector2f(100, 100));
    c1.setPoint(2, sf::Vector2f(0, 100));
    c1.setFillColor(sf::Color::Blue);
    c1.setPosition(sf::Vector2f(200, 300));

    p1.setPointCount(4);
    p1.setPoint(0, sf::Vector2f(0, 0));
    p1.setPoint(1, sf::Vector2f(100, 0));
    p1.setPoint(2, sf::Vector2f(50, 50));   // 100-50, 50
    p1.setPoint(3, sf::Vector2f(-50, 50));  // 0-50, 50
    p1.setFillColor(sf::Color::White);
    p1.setPosition(sf::Vector2f(400, 300));
}


void minijuegoTangram::ManejarEvento(sf::Event evento){

}

void minijuegoTangram::actualizar(){

}

void minijuegoTangram::renderizar(sf::RenderWindow& window){
    window.draw(tG1);
    window.draw(tG2);
    window.draw(tM1);
    window.draw(tP1);
    window.draw(tP2);
    window.draw(c1);
    window.draw(p1);
}