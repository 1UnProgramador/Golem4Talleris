#include <iostream>
#include "../../include/pantallas/PantallaCarga.h"
/* #include "../../include/pantallas/PantallaSeleccionar.h" */
#include "../../include/minijuegoMecatronica/minijuegoMecatronica.h"
#include "../../include/logica/Juego.h"
#include <memory>

const std::string Instrumentalizacion [] = {
    "¿Sabias que en P1 se aprende a interconectar redes?",
    "Por otra parte en P2, aparte de programar paginas podras hacer bases de datos con SQL",
    "En P3 haras simulaciones de demoliciones realistas",
    "En P4 podrás armar tu propio robot haciendo uso de electronica y electricidad",
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12"
};

PantallaCarga::PantallaCarga(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondo.png");
    tFondo.setRepeated(true);
    tFondo.setSmooth(false);

    fondo.setTexture(tFondo);
    w = juego->getWindow().getSize().x;
    h = juego->getWindow().getSize().y;

    fondo.setTextureRect(sf::IntRect(0, 0, w, h));

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);


    fondo.setPosition(0, 0);

    fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf");
    imagen.loadFromFile("../assets/temporales/imagenPantallaCarga.png");
    sImagen.setTexture(imagen);


    cBorde.setSize(sf::Vector2f(550, 650));
    cRelleno.setSize(sf::Vector2f(544, 644));
    cBorde.setFillColor(sf::Color(255, 255, 255));
    cRelleno.setFillColor(sf::Color(0, 0, 0));
    cBorde.setOrigin(cBorde.getGlobalBounds().width / 2, cBorde.getGlobalBounds().height / 2);
    cRelleno.setOrigin(cRelleno.getGlobalBounds().width / 2, cRelleno.getGlobalBounds().height / 2);
    cRelleno.setPosition((sf::VideoMode::getDesktopMode().width / 2.0f ), (sf::VideoMode::getDesktopMode().height / 2.0f) - 50);
    cBorde.setPosition(sf::VideoMode::getDesktopMode().width / 2.0f , (sf::VideoMode::getDesktopMode().height / 2.0f) - 50);


    sImagen.setScale(1.57, 1.57);
    sImagen.setOrigin(sImagen.getLocalBounds().width / 2, 0);
    sImagen.setPosition(cRelleno.getPosition().x, (cRelleno.getPosition().y - (cRelleno.getGlobalBounds().height / 2)) + 5 /* + (sImagen.getGlobalBounds().height) + 5 */);

    bienvenida.setFont(fuente);
    bienvenida.setString(juego->instrucciones);
    bienvenida.setCharacterSize(40);
    bienvenida.setOrigin(bienvenida.getGlobalBounds().width / 2, 0);
    bienvenida.setPosition(cRelleno.getPosition().x + 5 , sImagen.getPosition(). y + sImagen.getGlobalBounds().height);

    int size = sizeof(Instrumentalizacion)/sizeof(*Instrumentalizacion);
    srand(time(NULL));
    texto.setFont(fuente);
    texto.setString(Instrumentalizacion[rand()%size]);
    texto.setCharacterSize(40);
    texto.setOrigin(texto.getLocalBounds().left + texto.getLocalBounds().width / 2.0f , texto.getLocalBounds().top + texto.getLocalBounds().height / 2.0f);
    barraCarga.setSize({50, 50});
    barraCarga.setFillColor(sf::Color(0, 0, 255));
    barraCarga.setPosition(0, sf::VideoMode::getDesktopMode().height - barraCarga.getGlobalBounds().height);
    texto.setPosition(sf::VideoMode::getDesktopMode().width / 2.0f, barraCarga.getPosition().y - texto.getGlobalBounds().height);
}

void PantallaCarga::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter){
        juego->cambiarPantalla(std::make_unique<minijuegoMecatronica>(juego));
    }
}

void PantallaCarga::actualizar(){


    offsetX = (offsetX + speedX) % tFondo.getSize().x;
    offsetY = (offsetY + speedY) % tFondo.getSize().y;
    if (offsetX < 0) offsetX += tFondo.getSize().x;
    if (offsetY < 0) offsetY += tFondo.getSize().y;

    // aplicar el desplazamiento al textureRect
    fondo.setTextureRect(sf::IntRect(offsetX, offsetY, w, h));

}

void PantallaCarga::renderizar(sf::RenderWindow& window){
    window.draw(fondo);


    window.draw(texto);
    window.draw(barraCarga);
    window.draw(cBorde);
    window.draw(cRelleno);
    window.draw(sImagen);
    window.draw(bienvenida);
    float time=eje.getElapsedTime().asSeconds()/10.0;
    barraCarga.setSize({window.getSize().x*time, 50});
    if(time>=1.0){
        /* juego->cambiarPantalla(std::make_unique<PantallaSeleccionar>(juego)); */
        barraCarga.setFillColor(sf::Color::Transparent);
    }
}