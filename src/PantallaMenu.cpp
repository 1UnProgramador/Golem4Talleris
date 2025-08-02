#include "../include/PantallaMenu.h"
#include "../include/PantallaSeleccionar.h"
#include "../include/Juego.h"
#include <memory>

PantallaMenu::PantallaMenu(Juego* juego) : Pantalla(juego){
    fuente.loadFromFile("../assets/Bangers-Regular.ttf");
    texto.setFont(fuente);
    texto.setString("Presiona Enter para Comenzar!");
    texto.setCharacterSize(70);
    texto.setPosition(500, 500);
}

void PantallaMenu::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter){
        juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego));
    }
}

void PantallaMenu::actualizar(){}

void PantallaMenu::renderizar(sf::RenderWindow& window){
    window.draw(texto);
}