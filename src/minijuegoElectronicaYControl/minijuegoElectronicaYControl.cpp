#include "../../include/logica/Juego.h"
#include "../../include/minijuegoElectronicaYControl/minijuegoElectronicaYControl.h"

#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>

minijuegoElectronicaYControl::minijuegoElectronicaYControl(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoElectricidad.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    tImpresora.loadFromFile("../assets/minijuegoElectronicaYControl/chasis.png");
    impresora.setTexture(tImpresora);
    impresora.setOrigin(impresora.getGlobalBounds().width / 2, impresora.getGlobalBounds().height / 2);
    impresora.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    impresora.setScale(7.1, 7);

    tSoporte.loadFromFile("../assets/minijuegoElectronicaYControl/soporte.png");
    soporte.setTexture(tSoporte);
    soporte.setOrigin(soporte.getGlobalBounds().width / 2, soporte.getGlobalBounds().height / 2);
    soporte.setPosition(impresora.getPosition().x, impresora.getPosition().y);
    soporte.setScale(7, 7);

    tPuntero.loadFromFile("../assets/minijuegoElectronicaYControl/puntero.png");
    puntero.setTexture(tPuntero);
    puntero.setOrigin(puntero.getGlobalBounds().width / 2, puntero.getGlobalBounds().height / 2);
    puntero.setPosition(soporte.getPosition().x, soporte.getPosition().y + 12);
    puntero.setScale(3.5, 3.5);

    contorno.setSize(sf::Vector2f(impresora.getGlobalBounds().width, impresora.getGlobalBounds().height));
    contorno.setFillColor(sf::Color(128, 128, 128));
    contorno.setOrigin(contorno.getGlobalBounds().width / 2, contorno.getGlobalBounds().height / 2);
    contorno.setPosition(impresora.getPosition());

    float posicionXactual = impresora.getGlobalBounds().left;
    while (posicionXactual <= impresora.getPosition().x + (impresora.getGlobalBounds().width / 2)){
        sf::RectangleShape linea;
        linea.setSize(sf::Vector2f(1, impresora.getGlobalBounds().height));
        linea.setFillColor(sf::Color::Red);
        linea.setPosition(posicionXactual, impresora.getPosition().y - (impresora.getGlobalBounds().height / 2));
        lineasVerticales.push_back(linea);
        posicionXactual += movimiento;
    }
    for (int i = 0; i <= 5; i++)
    {
        lineasVerticales.erase(lineasVerticales.end());
        lineasVerticales.erase(lineasVerticales.begin());
    }


    float posicionYactual = impresora.getGlobalBounds().top;
    while (posicionYactual <= impresora.getPosition().y + (impresora.getGlobalBounds().height / 2)){
        sf::RectangleShape linea;
        linea.setSize(sf::Vector2f(impresora.getGlobalBounds().width - 100, 1));
        linea.setFillColor(sf::Color::Red);
        linea.setPosition(impresora.getPosition().x - (impresora.getGlobalBounds().width / 2) + 50, posicionYactual);
        lineasVerticales.push_back(linea);
        posicionYactual += movimiento;
    }

    puntero.setPosition((lineasVerticales[17].getPosition().x + movimiento / 2), puntero.getPosition().y);

    sf::RectangleShape cuadrado;
    cuadrado.setSize(sf::Vector2f(movimiento, movimiento));
    cuadrado.setOrigin(cuadrado.getGlobalBounds().width / 2, cuadrado.getGlobalBounds().height / 2);
    cuadrado.setFillColor(sf::Color::Blue);
    cuadrado.setPosition(-20, -20);
    std::cout << "cuadrado creado en: X:" << std::to_string(cuadrado.getPosition().x) << " Y: " << std::to_string(cuadrado.getPosition().y) << std::endl;
    cubos.push_back(cuadrado);
}
void minijuegoElectronicaYControl::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed) {
        if(evento.key.code == sf::Keyboard::Down){
            puntero.move(0, movimiento);
            soporte.move(0, movimiento);
            std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y) << std::endl;
        } else if(evento.key.code == sf::Keyboard::Up){
            puntero.move(0, -movimiento);
            soporte.move(0, -movimiento);
            std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y) << std::endl;
        } else if(evento.key.code == sf::Keyboard::Left){
            puntero.move(-movimiento, 0);
            std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y) << std::endl;
        } else if(evento.key.code == sf::Keyboard::Right){
            puntero.move(movimiento, 0);
            std::cout << "puntero en: X: " << std::to_string(puntero.getPosition().x) << " Y: " << std::to_string(puntero.getPosition().y) << std::endl;
        } else if(evento.key.code == sf::Keyboard::Enter){
            size_t i = 0;
            for (auto &cuadrado : cubos){
                if(cuadrado.getPosition() == sf::Vector2f(puntero.getPosition().x, puntero.getPosition().y + (puntero.getGlobalBounds().height / 2) + (cuadrado.getGlobalBounds().height / 2))){
                    cubos.erase(cubos.begin() + i);
                } else {
                    if (i == cubos.size() - 1){
                        sf::RectangleShape cuadrado;
                        cuadrado.setSize(sf::Vector2f(movimiento, movimiento));
                        cuadrado.setOrigin(cuadrado.getGlobalBounds().width / 2, cuadrado.getGlobalBounds().height / 2);
                        cuadrado.setFillColor(sf::Color::Blue);
                        cuadrado.setPosition(puntero.getPosition().x, puntero.getPosition().y + (puntero.getGlobalBounds().height / 2) + (cuadrado.getGlobalBounds().height / 2));
                        std::cout << "cuadrado creado en: X:" << std::to_string(cuadrado.getPosition().x) << " Y: " << std::to_string(cuadrado.getPosition().y) << std::endl;
                        cubos.push_back(cuadrado);
                    }
                }
                ++i;
            }
        }
    }
}
void minijuegoElectronicaYControl::actualizar(){

}
void minijuegoElectronicaYControl::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    window.draw(contorno);

    for(auto &linea : lineasVerticales){
        window.draw(linea);
    }
    for(auto &linea : lineasHorizontales){
        window.draw(linea);
    }

    for (auto &cuadrado : cubos){
        window.draw(cuadrado);
    }

    window.draw(impresora);
    window.draw(soporte);
    window.draw(puntero);


}