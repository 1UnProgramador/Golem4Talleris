#include "../../include/minijuegoPonchar/minijuegoPonchar.h"
#include "../../include/minijuegoPaginaWeb/minijuegoPaginaWeb.h"
#include "../../include/logica/Juego.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <string>

/* #include "../../assets/minijuegoPonchar/naranjaBlanco.png" */
minijuegoPonchar::minijuegoPonchar(Juego* juego) : Pantalla(juego){
    tFondo.loadFromFile("../assets/fondo.png");
    fondo.setTexture(tFondo);
    /* fondo2.setTexture(tFondo);
    fondo3.setTexture(tFondo);
    fondo4.setTexture(tFondo); */

    /* fondo2.setScale(0.8, 0.8);
    fondo3.setScale(0.8, 0.8);
    fondo4.setScale(0.8, 0.8); */

    fondo.setPosition(0, 0);
    /* fondo2.setPosition(fondo.getGlobalBounds().width, 0);
    fondo3.setPosition(0, fondo.getGlobalBounds().height);
    fondo4.setPosition(fondo2.getPosition().x, fondo3.getPosition().y); */

    float fX = sf::VideoMode::getDesktopMode().width / fondo.getGlobalBounds().width;
    float fY = sf::VideoMode::getDesktopMode().height / fondo.getGlobalBounds().height;

    fondo.setScale(fX, fY);

    int nCable = 1;
    fuente.loadFromFile("../assets/textos/Bangers-Regular.ttf");
    texto.setFont(fuente);
    texto.setString("");
    texto.setCharacterSize(24);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(10, 10);
    std::vector<std::string> nombresCables = {"naranjaBlanco", "naranja", "verdeBlanco", "azul", "azulBlanco", "verde", "cafeBlanco", "cafe"};
    for (const auto& nombre : nombresCables) {
        Cable cable;
        cable.tCable = std::make_shared<sf::Texture>();

        cable.pObjetivo.setPosition(1000 + (20) * nCable, 75);
        cable.pObjetivo.setSize(sf::Vector2f(11, 16));
        cable.pObjetivo.setFillColor(sf::Color::Red);

        if (!cable.tCable->loadFromFile("../assets/minijuegoPonchar/" + nombre + ".png")) {
            std::cerr << "No se pudo cargar " << nombre << ".png" << std::endl;
        }
        cable.pinObjetivo = nCable;
        cable.sCable.setScale(3, 3);
        cable.sCable.setTexture(*cable.tCable); // se desreferencia al puntero
        cables.push_back(cable);
        nCable += 1;
    }
}

void minijuegoPonchar::ManejarEvento(sf::Event evento){
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape)
    {
        exit(0);
    }
    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter){
        juego->cambiarPantalla(std::make_unique<minijuegoPaginaWeb>(juego));
    }
    if (evento.type == sf::Event::MouseButtonPressed) {
        // Detecta si el clic está sobre algún cable
        for (int i = 0; i <= 7; i++)
        {
            (cables[i].sCable.getGlobalBounds().contains(posicionEnVentana)) ? cables[i].arrastrando = true : cables[i].arrastrando = false;
        }
    } else if (evento.type == sf::Event::MouseMoved) {
        // Si dragging == true, actualiza la posición del cable al mouse
    } else if (evento.type == sf::Event::MouseButtonReleased)
    {

        for (int i = 0; i <= 7; i++)
        {
            for (int j = 0; j <= 7; j++)
            {
                if (cables[i].sCable.getGlobalBounds().intersects(cables[j].pObjetivo.getGlobalBounds()))
                {
                    cables[i].sCable.setPosition(cables[j].pObjetivo.getPosition().x - 5, cables[j].pObjetivo.getPosition().y);
                    cables[i].arrastrando = false;
                    cables[i].conectado = true;

                    if (cables[i].sCable.getGlobalBounds().intersects(cables[i].pObjetivo.getGlobalBounds())){
                        cables[i].correcto = true;
                        cables[j].pObjetivo.setFillColor(sf::Color::Green);
                        tIncorrectos--;
                    } else {
                        cables[i].correcto = false;
                        cables[j].pObjetivo.setFillColor(sf::Color::Red);
                        tIncorrectos++;
                    }

                    break;
                }
            }
            if (!cables[i].conectado) {
                cables[i].sCable.setPosition(100 + (20) * i, sf::VideoMode::getDesktopMode().height - cables[i].sCable.getGlobalBounds().height);
                cables[i].arrastrando = false;
                cables[i].conectado = false;
            }
        }
    }
}


void minijuegoPonchar::actualizar(){
    posicionMouse = sf::Mouse::getPosition(juego->getWindow());
    posicionEnVentana = juego->getWindow().mapPixelToCoords(posicionMouse);

    for (int i = 0; i <= 7; i++)
    {
        if (cables[i].arrastrando) {
            cables[i].sCable.setPosition(posicionEnVentana);
        } else if (!cables[i].conectado)
        {
            cables[i].sCable.setPosition(100 + (20) * (i + 1), sf::VideoMode::getDesktopMode().height - cables[i].sCable.getGlobalBounds().height);
        }

    }
    texto.setString("Estas haciendolo genial! Actualmente tienes:\n"+std::to_string(tIncorrectos)+" cables incorrectos");
}

void minijuegoPonchar::renderizar(sf::RenderWindow& window){
    window.draw(fondo);
    /* window.draw(fondo2);
    window.draw(fondo3);
    window.draw(fondo4); */
    for (int i = 0; i <= 7; i++){
        window.draw(cables[i]);
        window.draw(cables[i].pObjetivo);
    }
    window.draw(texto);
}
