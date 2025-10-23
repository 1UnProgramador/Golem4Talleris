#include "../../include/logica/Juego.h"
#include "../../include/minijuegoDisenoArquitectonico/minijuegoDisenoArquitectonico.h"
#include "../../include/pantallas/Metalmecanica.h"

#include <vector>
#include <cmath>
#include <memory>
#include <random>
#include <algorithm>
#include <iostream>

minijuegoDisenoArquitectonico::minijuegoDisenoArquitectonico(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondoDiseno.png");
    fondo.setTexture(tFondo);
    fondo.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);
}
void minijuegoDisenoArquitectonico::ManejarEvento(sf::Event evento){

}
void minijuegoDisenoArquitectonico::actualizar(){

}
void minijuegoDisenoArquitectonico::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
}