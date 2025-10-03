#include "../../include/pantallas/PantallaMenu.h"
#include "../../include/pantallas/PantallaSeleccionar.h"
#include "../../include/pantallas/PantallaCarga.h"
#include "../../include/logica/Juego.h"
#include <memory>

PantallaMenu::PantallaMenu(Juego* juego) : Pantalla(juego){

    tFondoMenu.loadFromFile("../assets/menu/dibujo fondo menu.jpg");
    FondoMenu.setTexture(tFondoMenu);
    tPlay.loadFromFile("../assets/menu/boton play.png");
    play.setTexture(tPlay);
    play.setOrigin(play.getGlobalBounds().width / 2, play.getGlobalBounds().height / 2);
    tExtra.loadFromFile("../assets/menu/boton Extra.png");
    Extra.setTexture(tExtra);
    Extra.setOrigin(Extra.getGlobalBounds().width / 2, play.getGlobalBounds().height / 2);
    tExit.loadFromFile("../assets/menu/boton exit.png");
    Exit.setTexture(tExit);
    Exit.setOrigin(Exit.getGlobalBounds().width / 2, play.getGlobalBounds().height / 2);
   

    fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf");
    texto.setFont(fuente);
    texto.setString("Enter para Comenzar!");
    texto.setCharacterSize(70);
    texto.setOrigin(texto.getLocalBounds().left + texto.getLocalBounds().width / 2.0f , texto.getLocalBounds().top + texto.getLocalBounds().height / 2.0f);
    texto.setPosition(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f);

    play.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.8);
    play.setScale(3.5, 3.5);
    
    Extra.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.6);
    Extra.setScale(3.5, 3.5);

    Exit.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 1.45);
    Exit.setScale(3.5, 3.5);

    float fX = sf::VideoMode::getDesktopMode().width / FondoMenu.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / FondoMenu.getGlobalBounds().height;

    FondoMenu.setScale(fX, fY);
}

void PantallaMenu::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter){
        juego->instrucciones = "Hola y Bienvenido a\nGollem4Talleris!";
        juego->cambiarPantalla(std::make_unique<PantallaCarga>(juego));
    }
}

void PantallaMenu::actualizar(){

}

void PantallaMenu::renderizar(sf::RenderWindow& window){
    /* window.draw(texto); */
    window.draw(FondoMenu);
    window.draw(play);
    window.draw(Extra);
    window.draw(Exit);
}