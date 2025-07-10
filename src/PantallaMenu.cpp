#include "../include/PantallaMenu.h"

PantallaMenu::PantallaMenu(std::function<void()> onStartCallback) : onStart(onStartCallback){
    fuente.loadFromFile("../assets/Bangers-Regular.ttf");
    texto.setFont(fuente);
    texto.setString("Presiona Enter para Comenzar!");
    texto.setCharacterSize(70);
    texto.setPosition(500, 500);
}

void PantallaMenu::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter){
        onStart();
    }
}

void PantallaMenu::actualizar(){}

void PantallaMenu::renderizar(sf::RenderWindow& window){
    window.draw(texto);
}