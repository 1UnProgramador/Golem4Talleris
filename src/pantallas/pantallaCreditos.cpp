/* #include "../../include/minijuegoTopografia/minijuegoTopografia.h" */
/* #include "../../include/pantallas/PantallaSeleccionar.h" */
#include "../../include/pantallas/pantallaCreditos.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
pantallaCreditos::pantallaCreditos(Juego* juego) : Pantalla(juego){
    tFondo1.loadFromFile("../assets/fondoInformatica.png");
    fondo1.setTexture(tFondo1);

    fondo1.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo1.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo1.getGlobalBounds().height;

    fondo1.setScale(fX, fY);


    tFondo2.loadFromFile("../assets/fondoElectricidad.png");
    fondo2.setTexture(tFondo2);

    fondo2.setPosition(0, fondo1.getGlobalBounds().height);

    float fX2 = sf::VideoMode::getDesktopMode().width / fondo2.getGlobalBounds().width;
    float fY2 = sf::VideoMode::getDesktopMode().height / fondo2.getGlobalBounds().height;

    fondo2.setScale(fX2, fY2);



    tFondo3.loadFromFile("../assets/fondoDiseno.png");
    fondo3.setTexture(tFondo3);

    fondo3.setPosition(0, fondo1.getGlobalBounds().height + fondo2.getGlobalBounds().height);

    float fX3 = sf::VideoMode::getDesktopMode().width / fondo3.getGlobalBounds().width;
    float fY3 = sf::VideoMode::getDesktopMode().height / fondo3.getGlobalBounds().height;

    fondo3.setScale(fX3, fY3);



    tFondo4.loadFromFile("../assets/fondoMetalmecanica.png");
    fondo4.setTexture(tFondo4);

    fondo4.setPosition(0, fondo1.getGlobalBounds().height + fondo2.getGlobalBounds().height + fondo3.getGlobalBounds().height);

    float fX4 = sf::VideoMode::getDesktopMode().width / fondo4.getGlobalBounds().width;
    float fY4 = sf::VideoMode::getDesktopMode().height / fondo4.getGlobalBounds().height;

    fondo4.setScale(fX4, fY4);
}
void pantallaCreditos::ManejarEvento(sf::Event evento){

}
void pantallaCreditos::actualizar(){
    fondo1.move(0, -velocidad);
    fondo2.move(0, -velocidad);
    fondo3.move(0, -velocidad);
    fondo4.move(0, -velocidad);

}
void pantallaCreditos::renderizar(sf::RenderWindow& window){
    window.draw(fondo1);
    window.draw(fondo2);
    window.draw(fondo3);
    window.draw(fondo4);
}