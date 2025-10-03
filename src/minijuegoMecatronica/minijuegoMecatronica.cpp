#include "../../include/logica/Juego.h"
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"
#include "../../include/minijuegoRedes/minijuegoRedes.h"

#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <iostream>

minijuegoMecatronica::minijuegoMecatronica(Juego* juego) : Pantalla(juego){

}
void minijuegoMecatronica::ManejarEvento(sf::Event evento){
    if(evento.type == sf::Event::KeyPressed){
        if (evento.key.code == sf::Keyboard::Enter){
juego->cambiarPantalla(std::make_unique<minijuegoRedes>(juego));
        }
    }
}
void minijuegoMecatronica::actualizar(){

}
void minijuegoMecatronica::renderizar(sf::RenderWindow& window){

}