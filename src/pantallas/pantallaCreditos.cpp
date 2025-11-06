/* #include "../../include/minijuegoTopografia/minijuegoTopografia.h" */
/* #include "../../include/pantallas/PantallaSeleccionar.h" */
#include "../../include/pantallas/pantallaCreditos.h"
#include "../../include/pantallas/pantallaCarga.h"
#include "../../include/pantallas/pantallaMenu.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

#include "../../src/logica/assetManager.h"

pantallaCreditos::pantallaCreditos(Juego* juego) : Pantalla(juego){
    tFondo1.loadFromMemory(fondoInformatica_png, fondoInformatica_png_len);
    fondo1.setTexture(tFondo1);

    fondo1.setPosition(0, 0);

    float fX = sf::VideoMode::getDesktopMode().width / fondo1.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo1.getGlobalBounds().height;

    fondo1.setScale(fX, fY);


    tFondo2.loadFromMemory(fondoElectricidad_png, fondoElectricidad_png_len);
    fondo2.setTexture(tFondo2);

    fondo2.setPosition(0, fondo1.getGlobalBounds().height);

    float fX2 = sf::VideoMode::getDesktopMode().width / fondo2.getGlobalBounds().width;
    float fY2 = sf::VideoMode::getDesktopMode().height / fondo2.getGlobalBounds().height;

    fondo2.setScale(fX2, fY2);



    tFondo3.loadFromMemory(fondoDiseno_png, fondoDiseno_png_len);
    fondo3.setTexture(tFondo3);

    fondo3.setPosition(0, fondo1.getGlobalBounds().height + fondo2.getGlobalBounds().height);

    float fX3 = sf::VideoMode::getDesktopMode().width / fondo3.getGlobalBounds().width;
    float fY3 = sf::VideoMode::getDesktopMode().height / fondo3.getGlobalBounds().height;

    fondo3.setScale(fX3, fY3);



    tFondo4.loadFromMemory(fondoMetalmecanica_png, fondoMetalmecanica_png_len);
    fondo4.setTexture(tFondo4);

    fondo4.setPosition(0, fondo1.getGlobalBounds().height + fondo2.getGlobalBounds().height + fondo3.getGlobalBounds().height);

    float fX4 = sf::VideoMode::getDesktopMode().width / fondo4.getGlobalBounds().width;
    float fY4 = sf::VideoMode::getDesktopMode().height / fondo4.getGlobalBounds().height;

    fondo4.setScale(fX4, fY4);

    fuente.loadFromMemory(Ubuntu_Bold_ttf, Ubuntu_Bold_ttf_len);
    texto.setFont(fuente);
    texto.setCharacterSize(50);


    prueba.setSize(sf::Vector2f(500, 500));
    prueba.setFillColor(sf::Color::Green);
    prueba.setOrigin(prueba.getGlobalBounds().width / 2, prueba.getGlobalBounds().height / 2);
    prueba.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    texto.setString(utf8_to_wstring(wrapTextString("Santiago Palacio\nBinye Chindoy\nSamuel Martínez\nCamilo Carvajal\n\n11-03", fuente, 50, prueba.getGlobalBounds().width)));
    texto.setOrigin(texto.getGlobalBounds().width / 2, texto.getGlobalBounds().height / 2);
    texto.setPosition(prueba.getPosition());
}
void pantallaCreditos::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed){
        if(evento.key.code == sf::Keyboard::Escape){
            juego->cambiarPantalla(std::make_unique<PantallaMenu>(juego));
        }
    }
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

    /* window.draw(prueba); */
    window.draw(texto);
}